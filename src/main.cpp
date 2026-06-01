#include "../include/Logger.h"
#include "../include/DeviceFactory.h"
#include "../include/Sensor.h"
#include <thread>
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

    TemperatureSensor houseSensor;
    houseSensor.startSimulation();

    GoogleNestFactory googleEcosystem;
    auto livingRoomThermostat = googleEcosystem.createThermostat();

    AppleHomeKitEcosystem appleEcosystem;
    auto bedroomThermostat = appleEcosystem.createThermostat();

    houseSensor.attach(livingRoomThermostat);
    houseSensor.attach(bedroomThermostat);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    LOG_WARNING("MAIN THREAD: Destroying Bedroom Thermostat unexpectedly!");
    bedroomThermostat.reset();

    houseSensor.stopSimulation();
    LOG_INFO("=== Smart Home  Central Hub Shutdown Complete ===");

    return 0;
}
