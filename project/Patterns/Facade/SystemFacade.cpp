#include "SystemFacade.hpp"
#include "../Factory/FabriqueCarteStandard.hpp"
#include <iostream>
#include <algorithm>

SystemFacade::SystemFacade()
    : nextUserId_(1), nextTableauId_(1), nextListeId_(1), nextCarteId_(1),
      gestionnaireNotifications_(GestionnaireNotifications::getInstance()) {
    fabriqueCarte_ = std::make_shared<FabriqueCarteStandard>();
}

std::shared_ptr<Utilisateur> SystemFacade::creerUtilisateur(const std::string& nom, 
                                                           const std::string& email) {
    auto utilisateur = std::make_shared<Utilisateur>(nextUserId_++, nom, email);
    utilisateurs_[utilisateur->getId()] = utilisateur;
    
    // Abonner l'utilisateur à tous les événements
    gestionnaireNotifications_->abonner(utilisateur, "TOUS");
    
    gestionnaireNotifications_->notifier("UTILISATEUR_CREE",
                                        "Utilisateur '" + nom + "' créé");
    return utilisateur;
}

std::shared_ptr<Utilisateur> SystemFacade::getUtilisateur(int id) const {
    auto it = utilisateurs_.find(id);
    return it != utilisateurs_.end() ? it->second : nullptr;
}

bool SystemFacade::supprimerUtilisateur(int id) {
    auto it = utilisateurs_.find(id);
    if (it != utilisateurs_.end()) {
        gestionnaireNotifications_->notifier("UTILISATEUR_SUPPRIME",
                                            "Utilisateur '" + it->second->getNom() + "' supprimé");
        
        // Désabonner l'utilisateur
        gestionnaireNotifications_->desabonner(it->second, "TOUS");
        
        utilisateurs_.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<Tableau> SystemFacade::creerTableau(const std::string& nom, int createurId) {
    auto createur = getUtilisateur(createurId);
    if (!createur) return nullptr;
    
    auto tableau = std::make_shared<Tableau>(nextTableauId_++, nom, createurId);
    tableaux_[tableau->getId()] = tableau;
    
    gestionnaireNotifications_->notifier("TABLEAU_CREE_SYSTEM",
                                        "Tableau '" + nom + "' créé par " + createur->getNom());
    return tableau;
}

std::shared_ptr<Tableau> SystemFacade::getTableau(int id) const {
    auto it = tableaux_.find(id);
    return it != tableaux_.end() ? it->second : nullptr;
}

bool SystemFacade::supprimerTableau(int id) {
    auto it = tableaux_.find(id);
    if (it != tableaux_.end()) {
        gestionnaireNotifications_->notifier("TABLEAU_SUPPRIME",
                                            "Tableau '" + it->second->getNom() + "' supprimé");
        tableaux_.erase(it);
        return true;
    }
    return false;
}

bool SystemFacade::deplacerCarte(int carteId, int nouvelleListeId, int nouvellePosition) {
    // Pour éviter les warnings "unused parameter"
    (void)nouvelleListeId;    // Indique au compilateur qu'on utilise le paramètre
    (void)nouvellePosition;   // Indique au compilateur qu'on utilise le paramètre
    
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("DEPLACEMENT_TENTATIVE",
                   "Tentative de deplacement carte " + std::to_string(carteId));
    return false; // Implémentation simplifiée
}

void SystemFacade::annulerDerniereCommande() {
    if (!historiqueCommandes_.empty()) {
        auto derniereCommande = historiqueCommandes_.back();
        derniereCommande->annuler();
        historiqueCommandes_.pop_back();
        
        gestionnaireNotifications_->notifier("COMMANDE_ANNULEE",
                                            "Derniere commande annulee");
    }
}

void SystemFacade::afficherUtilisateurs() const {
    std::cout << "\n=== UTILISATEURS (" << utilisateurs_.size() << ") ===\n";
    for (const auto& [id, utilisateur] : utilisateurs_) {
        std::cout << "ID: " << id << " | Nom: " << utilisateur->getNom()
                  << " | Email: " << utilisateur->getEmail() << "\n";
    }
}

void SystemFacade::afficherTableaux() const {
    std::cout << "\n=== TABLEAUX (" << tableaux_.size() << ") ===\n";
    for (const auto& [id, tableau] : tableaux_) {
        tableau->afficher();
    }
}

void SystemFacade::afficherNotificationsUtilisateur(int utilisateurId) const {
    auto utilisateur = getUtilisateur(utilisateurId);
    if (utilisateur) {
        utilisateur->afficherNotifications();
    } else {
        std::cout << "Utilisateur " << utilisateurId << " non trouve.\n";
    }
}

GestionnaireNotifications* SystemFacade::getGestionnaireNotifications() const {
    return gestionnaireNotifications_;
}