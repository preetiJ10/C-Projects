#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>   // for cin.ignore
#define NOMINMAX

#include <windows.h>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;

public:
    Bill(string item = "", int rate = 0, int quant = 0)
        : Item(item), Rate(rate), Quantity(quant) {}

    string getItem() const { return Item; }
    int getRate() const { return Rate; }
    int getQuant() const { return Quantity; }

    void setItem(const string& item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    // Convert to CSV format
    string toCSV() const {
        stringstream ss;
        ss << Item << "," << Rate << "," << Quantity;
        return ss.str();
    }

    // Load from CSV line
    static Bill fromCSV(const string& line) {
        stringstream ss(line);
        string item;
        int rate, quant;

        getline(ss, item, ',');
        ss >> rate;
        ss.ignore(); // skip comma
        ss >> quant;

        return Bill(item, rate, quant);
    }
};

// Global inventory
vector<Bill> inventory;

// Load items from file
void loadInventory() {
    inventory.clear();
    ifstream in("Bill.txt");   // local file
    string line;
    while (getline(in, line)) {
        if (!line.empty())
            inventory.push_back(Bill::fromCSV(line));
    }
    in.close();
}

// Save items back to file
void saveInventory() {
    ofstream out("Bill.txt", ios::trunc);
    for (const auto& b : inventory) {
        out << b.toCSV() << endl;
    }
    out.close();
}

// Add new items to stock
void addItem() {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Back" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            getline(cin, item);  // multi-word input supported

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inventory.push_back(Bill(item, rate, quant));
            saveInventory();

            cout << "\tItem Added Successfully!" << endl;
            Sleep(1500);
        }
        else if (choice == 2) {
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(1500);
        }
    }
}

// Show available stock
void viewStock() {
    system("cls");
    cout << "\tAvailable Stock" << endl;
    cout << "\t---------------------------" << endl;
    cout << "\tItem\tRate\tQuantity" << endl;

    for (const auto& b : inventory) {
        cout << "\t" << b.getItem() << "\t" << b.getRate()
            << "\t" << b.getQuant() << endl;
    }
    cout << endl;
    system("pause");
}

// Buy items & print bill
void printBill() {
    int total = 0;
    bool close = false;

    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Buy Item" << endl;
        cout << "\t2. Checkout" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string item;
            int quant;

            cout << "\tEnter Item Name: ";
            getline(cin, item);

            cout << "\tEnter Quantity: ";
            cin >> quant;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            bool found = false;
            for (auto& b : inventory) {
                if (b.getItem() == item) {
                    found = true;
                    if (quant <= b.getQuant()) {
                        int amount = b.getRate() * quant;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << b.getItem() << "\t " << b.getRate()
                            << "\t " << quant << "\t " << amount << endl;

                        b.setQuant(b.getQuant() - quant);
                        total += amount;
                        saveInventory();
                    }
                    else {
                        cout << "\tSorry, not enough stock for " << item << "!" << endl;
                    }
                    break;
                }
            }
            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }
            Sleep(2000);
        }
        else if (choice == 2) {
            close = true;
            cout << "\tCheckout..." << endl;
            Sleep(1500);
        }
    }

    system("cls");
    cout << endl << endl;
    cout << "\t Total Bill ----------------- : " << total << endl << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(3000);
}

// Main menu
int main() {
    loadInventory();
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. View Stock" << endl;
        cout << "\t3. Print Bill" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (val == 1) {
            system("cls");
            addItem();
        }
        else if (val == 2) {
            viewStock();
        }
        else if (val == 3) {
            printBill();
        }
        else if (val == 4) {
            exit = true;
            cout << "\tGoodbye!" << endl;
            Sleep(1500);
        }
    }
    return 0;
}