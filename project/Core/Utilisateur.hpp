#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Patterns/Observer/IObservateur.hpp"
#include "Role.hpp"

class Tableau;

class Utilisateur : public IObservateur {
private:
    int id_;
    std::string nom_;
    std::string email_;
    Role role_;
    std::vector<int> tableaux_;
    std::vector<std::string> notifications_;

public:
    Utilisateur(int id, std::string nom, std::string email, Role role = Role::MEMBRE);
    
    // Getters
    int getId() const;
    const std::string& getNom() const;
    const std::string& getEmail() const;
    Role getRole() const;
    const std::vector<int>& getTableaux() const;
    const std::vector<std::string>& getNotifications() const;
    
    // Setters
    void setNom(const std::string& n);
    void setEmail(const std::string& e);
    void setRole(Role r);
    
    // Méthodes métier
    void rejoindreTableau(int tableauId);
    void quitterTableau(int tableauId);
    
    // Implémentation de IObservateur
    void recevoirNotification(const std::string& type, const std::string& message) override;
    
    // Affichage
    void afficherNotifications() const;
    
    // Méthodes de vérification de permissions
    bool peutCreerTableau() const;
    bool peutSupprimerTableau() const;
    bool peutModifierTableau() const;
    bool peutAjouterMembre() const;
    bool peutAssignerCarte() const;
    bool peutCreerCarte() const;
    bool peutSupprimerCarte() const;
    bool estAdmin() const;
    bool estMembre() const;
    bool estObservateur() const;
};