// Managers/UserManager.cpp
#include "UserManager.hpp"

UserManager::UserManager(): nextId_(1) {}

std::shared_ptr<User> UserManager::createUser(const std::string& name, const std::string& role) {
    int id = nextId_++;
    auto u = std::make_shared<User>(id, name, role);
    users_[id] = u;
    return u;
}

std::shared_ptr<User> UserManager::getUser(int id) const {
    auto it = users_.find(id);
    if (it == users_.end()) return nullptr;
    return it->second;
}

bool UserManager::removeUser(int id) {
    auto it = users_.find(id);
    if (it == users_.end()) return false;
    users_.erase(it);
    return true;
}

std::map<int,std::shared_ptr<User>> UserManager::allUsers() const { return users_; }
