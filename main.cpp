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
            cout << "No Items present in the inventory currently." << endl;
            return;
        }

        for (const auto &item : inventory)
        {
            if (item.getName() == name)
            {
                cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: ₹" << item.getPrice()<<"/-"<< endl;
                return;
            }
        }
        cout << "Item not present currently." << endl;
    }

    // Method to add an item to the inventory
    void addItem(string item)
    {
        // Check if the item already exists in the inventory
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            if (inventory[i].getName() == item)
            {
                // Item found, update its quantity
                int quantity;
                cout << "Enter the number of " + item + "s to be added: ";
                cin >> quantity;

                int currQuantity = inventory[i].getQuantity();
                inventory[i].setQuantity(currQuantity + quantity);

                cout << "Quantity added to " << item << endl;
                cout << "New Quantity: " << inventory[i].getQuantity() << endl;
                cout << endl;
                return;
            }
        }

        // Item not found, add it to the inventory
        cout << "Item not found in inventory."<<endl<<"Adding the new item..." << endl;
        int quantity,price;
        cout<<"Enter the quantity:";
        cin >> quantity;
        cout<<"Enter the price per unit:";
        cin >> price;
        inventory.push_back(InventoryItem(item,quantity,price));
        cout << "New Item " << item << " Added To The Inventory !" << endl;
        cout << endl;
    }

    // Method to display all items in the inventory
    void displayInventory() const
    {
        if(inventory.empty())
        {
            cout<<"No Items found!! Inventory is Empty."<<endl;
        }
        cout << "Inventory Items:" << endl;
        for (const auto &item : inventory)
        {
            cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: ₹" << item.getPrice()<<"/-" << endl;
        }
    }

    // Method to find and display an item by name

    // Method to sell item
    void sellItem(const string &name)
    {
        if (inventory.empty())
        {
            cout << "No Items present in the inventory currently!! Please add items to sell." << endl;
            return;
        }
        // Find the item in the inventory
        auto it = std::find_if(inventory.begin(), inventory.end(), [&](const InventoryItem &item)
                               { return item.getName() == name; });

        // Check if the item was found
        if (it != inventory.end())
        {
            int quantity;
            cout << "Enter the quantity to sell: ";
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
            cout << "Item " << name << " successfully sold!!" << endl;
            cout<< "Quantity sold: " << quantity << endl;
            cout << "Total Amount (Including taxes): Rs." << (it->getPrice() * quantity)<<"/-"<< endl;
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

    int operation;
    string item;
    cout<<"WELCOME TO THE INVENTORY TRACKING SYSTEM..."<<endl;
    cout<<"Main Menu:"<<endl;
    while(true){
        cout<<"1)Display Inventory"<<endl;
        cout<<"2)Search an Item"<<endl;
        cout<<"3)Restock/Add Items"<<endl;
        cout<<"4)Sell Items"<<endl;
        cout<<"5)Exit"<<endl;
        cout<<"Enter which operation to perform:";
        cin>>operation;
        switch (operation) {
            case 1 :inventorySystem.displayInventory();
                break;
            case 2 :
                cout<<"Enter the name of the item to be searched:";
                cin >> item;
                inventorySystem.findItem(item);
                break;
            case 3 :
                cout<<"Enter the item to be added:";
                cin>>item;
                inventorySystem.addItem(item);
                break;
            case 4 :cout<<"Enter the item to sell:";
                cin>>item;
                inventorySystem.sellItem(item);
                break;
            case 5 :// Exit
            cout<<"Exiting Program..."<<endl<<"Have a nice day!!";
            exit(0); 
            break;

            default:
            cout << "Invalid operation! Please enter a valid option." << endl;
            break;
        }
        char doContinue;
        cout<<"Continue Updating? Y/N: ";
        cin>>doContinue;
        if(doContinue=='n'){
            cout<<"Exiting Program..."<<endl<<"Have a nice day!!";
            break;
        }
    }
    return 0;
}