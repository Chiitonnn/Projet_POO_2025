#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Carte.hpp"

class Liste {
private:
    int id_;
    std::string nom_;
    int position_;
    std::vector<std::shared_ptr<Carte>> cartes_;
    
public:
    Liste(int id, std::string nom, int position);
    
    // Getters
    int getId() const;
    const std::string& getNom() const;
    int getPosition() const;
    const std::vector<std::shared_ptr<Carte>>& getCartes() const;
    
    // Setters
    void setNom(const std::string& n);
    void setPosition(int position);
    
    // Méthodes métier
    std::shared_ptr<Carte> ajouterCarte(const std::string& titre);
    bool deplacerCarte(int carteId, int nouvellePosition);
    bool supprimerCarte(int carteId);
    
    // Affichage
    void afficher() const;
};