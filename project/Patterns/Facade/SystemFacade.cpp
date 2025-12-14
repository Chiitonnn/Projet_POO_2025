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
                                                           const std::string& email,
                                                           Role role) {
    auto utilisateur = std::make_shared<Utilisateur>(nextUserId_++, nom, email, role);
    utilisateurs_[utilisateur->getId()] = utilisateur;
    
    gestionnaireNotifications_->abonner(utilisateur, "TOUS");
    
    gestionnaireNotifications_->notifier("UTILISATEUR_CREE",
                                        "Utilisateur '" + nom + "' cree (role: " + 
                                        to_string(role) + ")");
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
                                            "Utilisateur '" + it->second->getNom() + "' supprime");
        
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
                                        "Tableau '" + nom + "' cree par " + createur->getNom());
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
                                            "Tableau '" + it->second->getNom() + "' supprime");
        tableaux_.erase(it);
        return true;
    }
    return false;
}

// Méthodes avec vérification de permissions
std::shared_ptr<Tableau> SystemFacade::creerTableauAvecPermission(const std::string& nom, int createurId) {
    auto createur = getUtilisateur(createurId);
    if (!createur) {
        std::cout << "[ERREUR] Utilisateur non trouve\n";
        return nullptr;
    }
    
    if (!createur->peutCreerTableau()) {
        std::cout << "[ERREUR PERMISSION] " << createur->getNom() 
                  << " (role: " << to_string(createur->getRole()) 
                  << ") ne peut pas creer de tableau\n";
        return nullptr;
    }
    
    return creerTableau(nom, createurId);
}

bool SystemFacade::supprimerTableauAvecPermission(int tableauId, int utilisateurId) {
    auto utilisateur = getUtilisateur(utilisateurId);
    if (!utilisateur) {
        std::cout << "[ERREUR] Utilisateur non trouve\n";
        return false;
    }
    
    if (!utilisateur->peutSupprimerTableau()) {
        std::cout << "[ERREUR PERMISSION] " << utilisateur->getNom() 
                  << " (role: " << to_string(utilisateur->getRole()) 
                  << ") ne peut pas supprimer de tableau\n";
        return false;
    }
    
    return supprimerTableau(tableauId);
}

bool SystemFacade::ajouterMembreAvecPermission(int tableauId, int utilisateurId, int ajouteurId) {
    auto ajouteur = getUtilisateur(ajouteurId);
    if (!ajouteur) {
        std::cout << "[ERREUR] Ajouteur non trouve\n";
        return false;
    }
    
    if (!ajouteur->peutAjouterMembre()) {
        std::cout << "[ERREUR PERMISSION] " << ajouteur->getNom() 
                  << " (role: " << to_string(ajouteur->getRole()) 
                  << ") ne peut pas ajouter de membre\n";
        return false;
    }
    
    auto tableau = getTableau(tableauId);
    if (tableau) {
        tableau->ajouterMembre(utilisateurId);
        return true;
    }
    
    std::cout << "[ERREUR] Tableau non trouve\n";
    return false;
}

bool SystemFacade::assignerCarteAvecPermission(int carteId, int utilisateurId, int assigneurId) {
    auto assigneur = getUtilisateur(assigneurId);
    if (!assigneur) {
        std::cout << "[ERREUR] Assigneur non trouve\n";
        return false;
    }
    
    if (!assigneur->peutAssignerCarte()) {
        std::cout << "[ERREUR PERMISSION] " << assigneur->getNom() 
                  << " (role: " << to_string(assigneur->getRole()) 
                  << ") ne peut pas assigner de carte\n";
        return false;
    }
    
    // Note: Dans une version complète, on chercherait la carte ici
    std::cout << "[INFO] Permission accordee pour assigner carte " 
              << carteId << " a utilisateur " << utilisateurId << "\n";
    return true;
}

bool SystemFacade::creerCarteAvecPermission(int listeId, const std::string& titre, int createurId) {
    auto createur = getUtilisateur(createurId);
    if (!createur) {
        std::cout << "[ERREUR] Createur non trouve\n";
        return false;
    }
    
    if (!createur->peutCreerCarte()) {
        std::cout << "[ERREUR PERMISSION] " << createur->getNom() 
                  << " (role: " << to_string(createur->getRole()) 
                  << ") ne peut pas creer de carte\n";
        return false;
    }
    
    // Note: Dans une version complète, on créerait la carte ici
    std::cout << "[INFO] Permission accordee pour creer carte: " << titre << "\n";
    return true;
}

bool SystemFacade::deplacerCarte(int carteId, int nouvelleListeId, int nouvellePosition) {
    (void)nouvelleListeId;
    (void)nouvellePosition;
    
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("DEPLACEMENT_TENTATIVE",
                   "Tentative de deplacement carte " + std::to_string(carteId));
    return false;
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
                  << " | Email: " << utilisateur->getEmail() 
                  << " | Role: " << to_string(utilisateur->getRole()) << "\n";
    }
}

void SystemFacade::afficherTableaux() const {
    std::cout << "\n=== TABLEAUX (" << tableaux_.size() << ") ===\n";
    for (const auto& [id, tableau] : tableaux_) {
        std::cout << "ID: " << id << " | Nom: " << tableau->getNom() 
                  << " | Createur: " << tableau->getCreateurId() << "\n";
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

bool SystemFacade::utilisateurPeutCreerTableau(int utilisateurId) const {
    auto utilisateur = getUtilisateur(utilisateurId);
    return utilisateur && utilisateur->peutCreerTableau();
}

bool SystemFacade::utilisateurPeutSupprimerTableau(int utilisateurId) const {
    auto utilisateur = getUtilisateur(utilisateurId);
    return utilisateur && utilisateur->peutSupprimerTableau();
}

GestionnaireNotifications* SystemFacade::getGestionnaireNotifications() const {
    return gestionnaireNotifications_;
}