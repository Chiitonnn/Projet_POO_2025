#pragma once
#include <string>
#include <map>

class IObservateur {
public:
    virtual ~IObservateur() = default;
    virtual void recevoirNotification(const std::string& type, const std::string& message) = 0;
};