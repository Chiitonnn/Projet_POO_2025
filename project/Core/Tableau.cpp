#include "Tableau.hpp"
#include "../Patterns/Observer/GestionnaireNotifications.hpp"
#include <iostream>
#include <algorithm>

Tableau::Tableau(int id, std::string nom, int createurId)
    : id_(id), nom_(std::move(nom)), createurId_(createurId) {
    membresIds_.push_back(createurId);
    
    // Notifier la création du tableau
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("TABLEAU_CREE", 
                   "Tableau '" + nom_ + "' cree par l'utilisateur " + std::to_string(createurId));
}

int Tableau::getId() const { return id_; }
const std::string& Tableau::getNom() const { return nom_; }
int Tableau::getCreateurId() const { return createurId_; }
const std::vector<int>& Tableau::getMembresIds() const { return membresIds_; }
const std::vector<std::shared_ptr<Liste>>& Tableau::getListes() const { return listes_; }

void Tableau::ajouterMembre(int utilisateurId) {
    if (std::find(membresIds_.begin(), membresIds_.end(), utilisateurId) == membresIds_.end()) {
        membresIds_.push_back(utilisateurId);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("MEMBRE_AJOUTE",
                       "Utilisateur " + std::to_string(utilisateurId) + 
                       " a rejoint le tableau '" + nom_ + "'");
    }
}

void Tableau::retirerMembre(int utilisateurId) {
    if (utilisateurId == createurId_) return; // Ne pas retirer le créateur
    
    auto it = std::find(membresIds_.begin(), membresIds_.end(), utilisateurId);
    if (it != membresIds_.end()) {
        membresIds_.erase(it);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("MEMBRE_RETIRE",
                       "Utilisateur " + std::to_string(utilisateurId) + 
                       " a quitte le tableau '" + nom_ + "'");
    }
}

std::shared_ptr<Liste> Tableau::creerListe(const std::string& nom) {
    static int nextListeId = 1;
    auto liste = std::make_shared<Liste>(nextListeId++, nom, static_cast<int>(listes_.size()));
    listes_.push_back(liste);
    
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("LISTE_CREEE",
                   "Liste '" + nom + "' creee dans le tableau '" + nom_ + "'");
    
    return liste;
}

bool Tableau::supprimerListe(int listeId) {
    auto it = std::find_if(listes_.begin(), listes_.end(),
                          [listeId](const auto& liste) { return liste->getId() == listeId; });
    
    if (it != listes_.end()) {
        auto nomListe = (*it)->getNom();
        listes_.erase(it);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("LISTE_SUPPRIMEE",
                       "Liste '" + nomListe + "' supprimee du tableau '" + nom_ + "'");
        return true;
    }
    return false;
}

void Tableau::afficher() const {
    std::cout << "\n=== Tableau: " << nom_ << " ===\n";
    std::cout << "Createur: " << createurId_ << "\n";
    std::cout << "Membres (" << membresIds_.size() << "): ";
    for (int id : membresIds_) std::cout << id << " ";
    std::cout << "\n";
    
    std::cout << "\nListes (" << listes_.size() << "):\n";
    for (const auto& liste : listes_) {
        liste->afficher();
    }
    std::cout << "==========================\n";
}