#pragma once
#include <string>

enum class WorkflowStatus {
    TODO,
    IN_PROGRESS,
    DONE
};

inline std::string to_string(WorkflowStatus s) {
    switch (s) {
        case WorkflowStatus::TODO: return "À faire";
        case WorkflowStatus::IN_PROGRESS: return "En cours";
        case WorkflowStatus::DONE: return "Terminé";
        default: return "Inconnu";
    }
}