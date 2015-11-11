#ifndef __PACKIR_H__
#define __PACKIR_H__
#include "Parameters.H"

class packir_input_data : public IRAD::Util::Parameters
{
public:
  int runtimeHours;
  int runtimeMins;
  int runtimeSecs;
  bool doRestart;
  bool periodicDomain;
  int domainShape;
  double endTolerance;
  float  packingFraction;
  float  aspectRatio;
  float tempDivergence;
  float initialTemperature;
  float cylinderAspect;
  std::string logName;
  std::string packOut;
  std::string packIn;
  std::string colorIn;
  unsigned int randomSeed;
  unsigned int nParticleModes;
  unsigned int numberOfAngles;
  unsigned int visualizationFrequency;
  std::vector<int> numberOfParticles;
  std::vector<float> particleGrowthRates;
public:
  std::string InputFileName(){ return(packIn); };
  std::string OutputFileName(){ return(packOut); };
  std::string ColorFileName(){ return(colorIn); };
  int NumberOfAngles(){return(numberOfAngles);};
  int InitializeDefaults(){
    runtimeHours = 99;
    runtimeMins = 0;
    runtimeSecs = 0;
    packingFraction = .9;
    endTolerance = 1e-5;
    aspectRatio = 1.0;
    tempDivergence = 1.01;
    initialTemperature = 1000.0;
    randomSeed = 17;
    doRestart = false;
    periodicDomain = true;
    domainShape = 0;
    logName = "pack.log";
    packOut = "pack.out";
    packIn  = "pack.in";
    colorIn = "colors";
    nParticleModes = 1;
    numberOfParticles.resize(1,1000);
    particleGrowthRates.resize(1,1);
    numberOfAngles = 12;
    visualizationFrequency = 1.0;
    cylinderAspect = 1.5;
  }
  int ConfigureFromParams(){
    if(this->IsSet("HOURS")){
      runtimeHours = this->GetValue<int>("HOURS");
      if(runtimeHours < 0 || runtimeHours > 99) runtimeHours = 99;
    }
    if(this->IsSet("MINS")){
      runtimeMins = this->GetValue<int>("MINS");
      if(runtimeMins < 0 || runtimeMins > 99) runtimeMins = 99;
    }
    if(this->IsSet("SECS")){
      runtimeSecs = this->GetValue<int>("SECS");
      if(runtimeSecs < 0 || runtimeSecs > 99) runtimeSecs = 99;
    }
    if(this->IsSet("ENDTOL")){
      endTolerance = this->GetValue<double>("ENDTOL");
      if(endTolerance < 0) endTolerance = 1e-5;
    }
    if(this->IsSet("PACKING_FRACTION")){
      packingFraction = this->GetValue<float>("PACKING_FRACTION");
      if(packingFraction < 0) packingFraction = .9;
    }
    if(this->IsSet("RESTART"))
      doRestart = this->GetValue<bool>("RESTART");
    if(this->IsSet("PERIODIC"))
      periodicDomain = this->GetValue<bool>("PERIODIC");
    if(this->IsSet("DOMAIN_SHAPE")){
      domainShape = this->GetValue<int>("DOMAIN_SHAPE");
      if(domainShape > 2) domainShape = 0;
    }
    if(this->IsSet("DOMAIN_ASPECT_RATIO")){
      aspectRatio = this->GetValue<float>("DOMAIN_ASPECT_RATIO");
      if(aspectRatio < 0) aspectRatio = 1.0;
    }
    if(this->IsSet("CYLINDER_ASPECT_RATIO")){
      cylinderAspect = this->GetValue<float>("CYLINDER_ASPECT_RATIO");
      if(cylinderAspect < 0) cylinderAspect = 1.0;
    }
    if(this->IsSet("TEMPERATURE")){
      initialTemperature = this->GetValue<float>("TEMPERATURE");
      if(initialTemperature < 0) initialTemperature = 1000.0;
    }
    if(this->IsSet("RANDOMSEED"))
      randomSeed = this->GetValue<unsigned int>("RANDOMSEED");
    if(this->IsSet("TEMPERATURE_DIVERGENCE")){
      tempDivergence = this->GetValue<float>("TEMPERATURE_DIVERGENCE");
      if(tempDivergence < 1.0) tempDivergence = 1.01;
    }
    if(this->IsSet("LOGNAME"))
      logName                   = this->GetValue<std::string>("LOGNAME");
    if(this->IsSet("PACKOUT"))
      packOut                   = this->GetValue<std::string>("PACKOUT");
    if(this->IsSet("PACKIN")) 
      packIn                    = this->GetValue<std::string>("PACKIN");
    if(this->IsSet("NMODES")){
      nParticleModes            = this->GetValue<unsigned int>("NMODES");
      if(nParticleModes < 1) nParticleModes = 1;
    } 
    if(this->IsSet("COLORFILE"))
      colorIn                   = this->GetValue<std::string>("COLORFILE");
    if(this->IsSet("NUMBER_OF_ANGLES"))
      numberOfAngles            = this->GetValue<unsigned int>("NUMBER_OF_ANGLES");
    if(this->IsSet("VISUALIZATION_FREQUENCY")){
      visualizationFrequency    = this->GetValue<float>("VISUALIZATION_FREQUENCY");
      if(visualizationFrequency < 0) visualizationFrequency = 1.0;
    }
    if(this->IsSet("NUMBER_OF_PARTICLES"))
      numberOfParticles         = this->GetValueVector<int>("NUMBER_OF_PARTICLES");
    if(this->IsSet("PARTICLE_GROWTH_RATES"))
      particleGrowthRates       = this->GetValueVector<float>("PARTICLE_GROWTH_RATES");
    if((numberOfParticles.size() != nParticleModes)){
      std::cerr << "packir_input_data::ConfigureFromParameters:Error: NUMBER_OF_PARTICLES "
                << "must be specified for each mode." << std::endl;
      return(1);
    }
    int nGrowthRates = particleGrowthRates.size();
    if((nGrowthRates > 1) && (nGrowthRates < nParticleModes))
      std::cerr << "packir_input_data::ConfigureFromParameters:Error: PARTICLE_GROWTH_RATES "
                << "must be specified for each mode." << std::endl;
  }

