#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <memory>

class IObserver{
    public:
        virtual ~IObserver() = default;
        virtual void  update(float newTemperature) = 0;
};

class ISuject{
    public:
        virtual ~ISuject() = default;
        virtual void  attach(std::shared_ptr<IObserver> observer) = 0;
        virtual void notify() = 0;
};

#endif
