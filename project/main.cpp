#include <iostream>
#include <memory>
#include <limits>
#include <vector>
#include "Patterns/Facade/SystemFacade.hpp"

// Déclarations anticipées
void menuListes(SystemFacade& systeme, std::shared_ptr<Tableau> tableau);
void menuCartes(SystemFacade& systeme, std::shared_ptr<Tableau> tableau, 
                std::shared_ptr<Liste> liste);
void menuCarteDetaillee(SystemFacade& systeme, std::shared_ptr<Tableau> tableau,
                       std::shared_ptr<Liste> liste, std::shared_ptr<Carte> carte);

// Fonctions utilitaires
int lireEntier() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entree invalide. Reessayez: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return x;
}

std::string lireChaine(const std::string& message) {
    std::cout << message;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

void afficherSeparateur() {
    std::cout << "\n" << std::string(50, '=') << "\n";
}

// Afficher un tableau
void afficherTableauDetaille(std::shared_ptr<Tableau> tableau) {
    if (!tableau) return;
    
    std::cout << "\nTABLEAU: " << tableau->getNom() << "\n";
    std::cout << "Createur: " << tableau->getCreateurId() << "\n";
    std::cout << "Membres: ";
    for (int id : tableau->getMembresIds()) std::cout << id << " ";
    std::cout << "\n" << std::string(30, '-') << "\n";
    
    int listeIndex = 0;
    for (const auto& liste : tableau->getListes()) {
        std::cout << "\n[" << listeIndex++ << "] LISTE: " << liste->getNom() << "\n";
        
        int carteIndex = 0;
        for (const auto& carte : liste->getCartes()) {
            std::cout << "  [" << carteIndex++ << "] CARTE: " << carte->getTitre();
            if (carte->getStatus() == WorkflowStatus::IN_PROGRESS) std::cout << " [EN COURS]";
            if (carte->getStatus() == WorkflowStatus::DONE) std::cout << " [TERMINE]";
            if (!carte->getMembresAssignesIds().empty()) std::cout << " [ASSIGNE]";
            if (!carte->getEtiquettes().empty()) std::cout << " [ETIQUETTES]";
            if (!carte->getCommentaires().empty()) std::cout << " [COMMENTAIRES]";
            std::cout << "\n";
        }
        if (liste->getCartes().empty()) {
            std::cout << "  (vide)\n";
        }
    }
}

// Menu tableaux
void menuTableaux(SystemFacade& systeme) {
    while (true) {
        afficherSeparateur();
        std::cout << "MENU PRINCIPAL - TABLEAUX\n";
        std::cout << "1. Creer un nouveau tableau\n";
        std::cout << "2. Voir tous les tableaux\n";
        std::cout << "3. Ouvrir un tableau\n";
        std::cout << "4. Quitter\n";
        std::cout << "Choix: ";
        
        int choix = lireEntier();
        
        switch (choix) {
            case 1: {
                std::string nom = lireChaine("Nom du tableau: ");
                std::cout << "Votre ID utilisateur: ";
                int createurId = lireEntier();
                
                auto tableau = systeme.creerTableau(nom, createurId);
                if (tableau) {
                    std::cout << "[OK] Tableau cree: " << nom << " (ID: " << tableau->getId() << ")\n";
                    
                    std::cout << "Voulez-vous acceder a ce tableau ? (o/n): ";
                    char acces;
                    std::cin >> acces;
                    std::cin.ignore();
                    
                    if (acces == 'o' || acces == 'O') {
                        menuListes(systeme, tableau);
                    }
                } else {
                    std::cout << "[ERREUR] Echec de creation\n";
                }
                break;
            }
            
            case 2: {
                systeme.afficherTableaux();
                break;
            }
            
            case 3: {
                std::cout << "ID du tableau a ouvrir: ";
                int tableauId = lireEntier();
                
                auto tableau = systeme.getTableau(tableauId);
                if (tableau) {
                    menuListes(systeme, tableau);
                } else {
                    std::cout << "[ERREUR] Tableau non trouve\n";
                }
                break;
            }
            
            case 4:
                std::cout << "Au revoir !\n";
                return;
                
            default:
                std::cout << "[ERREUR] Choix invalide\n";
        }
    }
}

// Menu listes
void menuListes(SystemFacade& systeme, std::shared_ptr<Tableau> tableau) {
    while (true) {
        afficherTableauDetaille(tableau);
        afficherSeparateur();
        std::cout << "MENU LISTES - Tableau: " << tableau->getNom() << "\n";
        std::cout << "1. Creer une nouvelle liste\n";
        std::cout << "2. Renommer une liste\n";
        std::cout << "3. Ouvrir une liste\n";
        std::cout << "4. Supprimer une liste\n";
        std::cout << "5. Ajouter un membre au tableau\n";
        std::cout << "6. Retour aux tableaux\n";
        std::cout << "Choix: ";
        
        int choix = lireEntier();
        
        switch (choix) {
            case 1: {
                std::string nom = lireChaine("Nom de la liste: ");
                auto liste = tableau->creerListe(nom);
                std::cout << "[OK] Liste creee: " << nom << "\n";
                break;
            }
            
            case 2: {
                std::cout << "Numero de la liste a renommer: ";
                int listeIndex = lireEntier();
                
                auto listes = tableau->getListes();
                if (listeIndex >= 0 && listeIndex < static_cast<int>(listes.size())) {
                    std::string nouveauNom = lireChaine("Nouveau nom: ");
                    listes[listeIndex]->setNom(nouveauNom);
                    std::cout << "[OK] Liste renommee\n";
                } else {
                    std::cout << "[ERREUR] Liste non trouvee\n";
                }
                break;
            }
            
            case 3: {
                std::cout << "Numero de la liste a ouvrir: ";
                int listeIndex = lireEntier();
                
                auto listes = tableau->getListes();
                if (listeIndex >= 0 && listeIndex < static_cast<int>(listes.size())) {
                    menuCartes(systeme, tableau, listes[listeIndex]);
                } else {
                    std::cout << "[ERREUR] Liste non trouvee\n";
                }
                break;
            }
            
            case 4: {
                std::cout << "Numero de la liste a supprimer: ";
                int listeIndex = lireEntier();
                
                auto listes = tableau->getListes();
                if (listeIndex >= 0 && listeIndex < static_cast<int>(listes.size())) {
                    std::string nomListe = listes[listeIndex]->getNom();
                    if (tableau->supprimerListe(listes[listeIndex]->getId())) {
                        std::cout << "[OK] Liste supprimee: " << nomListe << "\n";
                    }
                } else {
                    std::cout << "[ERREUR] Liste non trouvee\n";
                }
                break;
            }
            
            case 5: {
                std::cout << "ID de l'utilisateur a ajouter: ";
                int userId = lireEntier();
                tableau->ajouterMembre(userId);
                std::cout << "[OK] Membre ajoute\n";
                break;
            }
            
            case 6:
                return;
                
            default:
                std::cout << "[ERREUR] Choix invalide\n";
        }
    }
}

// Menu cartes
void menuCartes(SystemFacade& systeme, std::shared_ptr<Tableau> tableau, 
                std::shared_ptr<Liste> liste) {
    while (true) {
        std::cout << "\n" << std::string(40, '-') << "\n";
        std::cout << "LISTE: " << liste->getNom() << " (dans " << tableau->getNom() << ")\n";
        std::cout << std::string(40, '-') << "\n";
        
        int carteIndex = 0;
        for (const auto& carte : liste->getCartes()) {
            std::cout << "[" << carteIndex++ << "] " << carte->getTitre();
            if (carte->getStatus() == WorkflowStatus::IN_PROGRESS) std::cout << " [EN COURS]";
            if (carte->getStatus() == WorkflowStatus::DONE) std::cout << " [TERMINE]";
            std::cout << "\n";
        }
        if (liste->getCartes().empty()) {
            std::cout << "(Aucune carte)\n";
        }
        
        afficherSeparateur();
        std::cout << "MENU CARTES\n";
        std::cout << "1. Creer une nouvelle carte\n";
        std::cout << "2. Ouvrir/modifier une carte\n";
        std::cout << "3. Deplacer une carte\n";
        std::cout << "4. Supprimer une carte\n";
        std::cout << "5. Retour a la liste des listes\n";
        std::cout << "Choix: ";
        
        int choix = lireEntier();
        
        switch (choix) {
            case 1: {
                std::string titre = lireChaine("Titre de la carte: ");
                std::string description = lireChaine("Description (optionnelle): ");
                
                auto carte = liste->ajouterCarte(titre);
                if (!description.empty()) {
                    carte->setDescription(description);
                }
                std::cout << "[OK] Carte creee: " << titre << "\n";
                break;
            }
            
            case 2: {
                if (liste->getCartes().empty()) {
                    std::cout << "[ERREUR] Aucune carte dans cette liste\n";
                    break;
                }
                
                std::cout << "Numero de la carte a ouvrir: ";
                int carteIndex = lireEntier();
                
                auto cartes = liste->getCartes();
                if (carteIndex >= 0 && carteIndex < static_cast<int>(cartes.size())) {
                    menuCarteDetaillee(systeme, tableau, liste, cartes[carteIndex]);
                } else {
                    std::cout << "[ERREUR] Carte non trouvee\n";
                }
                break;
            }
            
            case 3: {
                if (liste->getCartes().empty()) {
                    std::cout << "[ERREUR] Aucune carte dans cette liste\n";
                    break;
                }
                
                std::cout << "Numero de la carte a deplacer: ";
                int carteIndex = lireEntier();
                std::cout << "Nouvelle position (0-" << liste->getCartes().size()-1 << "): ";
                int nouvellePos = lireEntier();
                
                if (liste->deplacerCarte(liste->getCartes()[carteIndex]->getId(), nouvellePos)) {
                    std::cout << "[OK] Carte deplacee\n";
                } else {
                    std::cout << "[ERREUR] Echec du deplacement\n";
                }
                break;
            }
            
            case 4: {
                if (liste->getCartes().empty()) {
                    std::cout << "[ERREUR] Aucune carte dans cette liste\n";
                    break;
                }
                
                std::cout << "Numero de la carte a supprimer: ";
                int carteIndex = lireEntier();
                
                auto cartes = liste->getCartes();
                if (carteIndex >= 0 && carteIndex < static_cast<int>(cartes.size())) {
                    std::string titre = cartes[carteIndex]->getTitre();
                    if (liste->supprimerCarte(cartes[carteIndex]->getId())) {
                        std::cout << "[OK] Carte supprimee: " << titre << "\n";
                    }
                } else {
                    std::cout << "[ERREUR] Carte non trouvee\n";
                }
                break;
            }
            
            case 5:
                return;
                
            default:
                std::cout << "[ERREUR] Choix invalide\n";
        }
    }
}

// Menu carte detaillee
void menuCarteDetaillee(SystemFacade& systeme, std::shared_ptr<Tableau> tableau,
                       std::shared_ptr<Liste> liste, std::shared_ptr<Carte> carte) {
    while (true) {
        std::cout << "\n" << std::string(40, '=') << "\n";
        std::cout << "CARTE: " << carte->getTitre() << "\n";
        std::cout << std::string(40, '=') << "\n";
        
        std::cout << "Description: " << carte->getDescription() << "\n";
        std::cout << "Statut: " << to_string(carte->getStatus()) << "\n";
        
        std::cout << "Membres assignes: ";
        auto membres = carte->getMembresAssignesIds();
        if (membres.empty()) {
            std::cout << "Aucun\n";
        } else {
            for (int id : membres) std::cout << id << " ";
            std::cout << "\n";
        }
        
        std::cout << "Etiquettes: ";
        auto etiquettes = carte->getEtiquettes();
        if (etiquettes.empty()) {
            std::cout << "Aucune\n";
        } else {
            for (const auto& e : etiquettes) {
                std::cout << "[" << e.getNom() << "] ";
            }
            std::cout << "\n";
        }
        
        std::cout << "Commentaires (" << carte->getCommentaires().size() << "):\n";
        for (const auto& commentaire : carte->getCommentaires()) {
            std::cout << "  - " << commentaire.getAuteur() << ": " 
                      << commentaire.getMessage() << "\n";
        }
        
        afficherSeparateur();
        std::cout << "MENU CARTE DETAILLEE\n";
        std::cout << "1. Modifier le titre\n";
        std::cout << "2. Modifier la description\n";
        std::cout << "3. Changer le statut\n";
        std::cout << "4. Assigner un membre\n";
        std::cout << "5. Ajouter une etiquette\n";
        std::cout << "6. Ajouter un commentaire\n";
        std::cout << "7. Retour a la liste\n";
        std::cout << "Choix: ";
        
        int choix = lireEntier();
        
        switch (choix) {
            case 1: {
                std::string nouveauTitre = lireChaine("Nouveau titre: ");
                carte->setTitre(nouveauTitre);
                std::cout << "[OK] Titre modifie\n";
                break;
            }
            
            case 2: {
                std::string nouvelleDesc = lireChaine("Nouvelle description: ");
                carte->setDescription(nouvelleDesc);
                std::cout << "[OK] Description modifiee\n";
                break;
            }
            
            case 3: {
                std::cout << "Nouveau statut:\n";
                std::cout << "1. A faire\n";
                std::cout << "2. En cours\n";
                std::cout << "3. Termine\n";
                std::cout << "Choix: ";
                int statutChoix = lireEntier();
                
                switch (statutChoix) {
                    case 1: carte->setStatus(WorkflowStatus::TODO); break;
                    case 2: carte->setStatus(WorkflowStatus::IN_PROGRESS); break;
                    case 3: carte->setStatus(WorkflowStatus::DONE); break;
                    default: std::cout << "[ERREUR] Choix invalide\n";
                }
                if (statutChoix >= 1 && statutChoix <= 3) {
                    std::cout << "[OK] Statut modifie\n";
                }
                break;
            }
            
            case 4: {
                std::cout << "ID du membre a assigner: ";
                int userId = lireEntier();
                carte->assignerMembre(userId);
                std::cout << "[OK] Membre assigne\n";
                break;
            }
            
            case 5: {
                std::string nom = lireChaine("Nom de l'etiquette: ");
                std::string couleur = lireChaine("Couleur: ");
                carte->ajouterEtiquette(Etiquette(nom, couleur));
                std::cout << "[OK] Etiquette ajoutee\n";
                break;
            }
            
            case 6: {
                std::string message = lireChaine("Message: ");
                std::string auteur = lireChaine("Votre nom: ");
                carte->ajouterCommentaire(Commentaire(carte->getCommentaires().size() + 1, 
                                                     message, auteur));
                std::cout << "[OK] Commentaire ajoute\n";
                break;
            }
            
            case 7:
                return;
                
            default:
                std::cout << "[ERREUR] Choix invalide\n";
        }
    }
}

// Menu initial
void menuInitial(SystemFacade& systeme) {
    afficherSeparateur();
    std::cout << "BIENVENUE DANS LE SYSTEME DE TABLEAUX\n";
    std::cout << std::string(50, '=') << "\n";
    
    std::cout << "Pour commencer, creez votre profil:\n";
    std::string nom = lireChaine("Votre nom: ");
    std::string email = lireChaine("Votre email: ");
    
    auto utilisateur = systeme.creerUtilisateur(nom, email);
    std::cout << "[OK] Bienvenue " << nom << "! (ID: " << utilisateur->getId() << ")\n";
    
    menuTableaux(systeme);
}

// Programme principal
int main() {
    SystemFacade systeme;
    
    try {
        menuInitial(systeme);
    } catch (const std::exception& e) {
        std::cout << "[ERREUR] " << e.what() << "\n";
    }
    
    std::cout << "\nMerci d'avoir utilise notre systeme !\n";
    return 0;
}