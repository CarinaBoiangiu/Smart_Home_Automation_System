#include "../include/DeviceFactory.h"
#include "../include/Logger.h"
#include <memory>
#include <string>

//Google  nest

class NestLight : public Light{
  public :
    void turnOn() override{
        LOG_INFO("Nest Light powered ON.");
    }
    void turnOff() override{
        LOG_INFO("Nest Light powered OFF");
    }
    std::string getName() const override{
        return "Google Nest Lightbulb ";
    }
    void setBrightness(int level) override{
        LOG_DEBUG("Nest Light brightness set to " + std::to_string(level) + "%");
    }
};

class NestThermostat : public Thermostat{
  public :
    void turnOn() override{
        LOG_INFO("Nest Thermostat HVAC powered ON.");
    }
    void turnOff() override{
        LOG_INFO("Nest Thermostat HVAC powered OFF");
    }
    std::string getName() const override{
        return "Google Nest Learning Thermostat ";
    }
    void setTemperature(float temp) override{
        LOG_INFO("Nest Thermostat adjusting target to " + std::to_string(temp) + " degrees.");
    }
    void update(float newTemperature) override{
        LOG_INFO("Nest Thermostat detected ambiet temp change to " + std::to_string(newTemperature)+ "°C");
        if(newTemperature < 18.0f){
            LOG_INFO("Nest: Too cold! Activating emergency heating.");
            turnOn();
        }else if(newTemperature > 25.0f){
            LOG_INFO("Nest: Too hot! Activating AC.");
            turnOff();
        }
    }
};

//Apple HomeKit
class AppleLight : public Light{
  public :
    void turnOn() override{
        LOG_INFO("Apple HomeKit Light smoothly transitioned ON.");
    }
    void turnOff() override{
        LOG_INFO("Apple HomeKit Light smoothly transitioned OFF.");
    }
    std::string getName() const override{
        return "Apple Smart LED";
    }
    void setBrightness(int level) override{
        LOG_DEBUG("Apple Light dimmed to " + std::to_string(level) + "% via Siri.");
    }
};

class AppleThermostat : public Thermostat{
  public :
    void turnOn() override{
       LOG_INFO("Apple HomeKit Climate Control active.");;
    }
    void turnOff() override{
        LOG_INFO("Apple HomeKit Climate Control inactive.");
    }
    std::string getName() const override{
        return "Apple iClimate";
    }
    void setTemperature(float temp) override{
        LOG_INFO("Apple Climate synchronized to " + std::to_string(temp) + " degrees.");
    }
    void update(float newTemperature) override{
        LOG_INFO("Apple iClimate sensor sync: " + std::to_string(newTemperature) + "°C");
        if(newTemperature < 20.0f){
            LOG_INFO("Apple: Optimal temp lost. Warming environment.");
            turnOn();
        }
    }
};

//Factory implementation

std::shared_ptr<Light> GoogleNestFactory::createLight() {
    LOG_DEBUG("GoogleNestFactory manufacturing a NestLight.");
    return std::make_shared<NestLight>();
}
std::shared_ptr<Thermostat> GoogleNestFactory::createThermostat() {
    LOG_DEBUG("GoogleNestFactory manufacturing a NestThermostat.");
    return std::make_shared<NestThermostat>();
}
std::shared_ptr<Light> AppleHomeKitEcosystem::createLight() {
    LOG_DEBUG("AppleHomeKitFactory manufacturing an AppleLight.");
    return std::make_shared<AppleLight>();
}
std::shared_ptr<Thermostat>  AppleHomeKitEcosystem::createThermostat(){
    LOG_DEBUG("AppleHomeKitFactory manufacturing an AppleThermostat.");
     return std::make_shared<AppleThermostat>();
}
