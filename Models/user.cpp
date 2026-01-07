#include "user.hpp"
#include "../Services/utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
User::User() {
    std::cout << "\n--- Create Account ---" << std::endl;

    // Validate Name
    do {
        std::cout << "Full Name (Letters only): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        if (!Validator::isValidName(name)) std::cout << "[!] Invalid name format.\n";
    } while (!Validator::isValidName(name));

    // Validate Email
    do {
        std::cout << "Email (e.g., user@example.com): ";
        std::cin >> email;
        if (!Validator::isValidEmail(email)) std::cout << "[!] Invalid email format.\n";
    } while (!Validator::isValidEmail(email));

    // Validate Password
    do {
        std::cout << "Password (min 6 chars, 1 letter, 1 number): ";
        std::cin >> password;
        if (!Validator::isValidPassword(password)) std::cout << "[!] Password too weak.\n";
    } while (!Validator::isValidPassword(password));

    // Validate Role
    do {
        std::cout << "Role (Customer/Seller): ";
        std::cin >> role;
        if (!Validator::isValidRole(role)) std::cout << "[!] Role must be 'Customer' or 'Seller'.\n";
    } while (!Validator::isValidRole(role));

    // Address (Simple non-empty check)
    std::cout << "Address: ";
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }

    std::getline(std::cin, address);

    if (address.empty()) {
        address = "N/A";
    }

    // Proceed to save to file...
    int id = AuthService::getNextId();

    std::ofstream outFile("Database/users.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << id << ":" << name << ":" << email << ":" << password << ":" << role << ":" << address << "\n";
        outFile.close();
        std::cout << "\nRegistration Successful! You can now login." << std::endl;
    } else {
        std::cerr << "Error: Could not open database file." << std::endl;
    }
}

User::User(int user_id, std::string user_name, std::string user_email, std::string user_password, std::string user_role, std::string user_address)
        : userId(user_id), name(user_name), email(user_email), password(user_password), role(user_role), address(user_address) {};


// Virtual Destructor
User::~User() {}

// Getters
int User::getUserId() const { return userId; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPassword() const { return password; }
std::string User::getRole() const { return role; }
std::string User::getAddress() const { return address; }