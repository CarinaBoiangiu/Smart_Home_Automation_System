#include "../include/Logger.h"
#include "../include/HomeFacade.h"
#include <thread>
#include <chrono>


//Test after  implement DeviceFactory
void provisionSmartRoom(IEcosystemFactory& factory, const std::string& roomName){
    LOG_INFO("Provisioning devices for " + roomName);
    auto roomLight =  factory.createLight();
    auto roomThermostat = factory.createThermostat();

    roomLight->turnOn();
    roomLight->setBrightness(80);

    roomThermostat->turnOn();
    roomThermostat->setTemperature(22.5f);
}

//Test logger
void simulateDeviceActivity(int deviceId){
    LOG_INFO("Device " + std::to_string(deviceId) + " booting up...");
    std::this_thread::sleep_for(std::chrono::milliseconds(15));

    if(deviceId % 2 == 0){
        LOG_WARNING("Device " + std::to_string(deviceId) + " experiencing high latency.");
    }else{
        LOG_DEBUG("Device " + std::to_string(deviceId) + " ping successful.");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    LOG_INFO("Device " + std::to_string(deviceId) + " entering sleep mode.");
}


int main(){
    Logger::getInstance().setLogFile("smarthone.log");
    LOG_INFO("=== System Boot ===");

    SmartHomeFacade myHouse;

    myHouse.initializeEcosystem("Apple");
    myHouse.startSensors();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    myHouse.triggerMorningRoutine();

    std::this_thread::sleep_for(std::chrono::seconds(4));

    myHouse.triggerEveningRoutine();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    myHouse.stopSensors();
    LOG_INFO("=== System Shutdown ===");

    return 0;
}
