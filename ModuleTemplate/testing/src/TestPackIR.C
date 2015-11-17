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

void AverageRDFs(const std::string &packOutFile,int nProc,std::ostream &outStream);

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

  MPI_Bcast(&runMode,1,MPI_INT,0,MPI_COMM_WORLD);

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

  float packingFractionValue = .6;
  std::string numberOfParticles("NUMBER_OF_PARTICLES");
  std::string numberOfParticals("1000");
  std::string endTolName("ENDTOL");
  std::string packingFractionName("PACKING_FRACTION");
  std::string endTol("1e-3");
  std::ostringstream paramOut;
  paramOut << packingFractionValue;
  std::string packingFraction(paramOut.str());
  std::string packInName("PACKIN");
  std::string packOutName("PACKOUT");
  std::string packLogName("LOGNAME");
  std::string randomSeedName("RANDOMSEED");
  std::string restartName("RESTART");
  std::string YES("1");

  COM_call_function(setParamHandle,&numberOfParticles,&numberOfParticals);
  COM_call_function(setParamHandle,&endTolName,&endTol);
  COM_call_function(setParamHandle,&packingFractionName,&packingFraction);

  std::cout << myRank << ": RUN MODE " << runMode << std::endl;

  if(runMode == 0){   // Parallel over image generation of single pack
    
    COM_call_function(setupHandle);

    if(myRank == 0)
      COM_call_function(packHandle);
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    int nAngles = nProc;
    int whichAngle = myRank;
    std::string imFileName("pack");
    std::string packOut("pack.out");
    COM_call_function(generateViewsHandle,&nAngles,&whichAngle,&packOut,&imFileName);
    
    // Generate RDF for single pack on one processor
    if(myRank == 0)
      COM_call_function(generateRDFHandle,&packOut);
  } else if (runMode == 1){
    
    std::ostringstream packIn;
    std::ostringstream packOut;
    std::ostringstream logOut;
    packIn  << "pack_" << myRank << ".in";
    packOut << "pack_" << myRank << ".out";
    logOut  << "pack_" << myRank << ".log";
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
    COM_call_function(setupHandle);
    COM_call_function(packHandle);
    COM_call_function(generateRDFHandle,&packOutFile);
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    if(myRank == 0){
      std::ofstream rdfOutFile;
      rdfOutFile.open("composite_rdf.out");
      AverageRDFs(packOutFile,nProc,rdfOutFile);
      rdfOutFile.close();
    }
  } else if(runMode == 2) {
    float vizFrequency = .01;
    float currentPackingFraction = vizFrequency;
    int nViz = 0;
    while(currentPackingFraction <= packingFractionValue){

      nViz++;
      std::cout << myRank << ": Processing nViz = " << nViz << std::endl;

      std::ostringstream pfOut;
      pfOut << currentPackingFraction;
      std::string packFrac(pfOut.str());

      if(myRank == 0)
        std::cout << "Setting packing fraction to " << packFrac << std::endl;
      COM_call_function(setParamHandle,&packingFractionName,&packFrac);
      std::ostringstream packIn;
      std::ostringstream packOut;
      std::ostringstream logOut;
      packIn  << "pack_" << nViz << ".in";
      packOut << "pack_" << nViz << ".out";
      logOut  << "pack_" << nViz << ".log";
      std::string packInFile(packIn.str());
      COM_call_function(setParamHandle,&packInName,&packInFile);
      std::string packOutFile(packOut.str());
      COM_call_function(setParamHandle,&packOutName,&packOutFile);
      std::string logOutFile(logOut.str());
      COM_call_function(setParamHandle,&packLogName,&logOutFile);

      COM_call_function(setupHandle);

      if(myRank == 0)
        COM_call_function(packHandle);
     

      MPI_Barrier(MPI_COMM_WORLD);

      if(myRank){
        int nAngles = nProc - 1;
        int whichAngle = myRank - 1;
        std::ostringstream imFileOut;
        imFileOut << "pack_" << (nViz < 10 ? "0" : "")
                  << nViz;
        std::string imFileName(imFileOut.str());
        COM_call_function(generateViewsHandle,&nAngles,&whichAngle,&packOutFile,&imFileName);
      } else {
        std::ostringstream comOut;
        comOut << "cp " << packOutFile << " restart";
        system(comOut.str().c_str());
        COM_call_function(setParamHandle,&restartName,&YES);
      }
      currentPackingFraction += vizFrequency;
    }
  }

  COM_UNLOAD_MODULE_STATIC_DYNAMIC(PackIR, "packer");
  
  COM_finalize();

  MPI_Finalize();
}

void AverageRDFs(const std::string &packOutFile,int nProc,std::ostream &outStream)
{
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
  //  std::ofstream rdfOutFile;
  //  rdfOutFile.open("composite_rdf.out");
  std::vector<float>::iterator rdfPosIt = positions.begin();
  std::vector<float>::iterator rdfValIt = rdfvals.begin();
  float fac = 1.0/((float)nProc);
  while(rdfValIt != rdfvals.end())
    outStream << *rdfPosIt++ << " " << fac*(*rdfValIt++) << std::endl;
  //  rdfOutFile.close();
}
