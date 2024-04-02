#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define a class for the inventory item
class InventoryItem {
private:
    string name;
    int quantity;
    double price;

public:
    // Constructor
    InventoryItem(string _name, int _quantity, double _price) : name(_name), quantity(_quantity), price(_price) {}

    // Getter methods
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    // Setter methods
    void setName(string _name) { name = _name; }
    void setQuantity(int _quantity) { quantity = _quantity; }
    void setPrice(double _price) { price = _price; }
};

// Define a class for the inventory system
class InventorySystem {
private:
    vector<InventoryItem> inventory;

public:
    // Method to add an item to the inventory
    void addItem(const InventoryItem& item) {
        inventory.push_back(item);
    }

    // Method to display all items in the inventory
    void displayInventory() const {
        cout << "Inventory Items:" << endl;
        for (const auto& item : inventory) {
            cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: ₹ " << item.getPrice()<<"/-"<< endl;
        }
    }

    // Method to find and display an item by name
    void findItem(const string& name) const {
        for (const auto& item : inventory) {
            if (item.getName() == name) {
                cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: ₹ " << item.getPrice() <<"/-"<< endl;
                return;
            }
        }
        cout << "Sorry!! Item not found." << endl;
    }
};

int main() {
    InventorySystem inventorySystem;

    // Example: Adding items to the inventory
    inventorySystem.addItem(InventoryItem("Item1", 10, 5.99));
    inventorySystem.addItem(InventoryItem("Item2", 5, 10.50));

    // Example: Displaying all items in the inventory
    inventorySystem.displayInventory();

    // Example: Finding an item by name
    inventorySystem.findItem("Item1");

    return 0;
}
