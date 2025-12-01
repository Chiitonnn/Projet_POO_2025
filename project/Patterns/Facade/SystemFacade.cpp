// Patterns/Facade/SystemFacade.cpp
#include "SystemFacade.hpp"
#include "../Patterns/Singleton/HistoryLogger.hpp"
#include <iostream>

SystemFacade::SystemFacade() {}

void SystemFacade::subscribeObserver(std::shared_ptr<IObserver> o) { notifier_.subscribe(o); }
void SystemFacade::unsubscribeObserver(std::shared_ptr<IObserver> o) { notifier_.unsubscribe(o); }

std::shared_ptr<User> SystemFacade::createUser(const std::string& name, const std::string& role) {
    auto u = userManager_.createUser(name, role);
    notifyAndLog("User created: " + u->getName() + " (id " + std::to_string(u->getId()) + ")");
    return u;
}
std::shared_ptr<Task> SystemFacade::createTask(const std::string& title, const std::string& desc, PriorityStrategyPtr strat) {
    auto t = taskManager_.createTask(title, desc, strat);
    notifyAndLog("Task created: " + t->getTitle() + " (id " + std::to_string(t->getId()) + ")");
    return t;
}

bool SystemFacade::deleteUser(int userId) {
    auto u = userManager_.getUser(userId);
    if (!u) return false;
    // simple: do not reassign tasks automatically
    userManager_.removeUser(userId);
    notifyAndLog("User deleted id " + std::to_string(userId));
    return true;
}
bool SystemFacade::deleteTask(int taskId) {
    auto t = taskManager_.getTask(taskId);
    if (!t) return false;
    taskManager_.removeTask(taskId);
    notifyAndLog("Task deleted id " + std::to_string(taskId));
    return true;
}

std::shared_ptr<User> SystemFacade::getUser(int userId) { return userManager_.getUser(userId); }
std::shared_ptr<Task> SystemFacade::getTask(int taskId) { return taskManager_.getTask(taskId); }

bool SystemFacade::assignTaskToUser(int taskId, int userId) {
    auto t = taskManager_.getTask(taskId);
    auto u = userManager_.getUser(userId);
    if (!t || !u) return false;
    // if already assigned to someone else, remove previous link
    if (t->getAssignedUserId() != -1 && t->getAssignedUserId() != userId) {
        auto prev = userManager_.getUser(t->getAssignedUserId());
        if (prev) prev->removeTask(taskId);
    }
    AssignmentManager::assign(t, u);
    notifyAndLog("Assigned task " + std::to_string(taskId) + " to user " + std::to_string(userId));
    return true;
}

bool SystemFacade::unassignTask(int taskId) {
    auto t = taskManager_.getTask(taskId);
    if (!t) return false;
    int uid = t->getAssignedUserId();
    if (uid == -1) return false;
    auto u = userManager_.getUser(uid);
    if (u) AssignmentManager::unassign(t, u);
    notifyAndLog("Unassigned task " + std::to_string(taskId));
    return true;
}

void SystemFacade::printAllUsers() const {
    auto users = userManager_.allUsers();
    std::cout << "Users:\n";
    for (const auto& [id,u] : users) {
        std::cout << " - id:" << id << " name: " << u->getName() << " role: " << u->getRole() << "\n";
        std::cout << "   Tasks: ";
        for (int t : u->getAssignedTasks()) std::cout << t << " ";
        std::cout << "\n";
    }
}

void SystemFacade::printAllTasks() const {
    auto tasks = taskManager_.allTasks();
    std::cout << "Tasks:\n";
    for (const auto& [id,t] : tasks) {
        std::cout << " - id:" << id << " title: " << t->getTitle() << " status: " << to_string(t->getStatus())
                  << " priority: " << t->getPriority() << " assignedTo: " << t->getAssignedUserId() << "\n";
    }
}

void SystemFacade::printHistory() const {
    auto logs = HistoryLogger::instance().getLogs();
    std::cout << "History logs:\n";
    for (auto& l : logs) std::cout << l << "\n";
}

void SystemFacade::notifyAndLog(const std::string& msg) const {
    notifier_.publish(msg);
    HistoryLogger::instance().log(msg); 
}
