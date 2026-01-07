#include "seller.hpp"
#include <fstream>
#include <sstream>
#include <limits>
#include <unordered_map>


Seller::Seller(int user_id, std::string user_name, std::string user_email, std::string user_password, std::string user_role, std::string user_address)
    : User(user_id, user_name, user_email, user_password, user_role, user_address) {}


#include <fstream>
#include <sstream>
#include <limits>

void Seller::addProduct() {
    std::string name, description, line;
    double price = 0.0;
    int qty = 0;
    int lastId = 0;

    std::cout << "\n--- Add Product ---" << std::endl;

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Product Name: ";
    std::getline(std::cin, name);

    std::cout << "Description: ";
    std::getline(std::cin, description);

    std::cout << "Price: ";
    std::cin >> price;

    std::cout << "Quantity: ";
    std::cin >> qty;

    /* ---------------------------------
       Step 1: Get last product ID
       --------------------------------- */
    std::ifstream in("Database/products.txt");
    if (in.is_open()) {
        while (std::getline(in, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string idStr;
            std::getline(ss, idStr, ':');
            lastId = std::stoi(idStr);
        }
        in.close();
    }

    int newProductId = lastId + 1;

    // Save product
    std::ofstream out("Database/products.txt", std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Error: cannot open products file." << std::endl;
        return;
    }

    out << newProductId << ":"
        << this->getUserId() << ":"
        << name << ":"
        << description << ":"
        << price << ":"
        << qty << "\n";

    out.close();

    std::cout << "Product added successfully. Product Name = "
              << name << std::endl;
}


void Seller::viewMyProducts() const {
    
}

bool Seller::updateProduct(int productId) {
   
}

bool Seller::deleteProduct(int productId) {
   
}
