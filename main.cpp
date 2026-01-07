#include "Views/menu.hpp"
#include "./Models/user.hpp"
#include <iostream>
#include <vector>
#include "./Services/utils.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Ensure the folder exists and required files exist
void ensureDatabaseStructure() {
    std::string dbFolder = "Database";

    // Ensure the Database folder exists
    if (!fs::exists(dbFolder)) {
        fs::create_directories(dbFolder);
    }

    // Ensure required files exist
    std::vector<std::string> files = {
        "Database/users.txt",
        "Database/products.txt",
        "Database/orders.txt"
    };

    for (const auto& file : files) {
        if (!fs::exists(file)) {
            std::ofstream out(file);
            if (out.is_open()) {
                out.close();
            } else {
                std::cerr << "Failed to create file: " << file << std::endl;
            }
        }
    }

    std::cout<<"Project initialized successfully."<<std::endl;
}

int main() {
    ensureDatabaseStructure();
    std::vector<User*> users = AuthService::loadUsers();
    Menu app(users);
    app.displayMainMenu();

    AuthService::clearUserVector(users);
    return 0;
}
