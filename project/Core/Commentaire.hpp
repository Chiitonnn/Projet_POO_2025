#pragma once
#include <string>
#include <ctime>

class Commentaire {
private:
    int id_;
    std::string message_;
    std::tm date_;
    std::string auteur_;
    
public:
    Commentaire() = default;
    Commentaire(int id, std::string message, std::string auteur);
    
    // Getters
    int getId() const;
    const std::string& getMessage() const;
    const std::tm& getDate() const;
    const std::string& getAuteur() const;
    
    // Setters
    void setMessage(const std::string& m);
    
    // Méthodes utilitaires
    std::string getDateFormatee() const;
    void afficher() const;
};