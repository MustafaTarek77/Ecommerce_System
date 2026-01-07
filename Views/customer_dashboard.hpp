#ifndef CUSTOMER_DASHBOARD_HPP
#define CUSTOMER_DASHBOARD_HPP

#include "../Models/user.hpp"
#include "../Models/product.hpp"
#include <vector>

using namespace std;

class CustomerDashboard {
public:
    static void show(User* customer, vector<Product>& products);
};

#endif
