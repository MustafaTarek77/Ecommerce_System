#include "Views/menu.hpp"
#include "./Models/user.hpp"
#include <iostream>
#include <vector>
#include "./Services/utils.hpp"

int main() {
    std::vector<User*> users = AuthService::loadUsers();
    Menu app(users);
    app.displayMainMenu();
    AuthService::clearUserVector(users);
    return 0;
}