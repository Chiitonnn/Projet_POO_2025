// Core/Task.cpp
#include "Task.hpp"
#include <chrono>
#include <iomanip>

static std::string nowTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

Task::Task(int id, std::string title, std::string desc, PriorityStrategyPtr strat)
: id_(id), title_(std::move(title)), description_(std::move(desc)),
  status_(WorkflowStatus::TODO), assignedUserId_(-1),
  priorityStrategy_(std::move(strat)), priority_(0)
{
    recalcPriority();
    addHistory("Created");
}

int Task::getId() const { return id_; }
const std::string& Task::getTitle() const { return title_; }
const std::string& Task::getDescription() const { return description_; }
WorkflowStatus Task::getStatus() const { return status_; }
int Task::getAssignedUserId() const { return assignedUserId_; }
int Task::getPriority() const { return priority_; }

void Task::setTitle(const std::string& t) {
    title_ = t;
    recalcPriority();
    addHistory("Title changed");
}
void Task::setDescription(const std::string& d) {
    description_ = d;
    recalcPriority();
    addHistory("Description changed");
}
void Task::setStatus(WorkflowStatus s) {
    status_ = s;
    recalcPriority();
    addHistory(std::string("Status changed to ") + to_string(s));
}
void Task::assignTo(int userId) {
    assignedUserId_ = userId;
    addHistory("Assigned to user id " + std::to_string(userId));
}
void Task::unassign() {
    assignedUserId_ = -1;
    addHistory("Unassigned");
}
void Task::recalcPriority() {
    if (priorityStrategy_) priority_ = priorityStrategy_->calculatePriority(*this);
    else priority_ = 0;
}

void Task::addHistory(const std::string& entry) {
    history_.push_back(nowTime() + " - " + entry);
}
std::string Task::historyString() const {
    std::ostringstream os;
    for (const auto& e : history_) os << e << "\n";
    return os.str();
}
