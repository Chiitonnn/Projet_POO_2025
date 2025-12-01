// Managers/AssignmentManager.hpp
#pragma once
#include "../Core/Task.hpp"
#include "../Core/User.hpp"
#include <memory>

class AssignmentManager {
public:
    static bool assign(std::shared_ptr<Task> task, std::shared_ptr<User> user);
    static bool unassign(std::shared_ptr<Task> task, std::shared_ptr<User> user);
};