  int CreateSpherePackInput(std::ostream &outStream){

    outStream << (runtimeHours < 10  ? "0" : "") << runtimeHours << ":" 
              << (runtimeMins  < 10  ? "0" : "") << runtimeMins  << ":" 
              << (runtimeSecs  < 10  ? "0" : "") << runtimeSecs  
              << "\t\t! RUNTIME (HOURS:MINS:SECS) " << std::endl
              << endTolerance << "\t\t! ENDTOL" << std::endl 
              << packingFraction << "\t\t! PACKING_FRACTION" << std::endl
              << doRestart << "\t\t! RESTART" << std::endl
              << periodicDomain << "\t\t! PERIODIC " << std::endl
              << domainShape << "\t\t! DOMAIN_SHAPE" << std::endl
              << aspectRatio << "\t\t! ASPECT_RATIO" << std::endl
              << initialTemperature << "\t\t! TEMPERATURE" << std::endl
              << randomSeed << "\t\t! RANDOMSEED" << std::endl
              << tempDivergence << "\t\t! TEMP_DIVERGENCE" << std::endl
              << logName << "\t\t! LOGNAME" << std::endl
              << packOut << "\t\t! PACKOUT" << std::endl
              << nParticleModes << "\t\t! NMODES" <<  std::endl;
    for(int i = 0; i < nParticleModes;i++){
      outStream << numberOfParticles[i] << " " << particleGrowthRates[i] 
                <<  "\t\t! NUMBER_OF_PARTICLES PARTICLE_GROWTH_RATES" 
                << std::endl;
    }
  }
};

#endif
