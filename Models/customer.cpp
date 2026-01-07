#include "customer.hpp"
#include <iostream>

Customer::Customer() : User() {
    std::cout << "Phone Number: ";
    std::cin >> phone;
    std::cout << "Address: ";
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::getline(std::cin, address);
    
}

std::string Customer::getPhone() const {
    return phone;
}
std::string Customer::getAddress() const {
    return address;
}