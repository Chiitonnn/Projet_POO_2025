#include "Commentaire.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

Commentaire::Commentaire(int id, std::string message, std::string auteur)
    : id_(id), message_(std::move(message)), auteur_(std::move(auteur)) {
    time_t now = time(nullptr);
    date_ = *localtime(&now);
}

int Commentaire::getId() const { return id_; }
const std::string& Commentaire::getMessage() const { return message_; }
const std::tm& Commentaire::getDate() const { return date_; }
const std::string& Commentaire::getAuteur() const { return auteur_; }

void Commentaire::setMessage(const std::string& m) { message_ = m; }

std::string Commentaire::getDateFormatee() const {
    std::ostringstream oss;
    oss << std::put_time(&date_, "%d/%m/%Y %H:%M");
    return oss.str();
}

void Commentaire::afficher() const {
    std::cout << "      [" << getDateFormatee() << "] " << auteur_ << ": " 
              << message_ << "\n";
}