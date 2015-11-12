///
/// @file
/// @ingroup com_group
/// @brief C++ Application Module Template
/// @author MTC 
/// @author WK
/// @author NS
/// @date ++Halloween, 2015
/// 
/// This file serves as both a test and a simple example for implementing
/// a service module in C/C++. 
///
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <cmath>

#include "COMM.H"
//#include "FC.h"
#include "com.h"
#include "com_devel.hpp"
//#include "TestSolver.H"
#include "PackIR.H"


class PackIR : public COM_Object {
  public:

    /// Default constructor.
    PackIR(){
      my_window_name.erase();
    };
    
    ///
    /// @brief Destructor
    ///
    /// The destructor will destroy the externally loaded modules (if they exists)
    ///
    virtual ~PackIR()
    {
    };  


    ///
    /// @brief Initialize stub solver from config file
    ///
    /// This function reads a configuration file and sets
    /// up some example solver-like data for use in testing
    //nt *rank/
    /// @param config_file A pointer to a std::string object where
    /// the configuration filename is specified.
    ///
    void InitApplication(void *config_file)
    {
      std::string *config_name = NULL;
      if(config_file){
        config_name = static_cast<std::string *>(config_file);
        std::ifstream Inf;
        Inf.open(config_name->c_str());
        std::cout << "Opening config file " << config_name->c_str() << std::endl;
        if(!Inf){
          std::cerr << "PackIR::InitModule:Error: Could not open configuration file, "
                    << config_name->c_str() << "." << std::endl;
          return;
        }
        // WARNING: for now, config is unused
        Inf.close();
      }

      // Add metadata for application data items

      // Step (1) sets up solution meta data
      //      Solution().Meta().AddField("time",'s',1,8,"s");

      // Create any application data (based on metadata)
      // Register application data into the window
      //      SolverUtils::RegisterSolverInto(my_window_name,*this);
    };


  void PackSetup()
  {
    packInput.InitializeDefaults();
    packInput.ConfigureFromParams();
  };
    ///
    /// @brief Step the dummy solver through time
    ///
    /// This function steps the dummy solver and sets up
    /// periodic solutions on the grid. time is advanced
    /// by delta_t.
    ///
    void PackSpheres()
    {
      packInput.InitializeDefaults();
      packInput.ConfigureFromParams();
      std::ofstream Ouf(packInput.InputFileName().c_str());
      packInput.CreateSpherePackInput(Ouf);
      Ouf.close();
      std::ostringstream Ostr;
      Ostr << SPHEREPACKCOMMAND << " " << packInput.InputFileName();
      spherePackStatus = system(Ostr.str().c_str());
    };

    
    ///
    /// @brief "Loads" the C++ PackIR
    ///
    /// This function creates an instance of a COM::PackIR object,
    /// creates a new Window with the specified name and registers the
    /// address of the new COM::PackIR object as the ".global"
    /// DataItem of the Window. This registers the C++ COM::PackIR
    /// "object" with the COM runtime system.
    /// 
    /// Next, several member functions are registered. The first
    /// argument to each member function is a COM_RAWDATA type
    /// which will be the address of the object registerd to
    /// the ".global" DataItem.
    ///
    /// @param name const std::string specifying the name of the 
    /// window to load the module into.
    ///
    /// @note This function must be a *static* function in order
    /// for it to work in the COM_LOAD_MODULE interface.
    ///
    /// @note The COM_VOID type has been used here to pass
    /// in a pointer to a std::string object.  This is cool.
    ///
    static void Load(const std::string &name){
      std::cout << "Loading PackIR with name " << name 
                << "." << std::endl;

      PackIR *test_module_pointer = new PackIR();
      COM_new_window(name);
      test_module_pointer->my_window_name = name;
      std::string global_name(name+".global");
      COM_new_dataitem(global_name.c_str(),'w',COM_VOID,1,"");
      COM_set_object(global_name.c_str(),0,test_module_pointer);

      std::vector<COM_Type> types(13,COM_INT);
    
      types[0] = COM_RAWDATA;
      types[1] = COM_VOID;
      types[2] = COM_VOID;
      COM_set_member_function( (name+".InitApplication").c_str(), 
                               (Member_func_ptr)(&PackIR::InitApplication), 
                               global_name.c_str(), "bi", &types[0]);
    
      COM_set_member_function( (name+".PackSpheres").c_str(), 
                               (Member_func_ptr)(&PackIR::PackSpheres), 
                               global_name.c_str(), "b", &types[0]);

      COM_set_member_function( (name+".PackSetup").c_str(), 
                               (Member_func_ptr)(&PackIR::PackSetup), 
                               global_name.c_str(), "b", &types[0]);

      COM_set_member_function( (name+".SetParam").c_str(), 
                               (Member_func_ptr)(&PackIR::SetParam), 
                               global_name.c_str(), "bii", &types[0]);
      
      types[1] = COM_INT;
      types[2] = COM_INT;
      types[3] = COM_INT;
      COM_set_member_function( (name+".GenerateViews").c_str(), 
                               (Member_func_ptr)(&PackIR::GenerateViews), 
                               global_name.c_str(), "bii", &types[0]);

      COM_set_member_function( (name+".GenerateRDF").c_str(), 
                               (Member_func_ptr)(&PackIR::GenerateRDF), 
                               global_name.c_str(), "b", &types[0]);


      COM_window_init_done(name);  
    }

