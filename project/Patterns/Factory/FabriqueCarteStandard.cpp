#include "FabriqueCarteStandard.hpp"
#include <iostream>

std::shared_ptr<Carte> FabriqueCarteStandard::creerCarte(int id, const std::string& titre, 
                                                        const std::string& description) {
    std::cout << "[FABRIQUE] Creation carte standard: " << titre << std::endl;
    return std::make_shared<Carte>(id, titre, description);
}