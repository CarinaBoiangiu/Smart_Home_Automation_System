#include "../include/HomeFacade.h"
#include "../include/Logger.h"
#include <algorithm>
#include <memory>

SmartHomeFacade::SmartHomeFacade(){
    LOG_INFO("Facade: Smart Home interface initialized.");
}
SmartHomeFacade::~SmartHomeFacade(){
    stopSensors();
    LOG_INFO("Facade: Smart Home interface destroyed.");
}

void  SmartHomeFacade::initializeEcosystem(const std::string& brandChoice){
    LOG_INFO("Facade: Configuring home for " + brandChoice + " ecosystem...");

    if(brandChoice == "Google"){
        activeFactory_ = std::make_unique<GoogleNestFactory>();
    }else if(brandChoice == "Apple"){
        activeFactory_ = std::make_unique<AppleHomeKitEcosystem>();
    }else{
        LOG_ERROR("Facade: Unknown ecosystem brand.");
        return;
    }

    lights_.push_back(activeFactory_->createLight());
    lights_.push_back(activeFactory_->createLight());

    auto mainThermostat = activeFactory_->createThermostat();
    thermostats_.push_back(mainThermostat);

    environmentSensor_.attach(mainThermostat);
    LOG_INFO("Facade: Initialization complete. 2 Lights, 1 Thermostat online.");
}
void SmartHomeFacade::startSensors(){
    environmentSensor_.startSimulation();
}
void SmartHomeFacade::stopSensors(){
    environmentSensor_.stopSimulation();
}

void SmartHomeFacade::triggerMorningRoutine(){
    LOG_INFO("--- Executing Morning Routine ---");
    for(auto& light : lights_){
        light->turnOn();
        light->setBrightness(100);
    }
    for(auto& thermostat : thermostats_){
        thermostat->setTemperature(22.0f);
    }
}
void SmartHomeFacade::triggerEveningRoutine(){
    LOG_INFO("--- Executing Evening Routine ---");
    for(auto& light : lights_){
        light->setBrightness(20);
    }
    for(auto& thermostat : thermostats_){
        thermostat->setTemperature(18.5f);
    }
}
