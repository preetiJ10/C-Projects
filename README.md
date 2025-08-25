# Supermarket Billing System

A simple **console-based Supermarket Billing System** written in C++.  
This project simulates a basic point-of-sale system where you can manage inventory, purchase items, and generate bills.

---

## Features

- Add new items to the inventory.
- View current stock of items.
- Purchase items and calculate the total bill.
- Multi-word item names supported (e.g., "Green Apple").
- Inventory is stored persistently in a local file (`Bill.txt`).
- Console menu-driven interface for easy navigation.

---

## How to Run

1. **Clone the repository:**

```bash
git clone https://github.com/YourUsername/SupermarketBillingSystem.git
Compile the program (using g++ or Visual Studio):

g++ SuperMarket.cpp -o billing.exe


Run the program:

billing.exe


Follow the menu to Add Item, View Stock, Print Bill, or Exit.

File Storage

The inventory is saved in a local file Bill.txt in the project folder.

Format:

ItemName,Rate,Quantity
Apple,50,10
Milk,20,5


Quantities update automatically after purchases.

Learning Outcomes

C++ basics: classes, objects, functions, and data types.

Using vectors and strings for data storage and manipulation.

File I/O with ifstream and ofstream.

Menu-driven programs and input validation.

Debugging issues like infinite loops and Windows macro conflicts.

Basic real-world problem solving (simulating a point-of-sale system).
