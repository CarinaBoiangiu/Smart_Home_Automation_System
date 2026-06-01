#ifndef DEVICE_FACTORY_H_
#define DEVICE_FACTORY_H_

#include "Device.h"
#include <memory>

//The Abstract Factory Interface
class IEcosystemFactory{
    public:
        virtual ~IEcosystemFactory() = default;

        virtual std::shared_ptr<Light> createLight() = 0;
        virtual std::shared_ptr<Thermostat> createThermostat() = 0;

};

// Factory 1 :  GoogleNestFactory
class GoogleNestFactory : public IEcosystemFactory{
    public:
        std::shared_ptr<Light> createLight() override;
        std::shared_ptr<Thermostat> createThermostat() override;
};

//Factory 2 : Apple HomeKit Ecosystem
class AppleHomeKitEcosystem : public IEcosystemFactory{
    public:
        std::shared_ptr<Light> createLight() override;
        std::shared_ptr<Thermostat> createThermostat() override;
};

#endif //DEVICE_FACTORY_H_
