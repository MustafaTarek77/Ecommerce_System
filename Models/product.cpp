#include "product.hpp"
#include <stdexcept>

// ---------------- Constructors ----------------
Product::Product()
    : productId(0), sellerId(0), name(""),
      description(""), price(0.0), stock(0) {}

Product::Product(int id, int sellerId,
                 const std::string& n,
                 const std::string& desc,
                 double p,
                 int s)
{
    // Use setters to enforce validation
    productId = id;          // ID is trusted from storage
    this->sellerId = sellerId;

    setName(n);
    setDescription(desc);
    updatePrice(p);
    updateStock(s);
}


int Product::getId() const { return productId; }
int Product::getSellerId() const { return sellerId; }
std::string Product::getName() const { return name; }
std::string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }


bool Product::setName(const std::string& n) {
    if (n.empty() || n.length() > 100)
        return false;
    name = n;
    return true;
}

bool Product::setDescription(const std::string& d) {
    if (d.empty())
        return false;
    description = d;
    return true;
}

bool Product::updatePrice(double p) {
    if (p <= 0)
        return false;
    price = p;
    return true;
}

bool Product::updateStock(int s) {
    if (s < 0)
        return false;
    stock = s;
    return true;
}