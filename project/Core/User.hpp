// Core/User.hpp
#pragma once
#include <string>
#include <vector>

class User {
private:
    int id_;
    std::string name_;
    std::string role_;
    std::vector<int> assignedTasks_;
public:
    User(int id, std::string name, std::string role);
    int getId() const;
    const std::string& getName() const;
    const std::string& getRole() const;
    const std::vector<int>& getAssignedTasks() const;

    void setName(const std::string& n);
    void setRole(const std::string& r);
    void addTask(int taskId);
    void removeTask(int taskId);
};
