#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> 
#include <sstream>

using namespace std;


class InventoryItem
{
private:
    string name;
    int quantity;
    double price;

public:
    InventoryItem(string _name, int _quantity, double _price) : name(_name), quantity(_quantity), price(_price) {}

    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setName(string _name) { name = _name; }
    void setQuantity(int _quantity) { quantity = _quantity; }
    void setPrice(double _price) { price = _price; }
};

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
                cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: ₹" << item.getPrice() << endl;
                return;
            }
        }
        cout << "Item not present currently." << endl;
    }

    // Method to add an item to the inventory
    void addItem(string item)
    {

        for (size_t i = 0; i < inventory.size(); ++i)
        {
            if (inventory[i].getName() == item)
            {
                
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
        cout << "Item not found in inventory. Adding new item..." << endl;
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
        cout << "Inventory Items:" << endl;
        for (const auto &item : inventory)
        {
            cout << "Name: " << item.getName() << ", Quantity: " << item.getQuantity() << ", Price: ₹" << item.getPrice() << endl;
        }
    }


    // Method to sell item
    void sellItem(const string &name)
    {
        // Find the item in the inventory
        auto it = std::find_if(inventory.begin(), inventory.end(), [&](const InventoryItem &item)
                               { return item.getName() == name; });

        if (it != inventory.end())
        {
            int quantity;
            cout << "Enter the quantity to sell: ";
            cin >> quantity;
            cout << endl;

            int currQuantity = it->getQuantity();

            while (quantity > currQuantity || quantity <= 0)
            {
                cout << "Please enter a valid quantity to sell (<= " << currQuantity << "): ";
                cin >> quantity;
            }

            it->setQuantity(currQuantity - quantity);

            // Display sale information
            cout << "Item " << name << " successfully sold!" << endl;
            cout<< "Quantity sold:-" << quantity << endl;
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
    
    void saveInventory(const string& filename) const
{
    ofstream outputFile(filename); 
    if (!outputFile)
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
    cout << "Saving..... " << endl;
    for (const auto &item : inventory)
    {
        outputFile << item.getName() << " " << item.getQuantity() << " " << item.getPrice() << endl;
    }

    outputFile.close();
    cout << "Inventory saved to file successfully." << endl;
}

// Method to load inventory from a file
void loadInventory(const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }

    inventory.clear();

    string line;
    while (getline(inputFile, line))
    {

        stringstream ss(line);
        string name;
        int quantity;
        double price;

       if (ss >> name >> quantity >> price && ss.peek() == EOF)
        {
            inventory.push_back(InventoryItem(name, quantity, price));
        }
        
    }

    inputFile.close();
    cout << "Inventory loaded from file successfully." << endl;
}


    
};

int main()
{
    InventorySystem inventorySystem;

    int operation;
    string item;
    while(true){
        cout<<"1)Display Inventory"<<endl;
        cout<<"2)Display Item"<<endl;
        cout<<"3)Add Items"<<endl;
        cout<<"4)Remove Items"<<endl;
        cout<<"5)Exit"<<endl;
        cout<<"Enter which operation to perform:";
        cin>>operation;
        switch (operation) {
            case 1 :
                cout << endl;
                cout<<"1)Display Inventory"<<endl;
                inventorySystem.displayInventory();
                break;
            case 2 :
                cout << endl;
                cout<<"2)Display Item"<<endl;
                cout<<"Enter the name of the item to be searched:";
                cin >> item;
                inventorySystem.findItem(item);
                break;
            case 3 :
                cout << endl;
                cout<<"3)Add Items"<<endl;
                cout<<"Enter the item to be added:";
                cin>>item;
                inventorySystem.addItem(item);
                break;
            case 4 :cout<<"Enter the item to be added:";
                cin>>item;
                inventorySystem.addItem(item);
                break;
            case 5 :// Exit
            cout<<"Exiting Program..."<<endl;
            exit(0); 
            break;

            default:
            cout << "Invalid operation! Please enter a valid option." << endl;
            break;
        }
        char doContinue;
        cout<<"Continue Updating? Y/N: ";
        cin>>doContinue;
        if(!doContinue)
            break;
        }
    }
    return 0;
}