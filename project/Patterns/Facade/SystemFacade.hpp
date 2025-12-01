// Patterns/Facade/SystemFacade.hpp
#pragma once
#include <memory>
#include "TaskManager.hpp"
#include "UserManager.hpp"
#include "AssignmentManager.hpp"
#include "../Observer/NotificationCenter.hpp"
#include "../Singleton/HistoryLogger.hpp"
#include "PriorityStrategy.hpp"
#include <memory>
#include <string>

class SystemFacade {
private:
    TaskManager taskManager_;
    UserManager userManager_;
    mutable NotificationCenter notifier_;
public:
    SystemFacade();

    // Observers
    void subscribeObserver(std::shared_ptr<IObserver> o);
    void unsubscribeObserver(std::shared_ptr<IObserver> o);

    // Create
    std::shared_ptr<User> createUser(const std::string& name, const std::string& role);
    std::shared_ptr<Task> createTask(const std::string& title, const std::string& desc, PriorityStrategyPtr strat);

    // Modify / Delete
    bool deleteUser(int userId);
    bool deleteTask(int taskId);

    std::shared_ptr<User> getUser(int userId);
    std::shared_ptr<Task> getTask(int taskId);

    // Assign
    bool assignTaskToUser(int taskId, int userId);
    bool unassignTask(int taskId);

    // Display
    void printAllUsers() const;
    void printAllTasks() const;
    void printHistory() const;

    // notify/log helper
    void notifyAndLog(const std::string& msg) const;
};
