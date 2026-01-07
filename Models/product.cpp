#include "product.hpp"

Product::Product()
    : productId(0), sellerId(0), name(""),
      description(""), price(0.0), stock(0) {}

Product::Product(int id, int sellerId,
                 const std::string& n,
                 const std::string& desc,
                 double p,
                 int s)
    : productId(id), sellerId(sellerId),
      name(n), description(desc),
      price(p), stock(s) {}

int Product::getId() const {
    return productId;
}

int Product::getSellerId() const {
    return sellerId;
}

std::string Product::getName() const {
    return name;
}

std::string Product::getDescription() const {
    return description;
}

double Product::getPrice() const {
    return price;
}

int Product::getStock() const {
    return stock;
}

void Product::setName(const std::string& n) {
    name = n;
}

void Product::setDescription(const std::string& d) {
    description = d;
}

void Product::updatePrice(double p) {
    price = p;
}

void Product::updateStock(int s) {
    stock = s;
}
