// Core/User.cpp
#include "User.hpp"
#include <algorithm>

User::User(int id, std::string name, std::string role)
: id_(id), name_(std::move(name)), role_(std::move(role)) {}

int User::getId() const { return id_; }
const std::string& User::getName() const { return name_; }
const std::string& User::getRole() const { return role_; }
const std::vector<int>& User::getAssignedTasks() const { return assignedTasks_; }

void User::setName(const std::string& n) { name_ = n; }
void User::setRole(const std::string& r) { role_ = r; }
void User::addTask(int taskId) {
    assignedTasks_.push_back(taskId);
}
void User::removeTask(int taskId) {
    assignedTasks_.erase(std::remove(assignedTasks_.begin(), assignedTasks_.end(), taskId), assignedTasks_.end());
}
