#pragma once
#include <string>

class Etiquette {
private:
    std::string nom_;
    std::string couleur_;
    
public:
    Etiquette() = default;
    Etiquette(std::string nom, std::string couleur);
    
    // Getters
    const std::string& getNom() const;
    const std::string& getCouleur() const;
    
    // Setters
    void setNom(const std::string& n);
    void setCouleur(const std::string& c);
};