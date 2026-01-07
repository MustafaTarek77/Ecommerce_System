# E-Commerce Console App

Simple C++ console-based e-commerce application used for learning and demonstration. Supports basic user registration/login, seller product management, and simple customer views.

**Repository layout**
- **`main.cpp`**: application entry point.
- **`Models/`**: domain models (`User`, `Seller`, `Product`, `Order`, `Cart`, etc.).
- **`Services/`**: utilities and authentication helpers (validation, user loader).
- **`Views/`**: console menus and UI loops (login, dashboards).
- **`Database/`**: plain-text data files (`users.txt`, `products.txt`, `orders.txt`).

**Important data formats**
- `Database/users.txt` — each line: `id:name:email:password:role:address`
- `Database/products.txt` — each line: `id:name:description:price:quantity:sellerId`

This project stores data as colon-separated text files for simplicity.

**Features implemented**
- User sign up and login (roles: `Customer`, `Seller`).
- Seller dashboard: Add product, View all products (shows seller name), View my products, Update product, Delete product.
- Basic `Product` model and file-based persistence.

Build & Run
----------

Requirements
- A C++ compiler supporting C++17 (e.g., `g++` / MinGW on Windows, `g++` on Linux).

Build (Windows PowerShell example)
```powershell
g++ -std=c++17 -I. main.cpp Models/*.cpp Services/*.cpp Views/*.cpp -o .\app.exe
```

Build (Linux / macOS)
```bash
g++ -std=c++17 -I. main.cpp Models/*.cpp Services/*.cpp Views/*.cpp -o ./app
```

Run
```powershell
./app.exe    # Windows (PowerShell)
./app        # Linux / macOS
```
