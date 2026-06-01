#ifndef HOME_FACADE_H_
#define HOME_FACADE_H_

#include "Device.h"
#include "DeviceFactory.h"
#include "Sensor.h"
#include <vector>
#include <memory>
#include <string>

class SmartHomeFacade{
    public:
        SmartHomeFacade();
        ~SmartHomeFacade();

        void  initializeEcosystem(const std::string& brandChoice);
        void startSensors();
        void stopSensors();

        void triggerMorningRoutine();
        void triggerEveningRoutine();
    private :
        std::unique_ptr<IEcosystemFactory> activeFactory_;

        std::vector<std::shared_ptr<Light>> lights_;
        std::vector<std::shared_ptr<Thermostat>>thermostats_;

        TemperatureSensor environmentSensor_;
};

#endif //HOME_FACADE_H_
