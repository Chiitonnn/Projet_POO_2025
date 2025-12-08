#include "Utilisateur.hpp"
#include <iostream>
#include <algorithm>

Utilisateur::Utilisateur(int id, std::string nom, std::string email)
    : id_(id), nom_(std::move(nom)), email_(std::move(email)) {}

int Utilisateur::getId() const { return id_; }
const std::string& Utilisateur::getNom() const { return nom_; }
const std::string& Utilisateur::getEmail() const { return email_; }
const std::vector<int>& Utilisateur::getTableaux() const { return tableaux_; }
const std::vector<std::string>& Utilisateur::getNotifications() const { return notifications_; }

void Utilisateur::setNom(const std::string& n) { nom_ = n; }
void Utilisateur::setEmail(const std::string& e) { email_ = e; }

void Utilisateur::rejoindreTableau(int tableauId) {
    if (std::find(tableaux_.begin(), tableaux_.end(), tableauId) == tableaux_.end()) {
        tableaux_.push_back(tableauId);
    }
}

void Utilisateur::quitterTableau(int tableauId) {
    tableaux_.erase(std::remove(tableaux_.begin(), tableaux_.end(), tableauId), tableaux_.end());
}

void Utilisateur::recevoirNotification(const std::string& type, const std::string& message) {
    std::string notification = "[" + type + "] " + message;
    notifications_.push_back(notification);
    std::cout << "Notification pour " << nom_ << ": " << notification << std::endl;
}

void Utilisateur::afficherNotifications() const {
    std::cout << "\n=== Notifications de " << nom_ << " ===\n";
    if (notifications_.empty()) {
        std::cout << "Aucune notification.\n";
    } else {
        for (const auto& notif : notifications_) {
            std::cout << "- " << notif << "\n";
        }
    }
    std::cout << "=============================\n";
}