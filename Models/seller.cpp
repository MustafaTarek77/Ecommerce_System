#include "seller.hpp"
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include "../Services/helper.hpp"

Seller::Seller(int user_id, std::string user_name, std::string user_email,
               std::string user_password, std::string user_role, std::string user_address)
    : User(user_id, user_name, user_email, user_password, user_role, user_address) {}



void Seller::loadMyProducts() {
    if (productsLoaded) return; // load once

    std::ifstream in("Database/products.txt");
    if (!in.is_open()) return;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idStr, sellerIdStr, name, desc, priceStr, qtyStr;

        std::getline(ss, idStr, ':');
        std::getline(ss, sellerIdStr, ':');
        std::getline(ss, name, ':');
        std::getline(ss, desc, ':');
        std::getline(ss, priceStr, ':');
        std::getline(ss, qtyStr, ':');

        int sellerId = std::stoi(sellerIdStr);
        if (sellerId != this->getUserId()) continue;

        int id = std::stoi(idStr);
        double price = std::stod(priceStr);
        int qty = std::stoi(qtyStr);

        myProducts.emplace_back(id, sellerId, name, desc, price, qty);
    }
    in.close();
    productsLoaded = true;
}

void Seller::saveMyProducts() const {
    std::ofstream out("Database/products.txt");
    if (!out.is_open()) {
        std::cerr << "Failed to save products." << std::endl;
        return;
    }

    for (const auto& p : myProducts) {
        out << p.getId() << ":"
            << p.getSellerId() << ":"
            << p.getName() << ":"
            << p.getDescription() << ":"
            << p.getPrice() << ":"
            << p.getStock() << "\n";
    }
    out.close();
}

int Seller::getNextProductId() const {
    if (myProducts.empty()) return 1;
    return myProducts.back().getId() + 1;
}

Product* Seller::findProductById(int productId) {
    for (auto& p : myProducts) {
        if (p.getId() == productId)
            return &p; // return address of the product
    }
    return nullptr;
}

void Seller::addProduct() {
    std::string name, description;
    double price;
    int qty;

    Product temp;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n--- Add Product ---\n";

    // ---------- Name ----------
    do {
        std::cout << "Product Name: ";
        std::getline(std::cin, name);
        if (!temp.setName(name))
            std::cout << "Invalid name. Try again.\n";
    } while (!temp.setName(name));

    // ---------- Description ----------
    do {
        std::cout << "Description: ";
        std::getline(std::cin, description);
        if (!temp.setDescription(description))
            std::cout << "Invalid description. Try again.\n";
    } while (!temp.setDescription(description));

    // ---------- Price ----------
    do {
        std::cout << "Price (> 0): ";
        std::cin >> price;
        if (!temp.updatePrice(price))
            std::cout << "Invalid price. Try again.\n";
    } while (!temp.updatePrice(price));

    // ---------- Quantity ----------
    do {
        std::cout << "Quantity (>= 0): ";
        std::cin >> qty;
        if (!temp.updateStock(qty))
            std::cout << "Invalid quantity. Try again.\n";
    } while (!temp.updateStock(qty));

    int newId = getNextProductId();

    myProducts.emplace_back(
        newId,
        getUserId(),
        temp.getName(),
        temp.getDescription(),
        temp.getPrice(),
        temp.getStock()
    );

    std::cout << "Product added successfully.\n"
              << "ID: " << newId
              << " | Name: " << temp.getName() << std::endl;

    waitForEnter();
}

bool Seller::updateProduct(int productId) {
    Product* p = findProductById(productId);
    if (!p) {
        std::cout << "Product not found.\n";
        return false;
    }

    double price;
    int stock;

    // ---------- Price ----------
    do {
        std::cout << "New price (> 0): ";
        std::cin >> price;
        if (!p->updatePrice(price))
            std::cout << "Invalid price. Try again.\n";
    } while (!p->updatePrice(price));

    // ---------- Stock ----------
    do {
        std::cout << "New stock (>= 0): ";
        std::cin >> stock;
        if (!p->updateStock(stock))
            std::cout << "Invalid stock. Try again.\n";
    } while (!p->updateStock(stock));

    std::cout << "Product updated successfully.\n";
    waitForEnter();
    return true;
}


void Seller::viewMyProducts() const {
   printProductsTable(myProducts);
}

bool Seller::deleteProduct(int productId) {
    Product* p = findProductById(productId);
    if (!p) {
        std::cout << "Product not found." << std::endl;
        return false;
    }
    myProducts.erase(
        std::remove_if(myProducts.begin(), myProducts.end(),
                       [productId](const Product& prod) { return prod.getId() == productId; }),
        myProducts.end()
    );

    std::cout << "Product deleted succesfully." << std::endl;
    waitForEnter();
    return true;
}

