#include "../include/DeviceFactory.h"
#include "../include/Logger.h"

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
};

//Factory implementation

std::unique_ptr<Light> GoogleNestFactory::createLight() {
    LOG_DEBUG("GoogleNestFactory manufacturing a NestLight.");
    return std::make_unique<NestLight>();
}
std::unique_ptr<Thermostat> GoogleNestFactory::createThermostat() {
    LOG_DEBUG("GoogleNestFactory manufacturing a NestThermostat.");
    return std::make_unique<NestThermostat>();
}
std::unique_ptr<Light> AppleHomeKitEcosystem::createLight() {
    LOG_DEBUG("AppleHomeKitFactory manufacturing an AppleLight.");
    return std::make_unique<AppleLight>();
}
std::unique_ptr<Thermostat>  AppleHomeKitEcosystem::createThermostat(){
    LOG_DEBUG("AppleHomeKitFactory manufacturing an AppleThermostat.");
     return std::make_unique<AppleThermostat>();
}
