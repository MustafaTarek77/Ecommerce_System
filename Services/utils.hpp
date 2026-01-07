#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include "../Models/user.hpp"

// Static utility class for Regex Validation
class Validator {
public:
    static bool isValidName(const std::string& name);
    static bool isValidEmail(const std::string& email);
    static bool isValidPassword(const std::string& pass);
    static bool isValidRole(const std::string& role);
};

// Functions for Authentication and Database Management
class AuthService {
public:
    static std::vector<User*> loadUsers();
    static bool authenticateUser(std::string email, std::string pass, std::string& role, std::string& name);
    static int getNextId();
    static void clearUserVector(std::vector<User*>& users);
};

#endif