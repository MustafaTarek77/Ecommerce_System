#include "menu.hpp"
#include "../Models/user.hpp"
#include "../Models/seller.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "customer_dashboard.hpp"
#include "../Services/utils.hpp"
#include "../Models/product.hpp"


Menu::Menu(std::vector<User*> users_vector): users(users_vector) {}
Menu::Menu(vector<User*> users_vector)
    : users(users_vector) 
{
    products = ProductUtils::loadProducts();
}

void Menu::displayMainMenu() {
    int choice;
    do {
        std::cout << "\n===============================" << std::endl;
        std::cout << "   WELCOME TO E-COMMERCE APP   " << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Sign Up" << std::endl;
        std::cout << "3. Logout" << std::endl;
        std::cout << "Selection: ";
        std::cin >> choice;

        switch (choice) {
            case 1: handleLogin(); break;
            case 2: handleSignUp(); break;
            case 3: std::cout << "Logout from the system..." << std::endl; break;
            default: std::cout << "Invalid choice!" << std::endl;
        }
    } while (choice != 3);
}

void Menu::handleLogin() {
    std::string email, pass;
    std::cout << "\n--- Login Page ---" << std::endl;
    std::cout << "Email: "; std::cin >> email;
    std::cout << "Password: "; std::cin >> pass;

    for (const auto& u : users) {
        // Accessing the private/protected members via getters
        if (u->getEmail() == email && u->getPassword() == pass) {
            std::cout << "\nLogin Successful! Welcome, " << u->getName() << std::endl;
            currUser = u;
            if (currUser->getRole() == "Customer") {
                CustomerDashboard::show(currUser, products);
            } else if (currUser->getRole() == "Seller") {
                sellerDashboard(currUser->getName());
            }
        }
    }

    std::cout << "\n[!] Invalid email or password." << std::endl;
}

void Menu::handleSignUp() {
    User* newUser= new User();
    users.push_back(newUser);
    currUser = newUser;
    if (currUser->getRole() == "Customer") {
        CustomerDashboard::show(currUser, products);
    } else if (currUser->getRole() == "Seller") {
        sellerDashboard(currUser->getName());
    }
}

// void Menu::customerDashboard(std::string name) {
//     std::cout << "\n--- Customer Dashboard (" << name << ") ---" << std::endl;
//     std::cout << "1. View Products\n2. View Cart\n3. Logout" << std::endl;
//     // Implementation for customer actions...
//     while(1){}
// }

void Menu::sellerDashboard(std::string name) {
    Seller s(currUser->getUserId(), currUser->getName(), currUser->getEmail(), currUser->getPassword(), currUser->getRole(), currUser->getAddress());
    int choice = 0;
    while (true) {
        std::cout << "\n--- Seller Dashboard (" << name << ") ---" << std::endl;
        std::cout << "1. Add Product\n2. View My Products\n3. Update Product\n4. Delete Product\n5. Logout" << std::endl;
        std::cout << "Selection: "; std::cin >> choice;
        switch (choice) {
            case 1: s.addProduct(); break;
            case 2: s.viewMyProducts(); break;
            case 3: {
                int pid; std::cout << "Product ID to update: "; std::cin >> pid;
                if (!s.updateProduct(pid)) std::cout << "Update failed (not found or not your product)." << std::endl;
                break;
            }
            case 4: {
                int pid; std::cout << "Product ID to delete: "; std::cin >> pid;
                if (!s.deleteProduct(pid)) std::cout << "Delete failed (not found or not your product)." << std::endl;
                else std::cout << "Product removed." << std::endl;
                break;
            }
            case 5: std::cout << "Logging out..." << std::endl; return;
            default: std::cout << "Invalid choice." << std::endl;
        }
    }
}