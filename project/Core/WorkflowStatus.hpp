// Core/WorkflowStatus.hpp
#pragma once
#include <string>

enum class WorkflowStatus {
    TODO,
    IN_PROGRESS,
    DONE
};

inline std::string to_string(WorkflowStatus s) {
    switch (s) {
        case WorkflowStatus::TODO: return "todo";
        case WorkflowStatus::IN_PROGRESS: return "in_progress";
        case WorkflowStatus::DONE: return "done";
    }
    return "unknown";
}
