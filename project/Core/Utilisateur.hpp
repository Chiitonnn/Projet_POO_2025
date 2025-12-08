#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Patterns/Observer/IObservateur.hpp"

class Tableau;

class Utilisateur : public IObservateur {
private:
    int id_;
    std::string nom_;
    std::string email_;
    std::vector<int> tableaux_; // IDs des tableaux où l'utilisateur est membre
    std::vector<std::string> notifications_;

public:
    Utilisateur(int id, std::string nom, std::string email);
    
    // Getters
    int getId() const;
    const std::string& getNom() const;
    const std::string& getEmail() const;
    const std::vector<int>& getTableaux() const;
    const std::vector<std::string>& getNotifications() const;
    
    // Setters
    void setNom(const std::string& n);
    void setEmail(const std::string& e);
    
    // Méthodes métier
    void rejoindreTableau(int tableauId);
    void quitterTableau(int tableauId);
    
    // Implémentation de IObservateur
    void recevoirNotification(const std::string& type, const std::string& message) override;
    
    // Affichage
    void afficherNotifications() const;
};