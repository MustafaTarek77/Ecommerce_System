 #ifndef SELLER_HPP
 #define SELLER_HPP

#include "user.hpp"
#include <string>
#include <vector>
#include <iostream>

class Seller : public User {
private:
public:
    Seller(int user_id, std::string user_name, 
        std::string user_email, std::string user_password, 
        std::string user_role, std::string user_address);
    void addProduct();
    void viewMyProducts() const;
    bool updateProduct(int productId);
    bool deleteProduct(int productId);
};

#endif
