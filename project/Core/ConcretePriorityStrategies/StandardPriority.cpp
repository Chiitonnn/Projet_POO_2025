// Core/ConcretePriorityStrategies/StandardPriority.cpp
#include "StandardPriority.hpp"
#include "../Task.hpp"
#include <string>

int StandardPriority::calculatePriority(const Task& task) const {
    // simple heuristic
    int score = 0;
    score += static_cast<int>(task.getTitle().size() / 5);
    score += static_cast<int>(task.getDescription().size() / 50);
    if (task.getStatus() == WorkflowStatus::IN_PROGRESS) score += 2;
    if (task.getStatus() == WorkflowStatus::DONE) score -= 5;
    return score;
}
