#pragma once
#include <memory>
#include <string>
#include <map>
#include "../../Core/Tableau.hpp"
#include "../../Core/Utilisateur.hpp"
#include "../../Core/Role.hpp"
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
    std::shared_ptr<Utilisateur> creerUtilisateur(const std::string& nom, 
                                                  const std::string& email,
                                                  Role role = Role::MEMBRE);
    std::shared_ptr<Utilisateur> getUtilisateur(int id) const;
    bool supprimerUtilisateur(int id);
    
    // Gestion des tableaux (version standard)
    std::shared_ptr<Tableau> creerTableau(const std::string& nom, int createurId);
    std::shared_ptr<Tableau> getTableau(int id) const;
    bool supprimerTableau(int id);
    
    // Gestion avec permissions
    std::shared_ptr<Tableau> creerTableauAvecPermission(const std::string& nom, int createurId);
    bool supprimerTableauAvecPermission(int tableauId, int utilisateurId);
    bool ajouterMembreAvecPermission(int tableauId, int utilisateurId, int ajouteurId);
    bool assignerCarteAvecPermission(int carteId, int utilisateurId, int assigneurId);
    bool creerCarteAvecPermission(int listeId, const std::string& titre, int createurId);
    
    // Commandes
    bool deplacerCarte(int carteId, int nouvelleListeId, int nouvellePosition);
    void annulerDerniereCommande();
    
    // Affichage
    void afficherUtilisateurs() const;
    void afficherTableaux() const;
    void afficherNotificationsUtilisateur(int utilisateurId) const;
    
    // Vérification rapide
    bool utilisateurPeutCreerTableau(int utilisateurId) const;
    bool utilisateurPeutSupprimerTableau(int utilisateurId) const;
    
    // Gestionnaire de notifications
    GestionnaireNotifications* getGestionnaireNotifications() const;
};