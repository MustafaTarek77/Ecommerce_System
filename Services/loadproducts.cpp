#include<iostream>
#include<fstream>
#include<sstream>
#include <vector>
#include "../Models/product.hpp"


std::vector<Product> loadProducts(int sellerId) {
    std::vector<Product> products;
    std::ifstream file("Database/products.txt");
    
    if (!file.is_open()) {
        return products; // Return empty vector if file doesn't exist
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, sellerIdStr, name, desc, priceStr, stockStr;

        // Parse using the ':' delimiter
        std::getline(ss, idStr, ':');
        std::getline(ss, sellerIdStr, ':');
        std::getline(ss, name, ':');
        std::getline(ss, desc, ':');
        std::getline(ss, priceStr, ':');
        std::getline(ss, stockStr, ':');

        try {
            int id = std::stoi(idStr);
            int sId = std::stoi(sellerIdStr);
            double price = std::stod(priceStr);
            int stock = std::stoi(stockStr);

            if (sId == sellerId) {
                // Construct Product object and add to vector
                products.emplace_back(id, sId, name, desc, price, stock);
            }
        } catch (...) {
            continue; // Skip malformed lines
        }
    }

    file.close();
    return products;
}