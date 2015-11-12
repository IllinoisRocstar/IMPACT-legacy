///
/// @file
/// @ingroup impact_group
/// @brief Main function of the test driver (in C/C++) for the test modules
/// @author Jessica Kress (jkress@ilrocstar.com)
/// @date May 1, 2014
/// 
/// This file serves as both a test and a simple example for implementing
/// a driver in C/C++. This driver loads and unloads two test modules: one
/// written in C/C++ and one written in Fortran.
///
#include "com.h"
#include "com_devel.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <fstream>

COM_EXTERN_MODULE(PackIR);


int main(int argc, char *argv[]){

  int runMode = 0;
  if(argv[1]){
    runMode = std::atoi(argv[1]);
  }

  MPI_Init(&argc,&argv);

  int nProc = 1;
  MPI_Comm_size(MPI_COMM_WORLD,&nProc);
  int myRank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

  COM_init( &argc, &argv);

  COM_LOAD_MODULE_STATIC_DYNAMIC( PackIR, "packer");

  int packHandle = COM_get_function_handle("packer.PackSpheres");
  if(packHandle < 0){
    std::cerr << "Error!  Could not get function handle for packer!" 
              << std::endl;
    return(1);
  }

  int setupHandle = COM_get_function_handle("packer.PackSetup");
  if(setupHandle < 0){
    std::cerr << "Error!  Could not get function handle for pack setup!" 
              << std::endl;
    return(1);
  }

  int setParamHandle = COM_get_function_handle("packer.SetParam");
  if(setParamHandle < 0){
    std::cerr << "Error! Could not get function handle for setting configuration parameters!"
              << std::endl;
    return(1);
  }
  
  int generateViewsHandle = COM_get_function_handle("packer.GenerateViews");
  if(generateViewsHandle < 0){
    std::cerr << "Error! Could not get function handle for generating pack renderings!"
              << std::endl;
    return(1);
  }

  int generateRDFHandle = COM_get_function_handle("packer.GenerateRDF");
  if(generateRDFHandle < 0){
    std::cerr << "Error! Could not get function handle for generating pack RDF!"
              << std::endl;
    return(1);
  }

  std::string numberOfParticles("NUMBER_OF_PARTICLES");
  std::string numberOfParticals("1000");
  std::string endTolName("ENDTOL");
  std::string packingFractionName("PACKING_FRACTION");
  std::string endTol("1e-3");
  std::string packingFraction(".5");
  std::string packInName("PACKIN");
  std::string packOutName("PACKOUT");
  std::string packLogName("LOGNAME");
  std::string randomSeedName("RANDOMSEED");

  COM_call_function(setParamHandle,&numberOfParticles,&numberOfParticals);
  COM_call_function(setParamHandle,&endTolName,&endTol);
  COM_call_function(setParamHandle,&packingFractionName,&packingFraction);


  if(runMode == 0){   // Parallel over image generation of single pack

    // std::string packInFile("pack.in");
    // COM_call_function(setParamHandle,&packInName,&packInFile);
    // std::string packOutFile("pack.out");
    // COM_call_function(setParamHandle,&packOutName,&packOutFile);
    
    if(myRank == 0)
      COM_call_function(packHandle);
    else
      COM_call_function(setupHandle);
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    int nAngles = nProc;
    int whichAngle = myRank;
    COM_call_function(generateViewsHandle,&nAngles,&whichAngle);
    
    // Generate RDF for single pack on one processor
    if(myRank == 0)
      COM_call_function(generateRDFHandle);
  } else if (runMode == 1){

    std::ostringstream packIn;
    std::ostringstream packOut;
    std::ostringstream logOut;
    packIn << "pack_" << myRank << ".in";
    packOut << "pack_" << myRank << ".out";
    logOut << "pack_" << myRank << ".log";
    std::string packInFile(packIn.str());
    COM_call_function(setParamHandle,&packInName,&packInFile);
    std::string packOutFile(packOut.str());
    COM_call_function(setParamHandle,&packOutName,&packOutFile);
    std::string logOutFile(logOut.str());
    COM_call_function(setParamHandle,&packLogName,&logOutFile);

    int randomSeed = 17 - 100*myRank;
    std::ostringstream randomSeedStr;
    randomSeedStr << randomSeed;
    std::string randomSeedVal(randomSeedStr.str());
    COM_call_function(setParamHandle,&randomSeedName,&randomSeedVal);
    COM_call_function(packHandle);
    COM_call_function(generateRDFHandle);

    MPI_Barrier(MPI_COMM_WORLD);
    
    if(myRank == 0){
      std::vector<float> positions;
      std::vector<float> rdfvals;
      std::ifstream myRDFInFile;
      std::string myRDFName(packOutFile+"_rdf.out");
      myRDFInFile.open(myRDFName.c_str());
      float position;
      float value;
      while(myRDFInFile >> position >> value){
        positions.push_back(position);
        rdfvals.push_back(value);
      }
      myRDFInFile.close();
      for(int i = 1; i < nProc;i++){
        std::ifstream rankRDFInFile;
        std::ostringstream rankRDFStr;
        rankRDFStr << "pack_" << i << ".out_rdf.out";
        rankRDFInFile.open(rankRDFStr.str().c_str());
        int nPos = 0;
        while(rankRDFInFile >> position >> value){
          rdfvals[nPos++] += value;
        }
        rankRDFInFile.close();
      }
      std::ofstream rdfOutFile;
      rdfOutFile.open("composite_rdf.out");
      std::vector<float>::iterator rdfPosIt = positions.begin();
      std::vector<float>::iterator rdfValIt = rdfvals.begin();
      float fac = 1.0/((float)nProc);
      while(rdfValIt != rdfvals.end())
        rdfOutFile << *rdfPosIt++ << " " << fac*(*rdfValIt++) << std::endl;
      rdfOutFile.close();
    }
  }




  COM_UNLOAD_MODULE_STATIC_DYNAMIC(PackIR, "packer");
  
  COM_finalize();

  MPI_Finalize();
}
