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

COM_EXTERN_MODULE(PackIR);


int main(int argc, char *argv[]){

  COM_init( &argc, &argv);

  COM_LOAD_MODULE_STATIC_DYNAMIC( PackIR, "packer");

  int packHandle = COM_get_function_handle("packer.PackSpheres");
  if(packHandle < 0){
    std::cerr << "Error!  Could not get function handle for packer!" 
              << std::endl;
    return(1);
  }

  int setParamHandle = COM_get_function_handle("packer.SetParam");
  if(setParamHandle < 0){
    std::cerr << "Error! Could not get function handle for setting configuration parameters!"
              << std::endl;
    return(1);
  }
  
  std::string numberOfParticles("NUMBER_OF_PARTICLES");
  std::string numberOfParticals("5000");
  COM_call_function(setParamHandle,&numberOfParticles,&numberOfParticals);
  std::string packInName("PACKIN");
  std::string packInFile("new_pack.in");
  COM_call_function(setParamHandle,&packInName,&packInFile);
  std::string packOutName("PACKOUT");
  std::string packOutFile("new_pack.out");
  COM_call_function(setParamHandle,&packOutName,&packOutFile);

  COM_call_function(packHandle);
  
  COM_UNLOAD_MODULE_STATIC_DYNAMIC(PackIR, "packer");
  
  COM_finalize();
}
