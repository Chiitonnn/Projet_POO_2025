#pragma once
#include <memory>
#include <string>
#include <map>
#include "../../Core/Tableau.hpp"
#include "../../Core/Utilisateur.hpp"
#include "../../Patterns/Command/ICommande.hpp"
#include "../../Patterns/Factory/IFabriqueCarte.hpp"
#include "../../Patterns/Observer/GestionnaireNotifications.hpp"

class SystemFacade {
private:
    std::map<int, std::shared_ptr<Utilisateur>> utilisateurs_;
    std::map<int, std::shared_ptr<Tableau>> tableaux_;
    std::shared_ptr<IFabriqueCarte> fabriqueCarte_;
    std::vector<std::shared_ptr<ICommande>> historiqueCommandes_;
    int nextUserId_;
    int nextTableauId_;
    int nextListeId_;
    int nextCarteId_;
    
    GestionnaireNotifications* gestionnaireNotifications_;
    
public:
    SystemFacade();
    
    // Gestion des utilisateurs
    std::shared_ptr<Utilisateur> creerUtilisateur(const std::string& nom, const std::string& email);
    std::shared_ptr<Utilisateur> getUtilisateur(int id) const;
    bool supprimerUtilisateur(int id);
    
    // Gestion des tableaux
    std::shared_ptr<Tableau> creerTableau(const std::string& nom, int createurId);
    std::shared_ptr<Tableau> getTableau(int id) const;
    bool supprimerTableau(int id);
    
    // Commandes
    bool deplacerCarte(int carteId, int nouvelleListeId, int nouvellePosition);
    void annulerDerniereCommande();
    
    // Affichage
    void afficherUtilisateurs() const;
    void afficherTableaux() const;
    void afficherNotificationsUtilisateur(int utilisateurId) const;
    
    // Gestionnaire de notifications
    GestionnaireNotifications* getGestionnaireNotifications() const;
};