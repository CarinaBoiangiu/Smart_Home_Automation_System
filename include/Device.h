#ifndef DEVICE_H_
#define DEVICE_H_

#include "Observer.h"
#include <string>

class Device{
    public:
        virtual ~Device() = default;
        virtual void turnOn() = 0;
        virtual void turnOff() = 0;
        virtual  std::string getName() const = 0;
};

class Light : public Device{
    public:
        virtual void setBrightness(int level) = 0;
};

class Thermostat : public Device, public IObserver{
    public:
        virtual  void setTemperature(float temp) = 0;
};


#endif //DEVICE_H_
