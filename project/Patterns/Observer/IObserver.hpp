// Patterns/Observer/IObserver.hpp
#pragma once
#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void notify(const std::string& event) = 0;
};
