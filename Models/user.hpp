#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include "limits"

class User {
protected:
    int userId;
    std::string name;
    std::string email;
    std::string password;
    std::string role;
    std::string address;

public:
    // Constructors
    User();
    User(int user_id, std::string user_name, std::string user_email, std::string user_password, std::string user_role, std::string user_address);
    
    // Destructor
    virtual ~User();

    // Getters & Setters
    int getUserId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPassword() const;
    std::string getRole() const;
    std::string getAddress() const;
};

#endif