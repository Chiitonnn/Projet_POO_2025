// Managers/TaskManager.hpp
#pragma once
#include <map>
#include <memory>
#include "../Core/Task.hpp"
#include "../Core/PriorityStrategy.hpp"

class TaskManager {
private:
    std::map<int, std::shared_ptr<Task>> tasks_;
    int nextId_;
public:
    TaskManager();
    std::shared_ptr<Task> createTask(const std::string& title, const std::string& desc, PriorityStrategyPtr strat);
    std::shared_ptr<Task> getTask(int id) const;
    bool removeTask(int id);
    std::map<int,std::shared_ptr<Task>> allTasks() const;
};
