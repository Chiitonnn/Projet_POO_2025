#pragma once
#include "ICommande.hpp"
#include "../../Core/Carte.hpp"
#include "../../Core/Liste.hpp"
#include <memory>

class CommandeDeplacerCarte : public ICommande {
private:
    std::shared_ptr<Carte> carte_;
    std::shared_ptr<Liste> ancienneListe_;
    std::shared_ptr<Liste> nouvelleListe_;
    int anciennePosition_;
    int nouvellePosition_;
    
public:
    CommandeDeplacerCarte(std::shared_ptr<Carte> carte, 
                          std::shared_ptr<Liste> ancienneListe,
                          std::shared_ptr<Liste> nouvelleListe,
                          int nouvellePosition);
    
    void executer() override;
    void annuler() override;
    std::string getDescription() const override;
};