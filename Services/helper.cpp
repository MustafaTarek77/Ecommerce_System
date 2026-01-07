#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include "../Models/product.hpp"


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}



void printProductsTable(const std::vector<Product>& products) {
    clearScreen();

    std::cout << "========== PRODUCTS ==========\n\n";

    if (products.empty()) {
        std::cout << "No products to display.\n";
        waitForEnter();
        return;
    }

    // Table header
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(30) << "Description"
              << std::setw(10) << "Price"
              << std::setw(8)  << "Stock"
              << "\n";

    std::cout << std::string(74, '-') << "\n";

    // Table rows
    for (const auto& p : products) {
        std::cout << std::left
                  << std::setw(6)  << p.getId()
                  << std::setw(20) << p.getName().substr(0, 19)
                  << std::setw(30) << p.getDescription().substr(0, 29)
                  << std::setw(10) << std::fixed << std::setprecision(2) << p.getPrice()
                  << std::setw(8)  << p.getStock()
                  << "\n";
    }

    std::cout << "\nTotal products: " << products.size() << "\n";
    waitForEnter();
}
