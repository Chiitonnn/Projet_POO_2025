#pragma once
#include <memory>
#include <string>

class Carte;

class IFabriqueCarte {
public:
    virtual ~IFabriqueCarte() = default;
    virtual std::shared_ptr<Carte> creerCarte(int id, const std::string& titre, const std::string& description = "") = 0;
};