    ///
    /// @brief Unloads the PackIR
    ///
    /// This function simply destroys the COM::PackIRObject created
    /// in the call to Load and then deletes the associated window with
    /// the specified name.
    ///
    static void Unload(const std::string &name){
      std::cout << "Unloading PackIR with name " << name 
                << "." << std::endl;
      PackIR *appModulePointer = NULL;
      std::string global_name(name+".global");
      COM_get_object(global_name.c_str(),0,&appModulePointer);
      COM_assertion_msg(appModulePointer->validate_object()==0, "Invalid object");
      if(appModulePointer){
        std::cout << "Deleting pointer to application module." << std::endl;
        delete appModulePointer;
      }
      std::cout << "Deleting window (" << name << ")" << std::endl;
      COM_delete_window(std::string(name));
      std::cout << "Done Unloading module." << std::endl;
    }

  void SetParam(void *keyPtr,void *valuePtr)
  {
    std::string *keyString;
    std::string *valueString;
    if(keyPtr){
      keyString = static_cast<std::string *>(keyPtr);
    } else {
      return;
    }
    if(valuePtr){
      valueString = static_cast<std::string *>(valuePtr);
    } else {
      return;
    }
    IRAD::Util::ParamType inParam;
    inParam.Key(*keyString);
    inParam.Value(*valueString);
    packInput.push_back(inParam);
  };


