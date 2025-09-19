# E-shop Application (C++)

## Overview
Object-Oriented Programming project for an e-shop application.  
Supports two types of users:
- **Admins**: manage products (add, edit, delete, view statistics).  
- **Customers**: search products, add to cart, complete orders, and view order history.  

## Features
- User authentication (login/registration).
- Product management (CRUD operations).
- Shopping cart with real-time updates.
- Order history saved to files.
- Data persistence using file I/O.
- Implemented with OOP principles: encapsulation, inheritance, polymorphism.

## Technologies
- C++  
- STL (`unordered_map`, `vector`)  
- File I/O  
- GitHub Classroom  

## How to Run
```bash
# Build (from repo root)
make

# Run
./oop24 files/categories.txt files/products.txt files/users.txt
