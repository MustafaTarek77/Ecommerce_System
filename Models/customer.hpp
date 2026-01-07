#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "user.hpp"

class Customer : public User {
private:
    std::string phone;
    std::string address;

public:
    Customer();
    std::string getPhone() const;
    std::string getAddress() const;
};

#endif
