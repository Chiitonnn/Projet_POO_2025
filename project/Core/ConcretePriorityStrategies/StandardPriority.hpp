// Core/ConcretePriorityStrategies/StandardPriority.hpp
#pragma once
#include "../PriorityStrategy.hpp"
#include "../Task.hpp"

// A simple priority: length of title + description length (demo)
class StandardPriority : public PriorityStrategy {
public:
    int calculatePriority(const Task& task) const override;
};
