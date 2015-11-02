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

#include "COMM.H"
//#include "FC.h"
#include "com.h"
#include "com_devel.hpp"
//#include "TestSolver.H"

namespace COM {
  /// Simple test function sets integer to 1.
  void IntFunction(int *io_data)
  {
    if(io_data)
      *io_data = 1;
  };

  /// Simple test function writes an integer to string
  void ConstIntFunction(const int *idata,void *string_data)
  {
    std::ostringstream Ostr;
    std::string *sdptr = static_cast<std::string *>(string_data);
    Ostr << *idata;
    sdptr->assign(Ostr.str());
  };
  
  ///
  /// @brief Test function for optional arguments
  ///
  /// This function tests the functionality of optional 
  /// arguments for registered functions. It will count the
  /// number of non-null arguments and sum their values. If
  /// the number of non-null arguments passed in does not match
  /// that specified by a0 on input, then -sum is returned. Otherwise
  /// the sum will be returned in a0.
  ///
  /// @param a0 integer specifies number of optional arguments on input
  /// @returns a0 Sum of all non-null arguments, or -1 if error detected
  ///
  void OptionalArgsFunction(int *a0, int *a1,int *a2, int *a3, int *a4,
                            int *a5,int *a6, int *a7, int *a8,
                            int *a9,int *a10,int *a11, int *a12){
    int number_of_nonnull_arguments = 0;
    int nonnull_count = 0;
    if(a0)
      number_of_nonnull_arguments = *a0;
    else
      return;
    *a0 = 0;
    if(a1){
      nonnull_count++;
      *a0 += *a1;
    }
    if(a2){
      nonnull_count++;
      *a0 += *a2;
    }
    if(a3){
      nonnull_count++;
      *a0 += *a3;
    }
    if(a4){
      nonnull_count++;
      *a0 += *a4;
    }
    if(a5){
      nonnull_count++;
      *a0 += *a5;
    }
    if(a6){
      nonnull_count++;
      *a0 += *a6;
    }
    if(a7){
      nonnull_count++;
      *a0 += *a7;
    }
    if(a8){
      nonnull_count++;
      *a0 += *a8;
    }
    if(a9){
      nonnull_count++;
      *a0 += *a9;
    }
    if(a10){
      nonnull_count++;
      *a0 += *a10;
    }
    if(a11){
      nonnull_count++;
      *a0 += *a11;
    }
    if(a12){
      nonnull_count++;
      *a0 += *a12;
    }
    if(nonnull_count != number_of_nonnull_arguments)
      *a0 *= -1;
  }

  class ApplicationModuleTemplate : public COM_Object {
  public:

    /// Default constructor.
    ApplicationModuleTemplate(){
      my_window_name.erase();
    };
    
    ///
    /// @brief Destructor
    ///
    /// The destructor will destroy the externally loaded modules (if they exists)
    ///
    virtual ~ApplicationModuleTemplate()
    {
    };  


    ///
    /// @brief Hello COM World
    ///
    /// This function just prints a message:
    /// "Hello COM from my_window_name!"
    /// to stdout and to the string passed in.
    ///
    /// @param  string_data, int.
    /// @returns.
    void Function0F(char *string_data, int size)
    {
      std::cout << "Entering Function0F: " << std::endl
		<< "Size = " << size << std::endl;
      std::ostringstream Ostr;
      Ostr << "Hello COM from " << my_window_name << "!";
      std::string::size_type x=Ostr.str().size();
      if(x > size)
        x = size;
      strncpy(string_data, Ostr.str().c_str(), x);
      std::cout << string_data << std::endl;
    };

    ///
    /// @brief Hello COM World
    ///
    /// This function just prints a message:
    /// "Hello COM from my_window_name!"
    /// to stdout and to the string passed in.
    ///
    /// @param string_data A pointer to a std::string object.
    /// @returns string_data set to the message.
    void Function0(void *string_data)
    {
      std::string *output_string = static_cast<std::string *>(string_data);
      std::ostringstream Ostr;
      Ostr << "Hello COM from " << my_window_name << "!";
      output_string->assign(Ostr.str());
      std::cout << *output_string << std::endl;
    };


    ///
    /// @brief Function that increments an integer
    ///
    /// @param an integer
    ///
    /// This function simply increments the value of
    /// the integer passed in to it.
    void Increment(int *i, int *rank)

    {
      *i+=*rank;
    };


    ///
    /// @brief Function that sleeps for the number of seconds of its process rank
    ///
    /// @param
    ///
    /// This function simply sleeps for the number of seconds of its process rank
    void SleepMultiply(int *mult)

