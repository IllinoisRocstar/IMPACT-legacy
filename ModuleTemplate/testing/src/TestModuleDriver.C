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

COM_EXTERN_MODULE( ApplicationModule);


int main(int argc, char *argv[]){

  COM_init( &argc, &argv);

  COM_LOAD_MODULE_STATIC_DYNAMIC( ApplicationModule, "packer");

  int packHandle = COM_get_function_handle("packer.Execute");
  if(packHandle < 0){
    std::cerr << "Error!  Could not get function handle for packer!" 
              << std::endl;
  }
  COM_CALL_FUNCTION(packHandle);
  
  COM_UNLOAD_MODULE_STATIC_DYNAMIC( ApplicationModule, "packer");
  
  COM_finalize();
}
