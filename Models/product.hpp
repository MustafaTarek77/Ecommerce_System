#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include <string>


class Product {
private:
    int productId;
    int sellerId;
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

    // getters
    int getId() const;
    int getSellerId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    int getStock() const;

    // setters (return bool)
    bool setName(const std::string& n);
    bool setDescription(const std::string& d);
    bool updatePrice(double p);
    bool updateStock(int s);
};

#endif