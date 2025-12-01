// Managers/AssignmentManager.cpp
#include "AssignmentManager.hpp"

bool AssignmentManager::assign(std::shared_ptr<Task> task, std::shared_ptr<User> user) {
    if (!task || !user) return false;
    int tid = task->getId();
    int uid = user->getId();
    if (task->getAssignedUserId() == uid) return true;
    if (task->getAssignedUserId() != -1) {
        // remove from previous user is caller responsibility
    }
    task->assignTo(uid);
    user->addTask(tid);
    return true;
}
bool AssignmentManager::unassign(std::shared_ptr<Task> task, std::shared_ptr<User> user) {
    if (!task || !user) return false;
    int tid = task->getId();
    task->unassign();
    user->removeTask(tid);
    return true;
}
