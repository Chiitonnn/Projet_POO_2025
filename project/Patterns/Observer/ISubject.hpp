// Patterns/Observer/ISubject.hpp
#pragma once
#include <memory>
#include "IObserver.hpp"

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void subscribe(std::shared_ptr<IObserver> o) = 0;
    virtual void unsubscribe(std::shared_ptr<IObserver> o) = 0;
    virtual void publish(const std::string& event) = 0;
};
