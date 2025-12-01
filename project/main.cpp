// main.cpp
#include <iostream>
#include <memory>
#include <limits>
#include "Patterns/Facade/SystemFacade.hpp"
#include "Core/ConcretePriorityStrategies/StandardPriority.hpp"
#include "Patterns/Observer/IObserver.hpp"

// Simple console observer
class ConsoleObserver : public IObserver {
public:
    void notify(const std::string& event) override {
        std::cout << "[NOTIF] " << event << std::endl;
    }
};

static int readInt() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrée invalide. Réessaye: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return x;
}

int main() {
    SystemFacade sys;
    auto consoleObs = std::make_shared<ConsoleObserver>();
    sys.subscribeObserver(consoleObs);
    auto defaultStrategy = std::make_shared<StandardPriority>();

    bool running = true;
    while (running) {
        std::cout << "\n===== GESTIONNAIRE DE TACHES =====\n"
                  << "1. Créer\n2. Assigner\n3. Modifier\n4. Afficher\n5. Supprimer\n6. Exit\n"
                  << "Choix: ";
        int choice = readInt();
        switch (choice) {
            case 1: { // Créer
                std::cout << "1. Créer un utilisateur\n2. Créer une tâche\n3. Retour\nChoix: ";
                int c = readInt();
                if (c == 1) {
                    std::string name, role;
                    std::cout << "Nom: "; std::getline(std::cin, name);
                    std::cout << "Role: "; std::getline(std::cin, role);
                    sys.createUser(name, role);
                } else if (c == 2) {
                    std::string title, desc;
                    std::cout << "Titre: "; std::getline(std::cin, title);
                    std::cout << "Description: "; std::getline(std::cin, desc);
                    sys.createTask(title, desc, defaultStrategy);
                }
            } break;
            case 2: { // Assigner
                std::cout << "1. Assigner une tâche à un utilisateur\n2. Assigner un utilisateur à une tâche\n3. Retour\nChoix: ";
                int c = readInt();
                if (c == 1 || c == 2) {
                    std::cout << "Id tâche: "; int tid = readInt();
                    std::cout << "Id utilisateur: "; int uid = readInt();
                    if (!sys.assignTaskToUser(tid, uid)) std::cout << "Erreur assignation\n";
                }
            } break;
            case 3: { // Modifier
                std::cout << "1. Modifier un utilisateur\n2. Modifier une tâche\n3. Modifier une assignation\n4. Retour\nChoix: ";
                int c = readInt();
                if (c == 1) {
                    std::cout << "Id utilisateur: "; int uid = readInt();
                    auto u = sys.getUser(uid);
                    if (!u) { std::cout << "Utilisateur non trouvé\n"; break; }
                    std::string name, role;
                    std::cout << "Nouveau nom (vide pour ignorer): "; std::getline(std::cin, name);
                    if (!name.empty()) u->setName(name);
                    std::cout << "Nouveau role (vide pour ignorer): "; std::getline(std::cin, role);
                    if (!role.empty()) u->setRole(role);
                    std::cout << "Modifié.\n";
                } else if (c == 2) {
                    std::cout << "Id tâche: "; int tid = readInt();
                    auto t = sys.getTask(tid);
                    if (!t) { std::cout << "Tâche non trouvée\n"; break; }
                    std::string title, desc;
                    std::cout << "Nouveau titre (vide pour ignorer): "; std::getline(std::cin, title);
                    if (!title.empty()) t->setTitle(title);
                    std::cout << "Nouvelle description (vide pour ignorer): "; std::getline(std::cin, desc);
                    if (!desc.empty()) t->setDescription(desc);
                    std::cout << "Changer statut? 1-todo 2-in_progress 3-done 0-ignore: ";
                    int s = readInt();
                    if (s==1) t->setStatus(WorkflowStatus::TODO);
                    if (s==2) t->setStatus(WorkflowStatus::IN_PROGRESS);
                    if (s==3) t->setStatus(WorkflowStatus::DONE);
                    std::cout << "Modifié.\n";
                } else if (c == 3) {
                    std::cout << "1. Désassigner tâche\n2. Réassigner tâche\nChoix: ";
                    int m = readInt();
                    if (m == 1) {
                        std::cout << "Id tâche: "; int tid = readInt();
                        if (!sys.unassignTask(tid)) std::cout << "Erreur désassignation\n";
                    } else if (m == 2) {
                        std::cout << "Id tâche: "; int tid = readInt();
                        std::cout << "Id nouvel utilisateur: "; int uid = readInt();
                        if (!sys.assignTaskToUser(tid, uid)) std::cout << "Erreur assignation\n";
                    }
                }
            } break;
            case 4: { // Afficher
                std::cout << "1. Afficher tous les utilisateurs + tâches\n2. Afficher toutes les tâches\n3. Afficher l’historique\n4. Retour\nChoix: ";
                int c = readInt();
                if (c == 1) sys.printAllUsers();
                else if (c == 2) sys.printAllTasks();
                else if (c == 3) sys.printHistory();
            } break;
            case 5: { // Supprimer
                std::cout << "1. Supprimer un utilisateur\n2. Supprimer une tâche\n3. Retour\nChoix: ";
                int c = readInt();
                if (c == 1) {
                    std::cout << "Id utilisateur: "; int uid = readInt();
                    if (!sys.deleteUser(uid)) std::cout << "Erreur suppression\n";
                } else if (c == 2) {
                    std::cout << "Id tâche: "; int tid = readInt();
                    if (!sys.deleteTask(tid)) std::cout << "Erreur suppression\n";
                }
            } break;
            case 6: running = false; break;
            default: std::cout << "Choix inconnu\n"; break;
        }
    }

    std::cout << "Au revoir.\n";
    return 0;
}