    {
      sleep((*mult));
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
          std::cerr << "ApplicationModuleTemplate::InitModule:Error: Could not open configuration file, "
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


    ///
    /// @brief Step the dummy solver through time
    ///
    /// This function steps the dummy solver and sets up
    /// periodic solutions on the grid. time is advanced
    /// by delta_t.
    ///
    void Execute()
    {
      spherePackStatus = system("spherepack pack.in");
    };

    ///
    /// @brief 
    /// 
    /// This function ...
    void get_communicator_module( int *commworks)
    {
      const char *comm_name = "TestParallelWin1";
      typedef IRAD::Comm::CommunicatorObject CommType;
      CommType _communicator;
      bool getcommunicator = true;
      MPI_Comm comm, default_comm;
      COM_get_communicator(comm_name, &comm);
      default_comm = COM_get_default_communicator();

      if(comm != MPI_COMM_SELF){
        _communicator.SetErr(1);
        std::cout << "COM_get_communicator does not return the communicator"
                  << " used by set_default_communicator!" << std::endl;
      }
      *commworks = 1;

      if(_communicator.Check()){
        //getcommunicator = false;
        *commworks = 0;
      }
      std::cout << "Getcommunicator output:  " << getcommunicator << std::endl;
      _communicator.ClearErr();

    };
    
    ///
    /// @brief "Loads" the C++ ApplicationModuleTemplate
    ///
    /// This function creates an instance of a COM::ApplicationModuleTemplate object,
    /// creates a new Window with the specified name and registers the
    /// address of the new COM::ApplicationModuleTemplate object as the ".global"
    /// DataItem of the Window. This registers the C++ COM::ApplicationModuleTemplate
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
      std::cout << "Loading ApplicationModuleTemplate with name " << name 
                << "." << std::endl;

      ApplicationModuleTemplate *test_module_pointer = new ApplicationModuleTemplate();
      COM_new_window(name);
      test_module_pointer->my_window_name = name;
      std::string global_name(name+".global");
      COM_new_dataitem(global_name.c_str(),'w',COM_VOID,1,"");
      COM_set_object(global_name.c_str(),0,test_module_pointer);

      std::vector<COM_Type> types(13,COM_INT);
    
      types[0] = COM_RAWDATA;
      types[1] = COM_STRING;

      COM_set_member_function( (name+".Function0F").c_str(), 
                               (Member_func_ptr)(&ApplicationModuleTemplate::Function0F), 
                               global_name.c_str(), "bbi", &types[0]);
 
      types[1] = COM_VOID;
      COM_set_member_function( (name+".Function0").c_str(), 
                               (Member_func_ptr)(&ApplicationModuleTemplate::Function0), 
                               global_name.c_str(), "bb", &types[0]);
    
      COM_set_member_function( (name+".InitApplication").c_str(), 
                               (Member_func_ptr)(&ApplicationModuleTemplate::InitApplication), 
                               global_name.c_str(), "bi", &types[0]);
    
      COM_set_member_function( (name+".Execute").c_str(), 
                               (Member_func_ptr)(&ApplicationModuleTemplate::Execute), 
                               global_name.c_str(), "b", &types[0]);
      types[1] = COM_INT;
      COM_set_member_function( (name+".get_communicator_module").c_str(),
                               (Member_func_ptr)(&ApplicationModuleTemplate::get_communicator_module),
                               global_name.c_str(), "bb", &types[0]);

      types[1] = COM_INT;     
      types[2] = COM_INT;
      COM_set_member_function( (name+".Increment").c_str(), 
                               (Member_func_ptr)(&ApplicationModuleTemplate::Increment), 
                               global_name.c_str(), "bbi", &types[0]);

      COM_set_member_function( (name+".SleepMultiply").c_str(), 
                               (Member_func_ptr)(&ApplicationModuleTemplate::SleepMultiply), 
                               global_name.c_str(), "bi", &types[0]);
 
      COM_set_function((name+".IntFunction").c_str(),
                       (Func_ptr)(&IntFunction),"b",&types[0]);
      
      COM_set_function((name+".ConstIntFunction").c_str(),
                       (Func_ptr)(&ConstIntFunction),"io",&types[0]);

      COM_set_function((name+".OptionalArgsFunction").c_str(),
                       (Func_ptr)(&OptionalArgsFunction),
                       "bIIIIIIIIIIII",&types[0]);

      COM_window_init_done(name);  
    }

    ///
    /// @brief Unloads the ApplicationModuleTemplate
    ///
    /// This function simply destroys the COM::ApplicationModuleTemplateObject created
    /// in the call to Load and then deletes the associated window with
    /// the specified name.
    ///
    static void Unload(const std::string &name){
      std::cout << "Unloading ApplicationModuleTemplate with name " << name 
                << "." << std::endl;
      ApplicationModuleTemplate *appModulePointer = NULL;
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

  private:
    std::string my_window_name; /// Tracks *this* window name.
    int spherePackStatus;
  };
}
  
// COM_Type types[5];

// types[0] = COM_RAWDATA;
// types[2] = COM_INT;
// types[1] = types[3] = types[4] = COM_METADATA;
// COM_set_member_function( (mname+".initialize").c_str(), 
// 			   (Member_func_ptr)(&Rocon::initialize), 
// 			   glb.c_str(), "bii", types);

// types[1] = COM_STRING;
// COM_set_member_function( (mname+".init_from_file").c_str(),
//       		   (Member_func_ptr)(&Rocon::init_from_file),
//       		   glb.c_str(),"bii", types);
// types[1] = COM_METADATA;
// types[2] = COM_METADATA;
// COM_set_member_function( (mname+".find_intersections").c_str(), 
// 			   (Member_func_ptr)(&Rocon::find_intersections), 
// 			   glb.c_str(), "biiob", types);
// COM_set_member_function( (mname+".constrain_displacements").c_str(), 
// 			   (Member_func_ptr)(&Rocon::constrain_displacements), 
// 			   glb.c_str(), "bibii", types);

// COM_set_member_function( (mname+".burnout").c_str(), 
// 			   (Member_func_ptr)(&Rocon::burnout), 
// 			   glb.c_str(), "biib", types);
  
// COM_set_member_function( (mname+".burnout_filter").c_str(), 
// 			   (Member_func_ptr)(&Rocon::burnout_filter), 
// 			   glb.c_str(), "bib", types);

/// 
/// @brief C/C++ bindings to load COMTESTMOD
///
extern "C" void COMTESTMOD_load_module( const char *name) {
  COM::ApplicationModuleTemplate::Load(name);
}
///
/// @brief C/C++ bindings to unload COMTESTMOD
///
extern "C" void COMTESTMOD_unload_module( const char *name){
  COM::ApplicationModuleTemplate::Unload(name);
}
