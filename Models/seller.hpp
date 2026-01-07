#ifndef SELLER_HPP
#define SELLER_HPP

#include "user.hpp"
#include "../Models/product.hpp"
#include <string>
#include <vector>
#include <iostream>

class Seller : public User {
private:
    std::vector<Product> myProducts;  // In-memory products
    bool productsLoaded = false;

    Product* findProductById(int productId);
    int getNextProductId() const;


public:
    Seller(int user_id, std::string user_name, 
           std::string user_email, std::string user_password, 
           std::string user_role, std::string user_address);

    // Load / Save
    void loadMyProducts();
    void saveMyProducts() const;

    // Product operations
    void addProduct();
    void viewMyProducts() const;
    bool updateProduct(int productId);
    bool deleteProduct(int productId);
};

#endif
