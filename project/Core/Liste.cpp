#include "Liste.hpp"
#include "../Patterns/Observer/GestionnaireNotifications.hpp"
#include "../Patterns/Factory/FabriqueCarteStandard.hpp"
#include <iostream>
#include <algorithm>

Liste::Liste(int id, std::string nom, int position)
    : id_(id), nom_(std::move(nom)), position_(position) {}

int Liste::getId() const { return id_; }
const std::string& Liste::getNom() const { return nom_; }
int Liste::getPosition() const { return position_; }
const std::vector<std::shared_ptr<Carte>>& Liste::getCartes() const { return cartes_; }

void Liste::setNom(const std::string& n) { 
    std::string ancienNom = nom_;
    nom_ = n; 
    
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("LISTE_RENOMMEE",
                   "Liste renommee: '" + ancienNom + "' -> '" + nom_ + "'");
}

void Liste::setPosition(int position) { 
    position_ = position; 
}

std::shared_ptr<Carte> Liste::ajouterCarte(const std::string& titre) {
    static int nextCarteId = 1;
    
    FabriqueCarteStandard fabrique;
    auto carte = fabrique.creerCarte(nextCarteId++, titre);
    cartes_.push_back(carte);
    
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("CARTE_CREEE",
                   "Carte '" + titre + "' creee dans la liste '" + nom_ + "'");
    
    return carte;
}

bool Liste::deplacerCarte(int carteId, int nouvellePosition) {
    auto it = std::find_if(cartes_.begin(), cartes_.end(),
                          [carteId](const auto& carte) { return carte->getId() == carteId; });
    
    if (it != cartes_.end() && nouvellePosition >= 0 && nouvellePosition < static_cast<int>(cartes_.size())) {
        auto carte = *it;
        int anciennePosition = std::distance(cartes_.begin(), it);
        
        cartes_.erase(it);
        cartes_.insert(cartes_.begin() + nouvellePosition, carte);
        carte->setPosition(nouvellePosition);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("CARTE_DEPLACEE",
                       "Carte '" + carte->getTitre() + "' déplacee de la position " + 
                       std::to_string(anciennePosition) + " à " + std::to_string(nouvellePosition));
        
        return true;
    }
    return false;
}

bool Liste::supprimerCarte(int carteId) {
    auto it = std::find_if(cartes_.begin(), cartes_.end(),
                          [carteId](const auto& carte) { return carte->getId() == carteId; });
    
    if (it != cartes_.end()) {
        auto nomCarte = (*it)->getTitre();
        cartes_.erase(it);
        
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("CARTE_SUPPRIMEE",
                       "Carte '" + nomCarte + "' supprimee de la liste '" + nom_ + "'");
        return true;
    }
    return false;
}

void Liste::afficher() const {
    std::cout << "  [Liste] " << nom_ << " (Position: " << position_ << ")\n";
    for (const auto& carte : cartes_) {
        carte->afficher();
    }
}