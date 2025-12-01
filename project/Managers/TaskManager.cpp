// Managers/TaskManager.cpp
#include "TaskManager.hpp"
#include <utility>

TaskManager::TaskManager(): nextId_(1) {}

std::shared_ptr<Task> TaskManager::createTask(const std::string& title, const std::string& desc, PriorityStrategyPtr strat) {
    int id = nextId_++;
    auto t = std::make_shared<Task>(id, title, desc, strat);
    tasks_[id] = t;
    return t;
}

std::shared_ptr<Task> TaskManager::getTask(int id) const {
    auto it = tasks_.find(id);
    if (it == tasks_.end()) return nullptr;
    return it->second;
}

bool TaskManager::removeTask(int id) {
    auto it = tasks_.find(id);
    if (it == tasks_.end()) return false;
    tasks_.erase(it);
    return true;
}

std::map<int,std::shared_ptr<Task>> TaskManager::allTasks() const { return tasks_; }
