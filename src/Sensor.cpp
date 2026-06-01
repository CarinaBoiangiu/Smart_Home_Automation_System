#include "../include/Sensor.h"
#include "../include/Logger.h"
#include <chrono>
#include <mutex>
#include <random>
#include <thread>

TemperatureSensor::TemperatureSensor() : currentTemperature_(22.0f), isRunning_(false){

}
TemperatureSensor::~TemperatureSensor(){
    stopSimulation();
}

void TemperatureSensor::attach(std::shared_ptr<IObserver> observer) {
    std::lock_guard<std::mutex> lock(observerMutex_);
    observer_.push_back(observer);
    LOG_DEBUG("Sensor: New observer attached.");
}
void  TemperatureSensor::notify(){
    std::lock_guard<std::mutex> lock(observerMutex_);

    for(auto it =  observer_.begin(); it !=observer_.end();){
        if(auto observerPtr = it->lock()){
            observerPtr->update(currentTemperature_);
            ++it;
        }else{
            LOG_WARNING("Sensor: Observer expired, removing from list.");
            it = observer_.erase(it);
        }
    }
}
void TemperatureSensor::startSimulation(){
    if(isRunning_) return;
    isRunning_ = true;
    LOG_INFO("Sensor: Background  thread starting.");
    sensorThreand_ =  std::thread(&TemperatureSensor::run, this);
}
void TemperatureSensor::stopSimulation(){
    if(isRunning_){
        isRunning_ = false;
        if(sensorThreand_.joinable()){
            sensorThreand_.join();
        }
        LOG_INFO("Sensor: Background thread stopped.");
    }
}

void  TemperatureSensor::run(){
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-3.0f, 3.0f);
    while(isRunning_){
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        currentTemperature_ += dist(rng);
        LOG_DEBUG("Sensor: Ambient temp updated to " + std::to_string(currentTemperature_) + "°C");
        notify();
    }
}
