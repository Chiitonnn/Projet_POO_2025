#pragma once
#include <string>

class ICommande {
public:
    virtual ~ICommande() = default;
    virtual void executer() = 0;
    virtual void annuler() = 0;
    virtual std::string getDescription() const = 0;
};