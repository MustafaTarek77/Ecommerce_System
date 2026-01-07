#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include "../Models/user.hpp"

class Menu {
public:
    Menu(std::vector<User*> users_vector);
    // Main entry point for the UI
    void displayMainMenu();

private:
    User* currUser=nullptr;
    std::vector<User*> users;
    // Authentication Sub-menus
    void handleLogin();
    void handleSignUp();
    
    // Role-based Dashboards
    void customerDashboard(std::string name);
    void sellerDashboard(std::string name);
};

#endif