  void packshapeswriter(double xnew, double y1, double znew, double cylinderAspect){
    
    std::ofstream viewfile;
    viewfile.open("PackShapesHeader.pov");
    
    viewfile << "#include \"colors.inc\"" << std::endl
             << "#include \"metals.inc\"" << std::endl
             << "#include \"glass.inc\"" << std::endl
             << "#include \"finish.inc\"" << std::endl
             << "#include \"textures.inc\"" << std::endl << std::endl
             << "// ********** Configurable Information ********" << std::endl
             << "background{ color White }" << std::endl
             << "#declare view_loc = <" << xnew << "," << y1 << "," 
             << znew << ">;" << std::endl
             << "camera{ " << std::endl
             << "//	right x*4/4" << std::endl
             << "        location view_loc" << std::endl 
             << "        look_at <0,-0.15,0>" << std::endl 
             << "        sky y" << std::endl 
             << "        angle 40" << std::endl 
             << "}" << std::endl
             << "light_source{ view_loc, 2 } " << std::endl  
             << std::endl
             << "//#include \"bound_box.inc\" " << std::endl
             << "//object{ BoundingBox } " << std::endl
             << std::endl
             << std::endl
             << "// bounding box " << std::endl
             << "#declare linewidth = 0.01; " << std::endl
             << "#declare AR = 1.0; " << std::endl
             << "#declare arz = 1.0/AR; " << std::endl
             << "#declare ary = 1.0; " << std::endl
             << "#declare arx = 1.0/AR; " << std::endl
             << "#declare BoundingBox = " << std::endl
             << "object { " << std::endl
             << "	merge { " << std::endl
             << "		// parallel to x axis " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,-ary,-arz> " << std::endl
             << "			<arx,-ary,-arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,ary,-arz> " << std::endl
             << "			<arx,ary,-arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,-ary,arz> " << std::endl
             << "			<arx,-ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,ary,arz> " << std::endl
             << "			<arx,ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		// parallel to y axis " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,-ary,-arz> " << std::endl
             << "			<-arx,ary,-arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<arx,-ary,-arz> " << std::endl
             << "			<arx,ary,-arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,-ary,arz> " << std::endl
             << "			<-arx,ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<arx,-ary,arz> " << std::endl
             << "			<arx,ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		// parallel to z axis " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,-ary,-arz> " << std::endl
             << "			<-arx,-ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<arx,-ary,-arz> " << std::endl
             << "			<arx,-ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<-arx,ary,-arz> " << std::endl
             << "			<-arx,ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "		cylinder { " << std::endl
             << "			<arx,ary,-arz> " << std::endl
             << "			<arx,ary,arz> " << std::endl
             << "			linewidth " << std::endl
             << "		} " << std::endl
             << "	} " << std::endl
             << "	texture{ Silver_Metal } " << std::endl
             << "} " << std::endl
             << "////////////// shape options ///////////////// " << std::endl
             << "//	0 		sphere " << std::endl
             << "//	1		gelcap " << std::endl
             << "//	2		cylinder " << std::endl
             << "//	3  		icosahedron " << std::endl
             << "//	4		cube " << std::endl
             << "//	5		hmx crystal " << std::endl
             << "//	6		hmx1 crystal " << std::endl
             << "//	7		petn crystal " << std::endl
             << "//	8		rdx crystal " << std::endl
             << "//	9		adn crystal " << std::endl
             << "//	10		cl20 crystal " << std::endl
             << "//**************************************************************************** " 
             << std::endl
             << "// ************* particle shapes ************** " << std::endl
             << "#declare eps1 = 1.0 - 1.0e-6; " << std::endl
             << "// *************** sphere = 0 " << std::endl
             << "#declare PackShape0 = sphere{ <0,0,0> eps1 } " << std::endl
             << "#declare aspect1 = 2.0; " << std::endl
             << "#declare basept = <0.0,-0.5*(2.0-2.0/aspect1), 0.0>; " << std::endl
             << "#declare toppt  = <0.0, 0.5*(2.0-2.0/aspect1), 0.0>; " << std::endl
             << "// GelCap = 1 " << std::endl
             << "#declare PackShape1 =  " << std::endl
             << "object { " << std::endl
             << "	merge { " << std::endl
             << "		sphere { " << std::endl
             << "		 	basept  " << std::endl
             << "		 	1.0/aspect1 " << std::endl
             << "		}		 " << std::endl
             << "		sphere{	 " << std::endl
             << "		 	toppt" << std::endl
             << "		 	1.0/aspect1" << std::endl
             << "		}" << std::endl
             << "		cylinder {" << std::endl
             << "			basept" << std::endl
             << "			toppt" << std::endl
             << "			1.0/aspect1" << std::endl
             << "		}" << std::endl
             << "	}" << std::endl
             << "	scale eps1" << std::endl
             << "}" << std::endl
             << "// *************** cylinder = 2" << std::endl
             << "#declare aspect2 = " << cylinderAspect << ";" << std::endl
             << "#declare r1 = 1.0 / sqrt( 1.0 + aspect2 * aspect2 );" << std::endl
             << "#declare h1 = r1 * aspect2;" << std::endl
             << "#declare bvl = 0.1 * r1;" << std::endl
             << "#declare PackShape2 =" << std::endl
             << "merge {" << std::endl
             << "	cylinder {" << std::endl
             << "		<0, -h1, 0 >" << std::endl
             << "		<0,  h1, 0 >" << std::endl
             << "		r1 - bvl" << std::endl
             << "	}" << std::endl
             << "	cylinder {" << std::endl
             << "		<0, -h1 + bvl, 0 >" << std::endl
             << "		<0,  h1 - bvl, 0 >" << std::endl
             << "		r1" << std::endl
             << "	}" << std::endl
             << "	torus {" << std::endl
             << "		r1 - bvl, bvl" << std::endl
             << "		translate <0, -h1 + bvl, 0 >" << std::endl
             << "	}" << std::endl
             << "	torus {" << std::endl
             << "		r1 - bvl, bvl" << std::endl
             << "		translate <0, h1 - bvl, 0 >" << std::endl
             << "	}" << std::endl
             << "}" << std::endl;
    viewfile.close();

  }

  std::string GenerateSnap(int i,double x,double y,double z,double theta,double aspectRatio)
  {
    int errorStatus = 0;
  
    double xnew = x*std::cos(theta) - z*std::sin(theta);
    double znew = x*std::sin(theta) + z*std::cos(theta);
  
    //Write PackShapesHeader.pov for pack2povray
    packshapeswriter(xnew,y,znew,aspectRatio);
    std::string pngString;
    //Run pack2povray and povray to generate the png image
    std::string povOutFile(packInput.OutputFileName()+std::string(".pov"));
    std::string command(PACK2POVRAYCOMMAND + std::string(" ") +
                        packInput.ColorFileName() + std::string(" ") +
                        packInput.OutputFileName()   + std::string(" ") +
                        povOutFile); 
    errorStatus = system(command.c_str());
    if(!errorStatus){
      command.assign(POVRAYCOMMAND + std::string(" -D ")+povOutFile);
      errorStatus = system(command.c_str());
      if(!errorStatus){
        std::ostringstream Ostr;
        Ostr << packInput.OutputFileName() << "_" 
             << i << ".png";
        pngString.assign(Ostr.str());
        command.assign("cp " + packInput.OutputFileName() + ".png " + pngString);
        errorStatus = system(command.c_str());
      }
    }
    return(pngString);
  }

  void SetupPostProcessing()
  {
    std::string command(std::string("cp ") + std::string(PACKSHAPESEND) + std::string(" .")); 
    system(command.c_str());         
    //Create the bounding box file
    std::ofstream boundfile;
    boundfile.open("bounding_box.inc");
    double xsize = 2.0/packInput.aspectRatio;
    double zsize = 2.0/packInput.aspectRatio;
    double ysize = 2.0;
    double x1,y1,z1,x2,y2,z2,radius;
    if(packInput.domainShape == 0){
      x1 = -1.0/packInput.aspectRatio;
      x2 = 1.0/packInput.aspectRatio;
      y1 = -1;
      y2 = 1;
      z1 = -1.0/packInput.aspectRatio;
      z2 = 1.0/packInput.aspectRatio;
      boundfile << "box{<" << x1 << "," << y1 << "," << z1 << ">,<"
                << x2 << "," << y2 << "," << z2
                << "> texture{pigment{color Silver transmit .7} } }";
    } else {
      x1 = 0.0;
      x2 = 0.0;
      y1 = -1;
      y2 = 1;
      z1 = 0.0;
      z2 = 0.0;
      radius = 1.0/packInput.aspectRatio;
      boundfile << "cylinder{<" << x1 << "," << y1 << "," << z1 << ">,<"
                << x2 << "," << y2 << "," << z2
                << ">,"<< radius << " texture{pigment{color Silver transmit .7} } }";
    }
    boundfile.close();
    /////////////////////
  }

  void GenerateViews(int *numAnglesIn,int *whichAngleIn)
  {

    int increments = *numAnglesIn;
    //    int rdfstats = *doRDFIn;
    int whichAngle = *whichAngleIn;
  
    double xsize = 2.0/packInput.aspectRatio;
    double zsize = 2.0/packInput.aspectRatio;
    double ysize = 2.0;
    double x1 = xsize + 2.0;
    double y1 = 3.0;
    double z1 = -1.0*(zsize + 2.0);
    double pi = std::acos(-1.0);
    std::string command;

    if(increments > 0){
     
      //Create rotating views for dynamically generated sequence xml output 
      for(int i=0; i < increments; i++){
        if(whichAngle < 0 || whichAngle == i){
          std::ostringstream dirStr;
          dirStr << "makeimage_" << i;
          std::ostringstream comStr;
          comStr << "mkdir " << dirStr.str();
          system(comStr.str().c_str());
          chdir(dirStr.str().c_str());
          comStr.clear();
          comStr.str("");
          comStr << "ln -s ../" << packInput.OutputFileName() << " .";
          system(comStr.str().c_str());
          comStr.clear();
          comStr.str("");

          SetupPostProcessing();
 
          double theta = double(i)*(2.0*pi/double(increments));       
          std::string pngString(GenerateSnap(i,x1,y1,z1,theta,packInput.cylinderAspect));
          if(pngString.empty()){
            std::cerr << "Snapshot (" << i << "," << theta << ") failed." << std::endl;
            return;
          }
          comStr << "cp " << pngString << " ../";
          system(comStr.str().c_str());
          chdir("..");
          comStr.clear();
          comStr.str("");
          comStr << "rm -rf " << dirStr.str();
          system(comStr.str().c_str());
        //////////////////////////
        }    
      }
    }
  }

  void GenerateRDF(){

    int numberOfParticles = 0;
    std::vector<int>::iterator npi = packInput.numberOfParticles.begin();
    while(npi != packInput.numberOfParticles.end())
      numberOfParticles += *npi++;
    //    std::cout << std::endl << "     Generating pack statistics for " << numberOfParticles
    //                << " particles." << std::endl;
      
    //command to call rdfgen (using path from cmake)
    std::string command = RDFGENCOMMAND + std::string(" < ") + packInput.OutputFileName()  
      + std::string(" > ") + packInput.OutputFileName() + std::string("_rdf.out");
    system(command.c_str());
  }
private:
  std::string my_window_name; /// Tracks *this* window name.
  int spherePackStatus;
  packir_input_data packInput;
};

/// 
/// @brief C/C++ bindings to load COMTESTMOD
///
extern "C" void packir_load_module( const char *name) {
  PackIR::Load(name);
}
extern "C" void PackIR_load_module( const char *name) {
  PackIR::Load(name);
}
extern "C" void PACKIR_LOAD_MODULE( const char *name) {
  PackIR::Load(name);
}
extern "C" void PACKIR_LOAD_MODULE_( const char *name) {
  PackIR::Load(name);
}
extern "C" void packir_load_module_( const char *name) {
  PackIR::Load(name);
}
///
/// @brief C/C++ bindings to unload COMTESTMOD
///
extern "C" void packir_unload_module( const char *name){
  PackIR::Unload(name);
}
extern "C" void packir_unload_module_( const char *name){
  PackIR::Unload(name);
}
extern "C" void PackIR_unload_module( const char *name){
  PackIR::Unload(name);
}
extern "C" void PACKIR_UNLOAD_MODULE( const char *name){
  PackIR::Unload(name);
}
extern "C" void PACKIR_UNLOAD_MODULE_( const char *name){
  PackIR::Unload(name);
}
