#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a class for the inventory item
class InventoryItem
{
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
class InventorySystem
{
private:
    vector<InventoryItem> inventory;

public:
    void findItem(const string &name) const
    {

        if (inventory.empty())
        {
            cout << "No Item present currently." << endl;
            return;
        }

        for (const auto &item : inventory)
        {
            if (item.getName() == name)
            {
                cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: $" << item.getPrice() << endl;
                return;
            }
        }
        cout << "Item not present currently." << endl;
    }

    // Method to add an item to the inventory
    void addItem(const InventoryItem &item)
    {
        // Check if the item already exists in the inventory
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            if (inventory[i].getName() == item.getName())
            {
                // Item found, update its quantity
                int quantity;
                cout << "Enter the number of " + item.getName() + "s to be added: ";
                cin >> quantity;

                int currQuantity = inventory[i].getQuantity();
                inventory[i].setQuantity(currQuantity + quantity);

                cout << "Quantity added to " << item.getName() << endl;
                cout << "New Quantity: " << inventory[i].getQuantity() << endl;
                cout << endl;
                return;
            }
        }

        // Item not found, add it to the inventory
        cout << "Item not found in inventory. Adding new item..." << endl;
        inventory.push_back(item);
        cout << "New Item " << item.getName() << " Added" << endl;
        cout << endl;
    }

    // Method to display all items in the inventory
    void displayInventory() const
    {
        cout << "Inventory Items:" << endl;
        for (const auto &item : inventory)
        {
            cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: $" << item.getPrice() << endl;
        }
    }

    // Method to find and display an item by name

    // Method to sell item
    void sellItem(const string &name)
    {
        // Find the item in the inventory
        auto it = std::find_if(inventory.begin(), inventory.end(), [&](const InventoryItem &item)
                               { return item.getName() == name; });

        // Check if the item was found
        if (it != inventory.end())
        {
            int quantity;
            cout << "Enter quantity to sell: ";
            cin >> quantity;

            int currQuantity = it->getQuantity();

            // Validate the quantity
            while (quantity > currQuantity || quantity <= 0)
            {
                cout << "Please enter a valid quantity to sell (<= " << currQuantity << "): ";
                cin >> quantity;
            }

            // Update the quantity
            it->setQuantity(currQuantity - quantity);

            // Display sale information
            cout << "Item " << name << " successfully sold!" << endl;
            cout << "Total Amount (Including taxes): Rs." << (it->getPrice() * quantity) << endl;
            cout << "Updated Quantity: " << it->getQuantity() << endl;
            cout << endl;
        }
        else
        {
            cout << "Item not found in inventory. Please enter a valid item." << endl;
            cout << endl;
        }
    }
};

int main()
{
    InventorySystem inventorySystem;

    // Example: Adding items to the inventory
    inventorySystem.addItem(InventoryItem("Item1", 10, 5.99));
    inventorySystem.addItem(InventoryItem("Item2", 20, 10.50));
    inventorySystem.addItem(InventoryItem("Item1", 0, 5.99));

    // Example: Displaying all items in the inventory
    inventorySystem.displayInventory();

    // Example: Finding an item by name
    inventorySystem.findItem("Item1");

    return 0;
}