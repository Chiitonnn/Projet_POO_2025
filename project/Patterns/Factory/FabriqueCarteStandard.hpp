#pragma once
#include "IFabriqueCarte.hpp"
#include "../../Core/Carte.hpp"

class FabriqueCarteStandard : public IFabriqueCarte {
public:
    std::shared_ptr<Carte> creerCarte(int id, const std::string& titre, const std::string& description = "") override;
};