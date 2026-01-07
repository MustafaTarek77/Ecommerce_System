#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
private:
    int productId;
    int sellerId;              // ✅ owner of the product
    std::string name;
    std::string description;
    double price;
    int stock;

public:
    Product();
    Product(int id, int sellerId,
            const std::string& n,
            const std::string& desc,
            double p,
            int s);

    // Getters
    int getId() const;
    int getSellerId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    int getStock() const;

    // Setters / Updaters
    void setName(const std::string& n);
    void setDescription(const std::string& d);
    void updatePrice(double p);
    void updateStock(int s);
};

#endif
