// Core/PriorityStrategy.hpp
#pragma once
#include <memory>

class Task; // forward

class PriorityStrategy {
public:
    virtual ~PriorityStrategy() = default;
    // return an int priority; higher == more important
    virtual int calculatePriority(const Task& task) const = 0;
};
using PriorityStrategyPtr = std::shared_ptr<PriorityStrategy>;
