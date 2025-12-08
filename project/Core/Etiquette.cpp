#include "Etiquette.hpp"

Etiquette::Etiquette(std::string nom, std::string couleur)
    : nom_(std::move(nom)), couleur_(std::move(couleur)) {}

const std::string& Etiquette::getNom() const { return nom_; }
const std::string& Etiquette::getCouleur() const { return couleur_; }
void Etiquette::setNom(const std::string& n) { nom_ = n; }
void Etiquette::setCouleur(const std::string& c) { couleur_ = c; }