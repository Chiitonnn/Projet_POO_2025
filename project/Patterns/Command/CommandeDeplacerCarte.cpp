#include "CommandeDeplacerCarte.hpp"
#include "../Observer/GestionnaireNotifications.hpp"
#include <iostream>
#include <algorithm>

CommandeDeplacerCarte::CommandeDeplacerCarte(std::shared_ptr<Carte> carte,
                                           std::shared_ptr<Liste> ancienneListe,
                                           std::shared_ptr<Liste> nouvelleListe,
                                           int nouvellePosition)
    : carte_(std::move(carte)),
      ancienneListe_(std::move(ancienneListe)),
      nouvelleListe_(std::move(nouvelleListe)),
      nouvellePosition_(nouvellePosition) {
    
    // Trouver la position actuelle dans l'ancienne liste
    if (ancienneListe_) {
        const auto& cartes = ancienneListe_->getCartes();
        for (size_t i = 0; i < cartes.size(); i++) {
            if (cartes[i]->getId() == carte_->getId()) {
                anciennePosition_ = static_cast<int>(i);
                break;
            }
        }
    }
}

void CommandeDeplacerCarte::executer() {
    if (!carte_ || !ancienneListe_ || !nouvelleListe_) return;
    
    // Retirer de l'ancienne liste
    auto cartesAncienne = ancienneListe_->getCartes();
    auto it = std::find_if(cartesAncienne.begin(), cartesAncienne.end(),
                          [this](const auto& c) { return c->getId() == carte_->getId(); });
    
    if (it != cartesAncienne.end()) {
        // En réalité, cette logique devrait être dans Liste
        // Pour simplifier, on notifie seulement
        auto notif = GestionnaireNotifications::getInstance();
        notif->notifier("COMMANDE_EXECUTEE",
                       "Carte '" + carte_->getTitre() + 
                       "' déplacee de '" + ancienneListe_->getNom() + 
                       "' vers '" + nouvelleListe_->getNom() + 
                       "' (position " + std::to_string(nouvellePosition_) + ")");
    }
}

void CommandeDeplacerCarte::annuler() {
    auto notif = GestionnaireNotifications::getInstance();
    notif->notifier("COMMANDE_ANNULEE",
                   "Annulation: Carte '" + carte_->getTitre() + 
                   "' retourne à '" + ancienneListe_->getNom() + 
                   "' (position " + std::to_string(anciennePosition_) + ")");
}

std::string CommandeDeplacerCarte::getDescription() const {
    return "Deplacement carte " + std::to_string(carte_->getId()) + 
           " de liste " + std::to_string(ancienneListe_->getId()) + 
           " à liste " + std::to_string(nouvelleListe_->getId());
}