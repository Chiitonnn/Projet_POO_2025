// Managers/UserManager.hpp
#pragma once
#include <map>
#include <memory>
#include "../Core/User.hpp"

class UserManager {
private:
    std::map<int, std::shared_ptr<User>> users_;
    int nextId_;
public:
    UserManager();
    std::shared_ptr<User> createUser(const std::string& name, const std::string& role);
    std::shared_ptr<User> getUser(int id) const;
    bool removeUser(int id);
    std::map<int,std::shared_ptr<User>> allUsers() const;
};
