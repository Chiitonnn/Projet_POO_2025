// Core/Task.hpp
#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include "WorkflowStatus.hpp"
#include "PriorityStrategy.hpp"

class Task {
private:
    int id_;
    std::string title_;
    std::string description_;
    WorkflowStatus status_;
    int assignedUserId_; // -1 if none
    int priority_;
    PriorityStrategyPtr priorityStrategy_;
    std::vector<std::string> history_;
public:
    Task(int id, std::string title, std::string desc, PriorityStrategyPtr strat);
    int getId() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    WorkflowStatus getStatus() const;
    int getAssignedUserId() const;
    int getPriority() const;

    void setTitle(const std::string& t);
    void setDescription(const std::string& d);
    void setStatus(WorkflowStatus s);
    void assignTo(int userId);
    void unassign();
    void recalcPriority();

    void addHistory(const std::string& entry);
    std::string historyString() const;
};
