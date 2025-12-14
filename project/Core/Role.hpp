#pragma once
#include <string>

enum class Role {
    ADMIN,        // Peut tout faire
    MEMBRE,       // Peut modifier
    OBSERVATEUR   // Lecture seule
};

inline std::string to_string(Role r) {
    switch (r) {
        case Role::ADMIN: return "Admin";
        case Role::MEMBRE: return "Membre";
        case Role::OBSERVATEUR: return "Observateur";
        default: return "Inconnu";
    }
}

inline Role role_from_string(const std::string& str) {
    if (str == "Admin" || str == "admin") return Role::ADMIN;
    if (str == "Membre" || str == "membre") return Role::MEMBRE;
    if (str == "Observateur" || str == "observateur") return Role::OBSERVATEUR;
    return Role::OBSERVATEUR;
}