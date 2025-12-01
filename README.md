# Projet_POO_2025

pour compiler : make 
pour executer : ./task_manager

pour compiler sous windows : 

g++ -std=c++17 -Wall -Wextra -O2 -I./Core -I./Managers -I./Patterns \
main.cpp Core/Task.cpp Core/User.cpp Core/ConcretePriorityStrategies/StandardPriority.cpp \
Managers/TaskManager.cpp Managers/UserManager.cpp Managers/AssignmentManager.cpp \
Patterns/Observer/NotificationCenter.cpp Patterns/Singleton/HistoryLogger.cpp \
Patterns/Facade/SystemFacade.cpp -o task_manager


pour executer sous windows : ./task_manager.exe
