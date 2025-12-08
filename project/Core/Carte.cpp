#include "Carte.hpp"
#include "../Patterns/Observer/GestionnaireNotifications.hpp"
#include <iostream>
#include <algorithm>

Carte::Carte(int id, std::string titre, std::string description)
    : id_(id), titre_(std::move(titre)), description_(std::move(description)),
      status_(WorkflowStatus::TODO), position_(0) {}

int Carte::getId() const { return id_; }
const std::string& Carte::getTitre() const { return titre_; }
const std::string& Carte::getDescription() const { return description_; }
WorkflowStatus Carte::getStatus() const { return status_; }
int Carte::getPosition() const { return position_; }
const std::vector<int>& Carte::getMembresAssignesIds() const { return membresAssignesIds_; }
const std::vector<Etiquette>& Carte::getEtiquettes() const { return etiquettes_; }
const std::vector<Commentaire>& Carte::getCommentaires() const { return commentaires_; }

void Carte::setTitre(const std::string& t) { 
    std::string ancienTitre = titre_;
    titre_ = t; 
    
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("CARTE_RENOMMEE",
                   "Carte renommee: '" + ancienTitre + "' -> '" + titre_ + "'");
}

void Carte::setDescription(const std::string& d) { 
    description_ = d; 
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("CARTE_MODIFIEE",
                   "Description de la carte '" + titre_ + "' modifiee");
}

void Carte::setStatus(WorkflowStatus s) { 
    status_ = s; 
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("STATUS_MODIFIE",
                   "Statut de la carte '" + titre_ + "' change a " + to_string(s));
}

void Carte::setPosition(int position) { 
    position_ = position; 
}

void Carte::assignerMembre(int utilisateurId) {
    if (std::find(membresAssignesIds_.begin(), membresAssignesIds_.end(), utilisateurId) 
        == membresAssignesIds_.end()) {
        membresAssignesIds_.push_back(utilisateurId);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("MEMBRE_ASSIGNE",
                       "Utilisateur " + std::to_string(utilisateurId) + 
                       " assigne à la carte '" + titre_ + "'");
    }
}

void Carte::retirerMembre(int utilisateurId) {
    auto it = std::find(membresAssignesIds_.begin(), membresAssignesIds_.end(), utilisateurId);
    if (it != membresAssignesIds_.end()) {
        membresAssignesIds_.erase(it);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("MEMBRE_RETIRE_CARTE",
                       "Utilisateur " + std::to_string(utilisateurId) + 
                       " retire de la carte '" + titre_ + "'");
    }
}

void Carte::ajouterEtiquette(const Etiquette& etiquette) {
    if (std::find_if(etiquettes_.begin(), etiquettes_.end(),
                    [&etiquette](const auto& e) { return e.getNom() == etiquette.getNom(); })
        == etiquettes_.end()) {
        etiquettes_.push_back(etiquette);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("ETIQUETTE_AJOUTEE",
                       "Etiquette '" + etiquette.getNom() + 
                       "' ajoutee à la carte '" + titre_ + "'");
    }
}

void Carte::retirerEtiquette(const std::string& nomEtiquette) {
    auto it = std::find_if(etiquettes_.begin(), etiquettes_.end(),
                          [&nomEtiquette](const auto& e) { return e.getNom() == nomEtiquette; });
    if (it != etiquettes_.end()) {
        etiquettes_.erase(it);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("ETIQUETTE_RETIREE",
                       "Etiquette '" + nomEtiquette + 
                       "' retiree de la carte '" + titre_ + "'");
    }
}

void Carte::ajouterCommentaire(const Commentaire& commentaire) {
    commentaires_.push_back(commentaire);
    
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("COMMENTAIRE_AJOUTE",
                   "Nouveau commentaire sur la carte '" + titre_ + 
                   "' par " + commentaire.getAuteur());
}

bool Carte::supprimerCommentaire(int commentaireId) {
    if (commentaireId >= 0 && commentaireId < static_cast<int>(commentaires_.size())) {
        commentaires_.erase(commentaires_.begin() + commentaireId);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("COMMENTAIRE_SUPPRIME",
                       "Commentaire supprime de la carte '" + titre_ + "'");
        return true;
    }
    return false;
}

void Carte::afficher() const {
    std::cout << "    - [Carte] " << titre_ << "\n";
    std::cout << "      Description: " << description_ << "\n";
    std::cout << "      Statut: " << to_string(status_) << "\n";
    std::cout << "      Position: " << position_ << "\n";
    
    if (!membresAssignesIds_.empty()) {
        std::cout << "      Assignes: ";
        for (int id : membresAssignesIds_) std::cout << id << " ";
        std::cout << "\n";
    }
    
    if (!etiquettes_.empty()) {
        std::cout << "      Etiquettes: ";
        for (const auto& e : etiquettes_) std::cout << e.getNom() << " ";
        std::cout << "\n";
    }
    
    if (!commentaires_.empty()) {
        std::cout << "      Commentaires: " << commentaires_.size() << "\n";
    }
}