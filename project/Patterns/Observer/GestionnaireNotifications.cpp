#include "GestionnaireNotifications.hpp"
#include <iostream>
#include <cstdio>
#include <algorithm>

GestionnaireNotifications* GestionnaireNotifications::instance_ = nullptr;

GestionnaireNotifications* GestionnaireNotifications::getInstance() {
    if (instance_ == nullptr) {
        instance_ = new GestionnaireNotifications();
    }
    return instance_;
}

void GestionnaireNotifications::abonner(std::shared_ptr<IObservateur> observateur, 
                                       const std::string& typeEvenement) {
    std::lock_guard<std::mutex> lock(mutex_);
    abonnements_[typeEvenement].push_back(observateur);
    std::cout << "Abonnement: " << typeEvenement << " -> " 
              << "Nouvel observateur\n";
}

void GestionnaireNotifications::desabonner(std::shared_ptr<IObservateur> observateur, 
                                          const std::string& typeEvenement) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = abonnements_.find(typeEvenement);
    if (it != abonnements_.end()) {
        auto& observateurs = it->second;
        observateurs.erase(std::remove(observateurs.begin(), observateurs.end(), observateur),
                          observateurs.end());
    }
}

void GestionnaireNotifications::notifier(const std::string& typeEvenement, 
                                        const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = abonnements_.find(typeEvenement);
    if (it != abonnements_.end()) {
        for (auto& observateur : it->second) {
            if (observateur) {
                observateur->recevoirNotification(typeEvenement, message);
            }
        }
    }
    
    // Notifier aussi les abonnés à "TOUS" les événements
    auto itTous = abonnements_.find("TOUS");
    if (itTous != abonnements_.end()) {
        for (auto& observateur : itTous->second) {
            if (observateur) {
                observateur->recevoirNotification(typeEvenement, message);
            }
        }
    }
    
    // Afficher dans les logs système
    std::cout << "[SYSTEM] Notification: " << typeEvenement << " - " << message << std::endl;
}

// Implémentation template pour le formatage
template<typename... Args>
void GestionnaireNotifications::notifier(const std::string& typeEvenement, 
                                        const std::string& format, Args... args) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), format.c_str(), args...);
    notifier(typeEvenement, std::string(buffer));
}