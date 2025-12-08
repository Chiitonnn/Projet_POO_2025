#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Utilisateur.hpp"
#include "Etiquette.hpp"
#include "Commentaire.hpp"
#include "WorkflowStatus.hpp"

class Carte {
private:
    int id_;
    std::string titre_;
    std::string description_;
    WorkflowStatus status_;
    int position_;
    std::vector<int> membresAssignesIds_;
    std::vector<Etiquette> etiquettes_;
    std::vector<Commentaire> commentaires_;
    
public:
    Carte(int id, std::string titre, std::string description = "");
    
    // Getters
    int getId() const;
    const std::string& getTitre() const;
    const std::string& getDescription() const;
    WorkflowStatus getStatus() const;
    int getPosition() const;
    const std::vector<int>& getMembresAssignesIds() const;
    const std::vector<Etiquette>& getEtiquettes() const;
    const std::vector<Commentaire>& getCommentaires() const;
    
    // Setters
    void setTitre(const std::string& t);
    void setDescription(const std::string& d);
    void setStatus(WorkflowStatus s);
    void setPosition(int position);
    
    // Méthodes métier
    void assignerMembre(int utilisateurId);
    void retirerMembre(int utilisateurId);
    void ajouterEtiquette(const Etiquette& etiquette);
    void retirerEtiquette(const std::string& nomEtiquette);
    void ajouterCommentaire(const Commentaire& commentaire);
    bool supprimerCommentaire(int commentaireId);
    
    // Affichage
    void afficher() const;
};