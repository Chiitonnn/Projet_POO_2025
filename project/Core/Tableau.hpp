#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Utilisateur.hpp"
#include "Liste.hpp"

class Tableau {
private:
    int id_;
    std::string nom_;
    int createurId_; // ID du créateur
    std::vector<int> membresIds_; // IDs des membres
    std::vector<std::shared_ptr<Liste>> listes_;
    
public:
    Tableau(int id, std::string nom, int createurId);
    
    // Getters
    int getId() const;
    const std::string& getNom() const;
    int getCreateurId() const;
    const std::vector<int>& getMembresIds() const;
    const std::vector<std::shared_ptr<Liste>>& getListes() const;
    
    // Méthodes métier
    void ajouterMembre(int utilisateurId);
    void retirerMembre(int utilisateurId);
    std::shared_ptr<Liste> creerListe(const std::string& nom);
    bool supprimerListe(int listeId);
    
    // Affichage
    void afficher() const;
};