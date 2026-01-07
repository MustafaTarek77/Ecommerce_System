#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;
// --- Validator Implementations ---

bool Validator::isValidName(const std::string& name) {
    const std::regex pattern("^[a-zA-Z\\s]{2,50}$");
    return std::regex_match(name, pattern);
}

bool Validator::isValidEmail(const std::string& email) {
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool Validator::isValidPassword(const std::string& pass) {
    const std::regex pattern("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{6,}$");
    return std::regex_match(pass, pattern);
}

bool Validator::isValidRole(const std::string& role) {
    return (role == "Customer" || role == "Seller");
}

// --- AuthService Implementations ---

bool AuthService::authenticateUser(std::string email, std::string pass, std::string& role, std::string& name) {
    std::ifstream file("Database/users.txt");
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, uName, uEmail, uPass, uRole;
        
        // Using ':' as the delimiter based on your logic
        std::getline(ss, id, ':');
        std::getline(ss, uName, ':');
        std::getline(ss, uEmail, ':');
        std::getline(ss, uPass, ':');
        std::getline(ss, uRole, ':');

        if (uEmail == email && uPass == pass) {
            role = uRole;
            name = uName;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

int AuthService::getNextId() {
    std::ifstream file("Database/users.txt");
    std::string line;
    int maxId = 0;

    if (!file.is_open()) return 1000; 

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string idStr;
        // Standardized to ':' to match authenticateUser
        if (std::getline(ss, idStr, ':')) {
            try {
                int currentId = std::stoi(idStr);
                if (currentId > maxId) {
                    maxId = currentId;
                }
            } catch (...) {
                continue; 
            }
        }
    }
    file.close();
    return (maxId == 0) ? 1000 : maxId + 1;
}

std::vector<User*> AuthService::loadUsers() {
    std::vector<User*> users;
    std::ifstream file("Database/users.txt");
    
    if (!file.is_open()) {
        return users; // Return empty vector if file doesn't exist
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name, email, pass, role, address;

        // Parse using the ':' delimiter
        std::getline(ss, idStr, ':');
        std::getline(ss, name, ':');
        std::getline(ss, email, ':');
        std::getline(ss, pass, ':');
        std::getline(ss, role, ':');
        std::getline(ss, address, ':');

        try {
            int id = std::stoi(idStr);
            // Construct User object and add to vector
            users.push_back(new User(id, name, email, pass, role, address));
        } catch (...) {
            continue; // Skip malformed lines
        }
    }

    file.close();
    return users;
}

void AuthService::clearUserVector(std::vector<User*>& users) {
    for (User* u : users) {
        delete u; // Free the memory allocated with 'new'
    }
    users.clear(); // Remove the now-dangling pointers from the vector
}

std::vector<Product> ProductUtils::loadProducts() {
    vector<Product> products;
    ifstream file("Database/products.txt");

    if (!file.is_open()) {
        return products;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string pid, sid, name, desc, price, stock;

        getline(ss, pid, ':');
        getline(ss, sid, ':');
        getline(ss, name, ':');
        getline(ss, desc, ':');
        getline(ss, price, ':');
        getline(ss, stock, ':');

        try {
            products.push_back(
                Product(
                    stoi(pid),
                    stoi(sid),
                    name,
                    desc,
                    stod(price),
                    stoi(stock)
                )
            );
        } catch (...) {
            continue;
        }
    }

    file.close();
    return products;
}
