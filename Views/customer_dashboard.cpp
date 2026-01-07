#include "customer_dashboard.hpp"
#include <iostream>

using namespace std;

void listProducts(const vector<Product>& products) {
    for (const auto& p : products) {
        cout << p.getProductId() << " | "
             << p.getName() << " | "
             << p.getDescription() << " | "
             << p.getPrice() << " | Stock: "
             << p.getStock() << endl;
    }
}

void searchProduct(const vector<Product>& products) {
    string key;
    cout << "Enter product name: ";
    cin >> key;

    for (const auto& p : products) {
        if (p.getName().find(key) != string::npos) {
            cout << p.getName() << " - " << p.getPrice() << endl;
        }
    }
}

void CustomerDashboard::show(User* customer, vector<Product>& products) {
    int choice;

    do {
        cout << "\n--- Customer Dashboard ---\n";
        cout << "Welcome " << customer->getName() << endl;
        cout << "Address: " << customer->getAddress() << endl;
        cout << "\n1. View Products\n";
        cout << "2. Search Product\n";
        cout << "3. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listProducts(products);
                break;
            case 2:
                searchProduct(products);
                break;
        }
    } while (choice != 3);
}
