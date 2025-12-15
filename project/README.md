# Gestionnaire de Tâches collaboratif (Terminal) - C++

## But
Projet C++ terminal inspiré de Trello — gestion de tâches, utilisateurs, assignations, notifications et historique.

## Structure
- `Core/` : entités métier (Task, User, Strategy)
- `Managers/` : gestionnaires (TaskManager, UserManager, AssignmentManager)
- `Patterns/Observer/` : Observer pattern (NotificationCenter)
- `Patterns/Singleton/` : HistoryLogger (singleton)
- `Patterns/Facade/` : SystemFacade (interface simplifiée)
- `main.cpp` : interface terminal interactive

## Design patterns utilisés
- **Singleton** : `HistoryLogger` (logs centralisés)
- **Observer** : `NotificationCenter` (publish/subscribe pour notifications)
- **Strategy** : `PriorityStrategy` et implémentation `StandardPriority`
- **Facade** : `SystemFacade` rassemble opérations haute-niveau

## Compilation
Assurez-vous d'avoir `g++` (support C++17).
```bash
make 


# Projet_POO_2025

pour compiler : make 
pour executer : make run