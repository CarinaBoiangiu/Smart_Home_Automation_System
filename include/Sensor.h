#ifndef SENSOR_H_
#define SENSOR_H_

#include "Observer.h"
#include <memory>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>

class TemperatureSensor : public ISuject{
    public:
        TemperatureSensor();
        ~TemperatureSensor();

        void attach(std::shared_ptr<IObserver> observer) override;
        void  notify() override;

        void startSimulation();
        void stopSimulation();

    private:
        void  run();

        std::vector<std::weak_ptr<IObserver>> observer_;
        std::mutex observerMutex_;

        float currentTemperature_;

        std::thread sensorThreand_;
        std::atomic<bool> isRunning_;
};


#endif //SENSOR_H_
