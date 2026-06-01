#include "../include/Logger.h"
#include "../include/DeviceFactory.h"
#include <thread>
#include <vector>
#include <string>
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
    LOG_INFO("=== Smart Home Central Hub Starting ===");

    // std::vector<std::thread> deviceThreads;

    // for(int i = 1; i <= 10; ++i){
    //     deviceThreads.push_back(std::thread(simulateDeviceActivity, i));
    // }

    // for(auto& t : deviceThreads){
    //     if(t.joinable()){
    //         t.join();
    //     }
    // }
    LOG_INFO("--- Setting up Downstairs (Google) ----");
    GoogleNestFactory googleEcosystem;
    provisionSmartRoom(googleEcosystem, "Living Room");

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    LOG_INFO("--- Setting up  Upstairs (Apple) ---");
    AppleHomeKitEcosystem appleEcosystem;
    provisionSmartRoom(appleEcosystem, "Master Bedroom");

    LOG_INFO("=== Smart Home  Central Hub Shutdown Complete ===");

    return 0;
}
