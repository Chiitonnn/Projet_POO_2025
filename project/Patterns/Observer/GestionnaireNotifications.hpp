#pragma once
#include "IObservateur.hpp"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <mutex>

class GestionnaireNotifications {
private:
    static GestionnaireNotifications* instance_;
    std::map<std::string, std::vector<std::shared_ptr<IObservateur>>> abonnements_;
    mutable std::mutex mutex_;
    
    GestionnaireNotifications() = default;
    GestionnaireNotifications(const GestionnaireNotifications&) = delete;
    GestionnaireNotifications& operator=(const GestionnaireNotifications&) = delete;
    
public:
    static GestionnaireNotifications* getInstance();
    
    void abonner(std::shared_ptr<IObservateur> observateur, const std::string& typeEvenement);
    void desabonner(std::shared_ptr<IObservateur> observateur, const std::string& typeEvenement);
    void notifier(const std::string& typeEvenement, const std::string& message);
    
    template<typename... Args>
    void notifier(const std::string& typeEvenement, const std::string& format, Args... args);
};