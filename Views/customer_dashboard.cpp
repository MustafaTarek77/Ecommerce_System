#include "customer_dashboard.hpp"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include "customer_dashboard.hpp"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>
#include <fstream>
#include <map>
#include "../Services/utils.hpp"
#include "../Services/helper.hpp"

using namespace std;


void listProducts(const vector<Product>& products) {
    printProductsTable(products);
}

void addToCart(vector<Product>& products, vector<Product>& cart) {
    cout << "Add product to cart? (y/n): ";
    char c; cin >> c;
    if (c != 'y' && c != 'Y') return;
    int pid;
    cout << "Enter product ID to add: ";
    cin >> pid;
    auto it = find_if(products.begin(), products.end(), [pid](const Product& p){ return p.getId() == pid; });
    if (it == products.end()) {
        cout << "Product not found." << endl;
        waitForEnter();
        return;
    }
    if (it->getStock() <= 0) {
        cout << "Product out of stock." << endl;
        waitForEnter();
        return;
    }
    cart.push_back(*it);
    cout << "Product added to cart." << endl;
    waitForEnter();
}

static int getNextOrderId() {
    std::ifstream in("Database/orders.txt");
    if (!in) return 1;
    string line; int lastId = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto pos = line.find(':');
        if (pos != string::npos) {
            try { lastId = stoi(line.substr(0, pos)); } catch(...) { }
        }
    }
    return lastId + 1;
}

static void saveOrderToFile(int orderId, User* customer, const map<int,int>& items, double total) {
    std::ofstream out("Database/orders.txt", std::ios::app);
    if (!out) {
        cout << "Failed to open orders file for writing." << endl;
        return;
    }
    out << orderId << ":" << customer->getUserId() << ":";
    bool first = true;
    for (auto &kv : items) {
        if (!first) out << ",";
        out << kv.first << "x" << kv.second;
        first = false;
    }
    out << ":" << fixed << setprecision(2) << total << ":Cash:Completed\n";
    out.close();
}

void viewCart(vector<Product>& cart, vector<Product>& products, User* customer) {
    clearScreen();
    if (cart.empty()) {
        cout << "Your cart is empty." << endl;
        waitForEnter();
        return;
    }

    map<int,int> counts;
    for (const auto& p : cart) counts[p.getId()]++;

    double total = 0.0;
    cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << setw(12) << "Subtotal" << endl;
    cout << string(60, '-') << endl;
    for (auto &kv : counts) {
        int pid = kv.first; int qty = kv.second;
        auto it = find_if(products.begin(), products.end(), [pid](const Product& p){ return p.getId() == pid; });
        if (it == products.end()) continue;
        double sub = it->getPrice() * qty;
        total += sub;
        cout << left << setw(5) << it->getId() << setw(20) << it->getName() << setw(10) << qty << setw(10) << fixed << setprecision(2) << it->getPrice() << setw(12) << fixed << setprecision(2) << sub << endl;
    }
    cout << string(60, '-') << endl;
    cout << "Total: " << fixed << setprecision(2) << total << endl;

    cout << "\nOptions: 1) Checkout (Cash)  2) Clear Cart  3) Back\n";
    int opt; cout << "Choice: "; cin >> opt;
    if (opt == 2) {
        cart.clear();
        cout << "Cart cleared." << endl;
        waitForEnter();
        return;
    }
    if (opt != 1) return;

    cout << "Proceed to cash payment? (y/n): "; char c; cin >> c;
    if (c != 'y' && c != 'Y') return;

    
    int oid = getNextOrderId();
    saveOrderToFile(oid, customer, counts, total);
    cout << "Order saved (ID: " << oid << ")." << endl;

    for (auto &kv : counts) {
        int pid = kv.first; int qty = kv.second;
        auto it = find_if(products.begin(), products.end(), [pid](Product& p){ return p.getId() == pid; });
        if (it != products.end()) {
            it->updateStock(it->getStock() - qty);
        }
    }

    cart.clear();
    waitForEnter();
}


void searchProduct(const vector<Product>& products) {
    clearScreen();


    string key;
    cout << "Enter product name: ";
    cin >> key;

    vector<Product> filteredProducts;         
         
         for (const auto& p : products) {
             if (p.getName().find(key) != string::npos) {
                 filteredProducts.push_back(p);
                }
            }
            printProductsTable(filteredProducts);
            
            if (filteredProducts.empty()) {
        cout << "\nNo matching products found.\n";
    }
            
        }
        
void filterByMax(const vector<Product>& products) {
        clearScreen();

        
            double maxPrice;
            cout << "Enter maximum price: ";
            cin >> maxPrice;
            vector<Product> filteredProducts;         
        
        
            for (const auto& p : products) {
                if (p.getPrice() <= maxPrice) {
                    filteredProducts.push_back(p);                    
                }
            }
            printProductsTable(filteredProducts);
               if (filteredProducts.empty()) {
        cout << "\nNo matching products found.\n";
    }
        
        }


void filterBySeller(const vector<Product>& products) {
    clearScreen();

    string key;
    cout << "Enter seller name: ";
    if (cin.peek() == '\n') cin.ignore();
    std::getline(cin, key);

    auto toLower = [](const string &s){ string out = s; std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c){ return std::tolower(c); }); return out; };

    vector<User*> users = AuthService::loadUsers();
    int sellerId = -1;
    string keyL = toLower(key);
    for (auto u : users) {
        if (u->getRole() == "Seller") {
            if (toLower(u->getName()).find(keyL) != string::npos) {
                sellerId = u->getUserId();
                break;
            }
        }
    }

    AuthService::clearUserVector(users);

    cout << left
         << setw(5)  << "ID"
         << setw(15) << "Name"
         << setw(25) << "Description"
         << setw(10) << "Price"
         << setw(8)  << "Stock"
         << endl;

         cout << string(63, '-') << endl;
         
        if (sellerId == -1) {
            cout << "\nSeller not found by that name.\n";
            waitForEnter();
            return;
        }

        bool found = false;
        for (const auto& p : products) {
            if (p.getSellerId() == sellerId) {
                cout << left
                     << setw(5)  << p.getId()
                     << setw(15) << p.getName()
                     << setw(25) << p.getDescription()
                     << setw(10) << fixed << setprecision(2) << p.getPrice()
                     << setw(8)  << p.getStock()
                     << endl;
                found = true;
            }
        }

        if (!found) cout << "\nNo products found for this seller.\n";
            
            waitForEnter();
        }

        
void CustomerDashboard::show(User* customer, vector<Product>& products) {
            int choice;
            vector<Product> cart; 

    do {
        clearScreen();
        cout << "\n--- Customer Dashboard ---\n";
        cout << "Welcome " << customer->getName() << endl;
        cout << "\n1. View Products\n";
        cout << "2. Search Product\n";
        cout << "3. Filter by Max Price\n";
        cout << "4. Filter by Seller\n";
        cout << "5. View Cart\n";
        cout << "6. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listProducts(products);
                addToCart(products, cart);
                break;
            case 2:
                searchProduct(products);
                break;
            case 3:
                filterByMax(products);
                break;
            case 4:
                filterBySeller(products);
                break;
            case 5:
                viewCart(cart, products, customer);
                break;
        }
    } while (choice != 6);
}
