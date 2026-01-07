#include "customer_dashboard.hpp"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include "../Services/utils.hpp"

using namespace std;


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");   
#endif
}

void waitForEnter() {
    cout << "\nPress Enter to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void listProducts(const vector<Product>& products) {
    clearScreen();

    cout << left
         << setw(5)  << "ID"
         << setw(15) << "Name"
         << setw(25) << "Description"
         << setw(10) << "Price"
         << setw(8)  << "Stock"
         << endl;

    cout << string(63, '-') << endl;

    for (const auto& p : products) {
        cout << left
             << setw(5)  << p.getId()
             << setw(15) << p.getName()
             << setw(25) << p.getDescription()
             << setw(10) << fixed << setprecision(2) << p.getPrice()
             << setw(8)  << p.getStock()
             << endl;
    }

    waitForEnter();
}




void searchProduct(const vector<Product>& products) {
    clearScreen();

    string key;
    cout << "Enter product name: ";
    cin >> key;

    cout << left
         << setw(5)  << "ID"
         << setw(15) << "Name"
         << setw(25) << "Description"
         << setw(10) << "Price"
         << setw(8)  << "Stock"
         << endl;

         cout << string(63, '-') << endl;
         
         bool found = false;
         
         for (const auto& p : products) {
             if (p.getName().find(key) != string::npos) {
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
            
            if (!found) {
                cout << "\nNo matching products found.\n";
            }
            
            waitForEnter();
        }
        
void filterByMax(const vector<Product>& products) {
            clearScreen();
        
            double maxPrice;
            cout << "Enter maximum price: ";
            cin >> maxPrice;
        
            cout << left
                 << setw(5)  << "ID"
                 << setw(15) << "Name"
                 << setw(25) << "Description"
                 << setw(10) << "Price"
                 << setw(8)  << "Stock"
                 << endl;
        
            cout << string(63, '-') << endl;
        
            bool found = false;
        
        
            for (const auto& p : products) {
                if (p.getPrice() <= maxPrice) {
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
            if (!found) {
                cout << "\nNo products found within the specified price range.\n";
            }
        
            waitForEnter();
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

    
    
    do {
        clearScreen();
        cout << "\n--- Customer Dashboard ---\n";
        cout << "Welcome " << customer->getName() << endl;
        cout << "\n1. View Products\n";
        cout << "2. Search Product\n";
        cout << "3. Filter by Max Price\n";
        cout << "4. Filter by Seller\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listProducts(products);
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
        }
    } while (choice != 5);
}
