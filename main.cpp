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
    virtual string getExpirationDate() const { return "-"; }

    void setName(string _name) { name = _name; }
    void setQuantity(int _quantity) { quantity = _quantity; }
    void setPrice(double _price) { price = _price; }
};

class PerishableItem : public InventoryItem
{
private:
    string expirationDate;

public:
    PerishableItem(string _name, int _quantity, double _price, string _expirationDate)
        : InventoryItem(_name, _quantity, _price), expirationDate(_expirationDate) {}

    string getExpirationDate() const override { return expirationDate; }
};

class InventorySystem
{
private:
    vector<PerishableItem> inventory;

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
                cout << "Name: " << item.getName() << "------- Quantity: " << item.getQuantity() << "------- Price: ₹" << item.getPrice() << endl;
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

                int quantity, choice;
                cout << "Enter the number of " + item + "s to be added: ";
                cin >> quantity;

                int currQuantity = inventory[i].getQuantity();
                inventory[i].setQuantity(currQuantity + quantity);

                cout << "Quantity added to " << item << endl;
                cout << "New Quantity: " << inventory[i].getQuantity() << endl;
                cout << endl;
                cout << "Enter 1 to update price: ";
                cin >> choice;

                if (choice == 1)
                {
                    double new_price;
                    cout << "Enter the updated price: ";
                    cin >> new_price;

                    inventory[i].setPrice(new_price);
                    cout << " Price Updated !" << endl;
                    cout << "New Price: " << inventory[i].getPrice() << endl;
                    cout << endl;
                }
                return;
            }
        }

        // Item not found, add it to the inventory
        cout << "Item not found in inventory." << endl
             << "Adding the new item..." << endl;
        int quantity, price, choice;
        string expirationDate;
        cout << "Enter the quantity:";
        cin >> quantity;
        cout << "Enter the price per unit:";
        cin >> price;
        cout << "Enter the expiration date(dd/mm/yyyy) or '-' if not:";
        cin >> expirationDate;
        inventory.push_back(PerishableItem(item, quantity, price, expirationDate));
        cout << "New Item " << item << " Added To The Inventory !!" << endl;
        cout << endl;
    }

    // Method to display all items in the inventory
    void displayInventory() const
    {
        if (inventory.empty())
        {
            cout << "-----------------------------------------" << endl;
            cout << "No items are currently in the inventory." << endl;
            cout << "-----------------------------------------" << endl;
            return;
        }

        cout << "-------------------------------------------------------------------------------------------------------" << endl;
        cout << "Inventory Items:" << endl;
        cout << "-------------------------------------------------------------------------------------------------------" << endl;
        cout << "Name\t|\tQuantity\t|\tPrice (per unit)\t|\tExpiration Date" << endl;
        cout << "-------------------------------------------------------------------------------------------------------" << endl;
        for (const auto &item : inventory)
        {

            cout << item.getName() << "\t\t" << item.getQuantity() << "\t\t\t\tRs." << item.getPrice() << "\t\t\t\t" << item.getExpirationDate() << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------" << endl;
    }

    // Method to sell item
    void sellItem(const string &name)
    {
        string item = name;
        if (inventory.empty())
        {
            cout << "------------------------------------------------------------------------" << endl;
            cout << "No Items present in the inventory currently!! Please add items to sell." << endl;
            cout << "------------------------------------------------------------------------" << endl;
            return;
        }
        item[0] = toupper(item[0]);
        auto it = std::find_if(inventory.begin(), inventory.end(), [&](const InventoryItem &i)
                               { return i.getName() == item; });

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

            cout << "--------------------------------------------------" << endl;
            cout << "Name\t\tQuantity Sold\tPrice (per unit)" << endl;
            cout << "--------------------------------------------------" << endl;
            cout << item << "\t\t" << quantity << "\t\tRs." << it->getPrice() << endl;
            cout << "Total Amount (Including taxes): Rs." << (it->getPrice() * quantity) << "/-" << endl;
            cout << "Updated Quantity: " << it->getQuantity() << endl;
            cout << endl;
            if(it->getQuantity() == 0){
                inventory.erase(it);
            }
        }
        else
        {
            cout << "Item not found in inventory. Please enter a valid item." << endl;
            cout << endl;
        }
    }

    void saveInventory(const string &filename) const
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
            outputFile << item.getName() << " " << item.getQuantity() << " " << item.getPrice() << " " << item.getExpirationDate() << endl;
        }

        outputFile.close();
        cout << "Inventory saved to file successfully." << endl;
        cout << endl;
    }

    // Method to load inventory from a file
    void loadInventory(const string &filename)
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
            string name, expirationDate;
            int quantity;
            double price;

            if (ss >> name >> quantity >> price >> expirationDate && ss.peek() == EOF)
            {
                inventory.push_back(PerishableItem(name, quantity, price, expirationDate));
            }
        }

        inputFile.close();
        cout << "Inventory loaded from file successfully." << endl;
        cout << endl;
    }
};

int main()
{
    InventorySystem inventorySystem;

    int operation;
    string item, file;
    int choice, i;
    cout << "--------------------------------------------" << endl;
    cout << "WELCOME TO THE INVENTORY TRACKING SYSTEM..." << endl;
    cout << "--------------------------------------------" << endl;
    while (true)
    {
        cout << endl;
        cout << "Main Menu:" << endl;
        cout << "1)Display Inventory" << endl;
        cout << "2)Search an Item" << endl;
        cout << "3)Restock/Add Items" << endl;
        cout << "4)Sell Items" << endl;
        cout << "5)Save & Load Inventory " << endl;
        cout << "6)Exit" << endl;
        cout << "Enter which operation to perform:";
        cin >> operation;
        switch (operation)
        {
        case 1:
            cout << endl;
            cout << "1)Display Inventory" << endl;
            inventorySystem.displayInventory();
            break;
        case 2:
            cout << endl;
            cout << "2)Display Item" << endl;
            cout << "Enter the name of the item to be searched:";
            cin >> item;
            item[0] = toupper(item[0]);
            inventorySystem.findItem(item);
            break;
        case 3:
            cout << endl;
            cout << "3)Add Items" << endl;
            cout << "Enter the number of items to be added:";
            cin >> i;
            for (int j = 1; j <= i; j++)
            {
                cout << "Enter the " << j << "th item to be added:";
                cin >> item;
                item[0] = toupper(item[0]);
                inventorySystem.addItem(item);
            }
            break;
        case 4:
            cout << endl;
            cout << "Enter the number of items to sell:";
            cin >> i;
            for (int j = 1; j <= i; j++)
            {
                cout << "Enter the " << j << "th item to sell:";
                cin >> item;
                item[0] = toupper(item[0]);
                inventorySystem.sellItem(item);
            }
            break;
        case 5:
            cout << endl;
            cout << "5)Save & Load Inventory " << endl;
            cout << "Enter 1 to Save or 0 to Load inventory : ";
            cin >> choice;
            cout << "Enter the file name to proceed: " << endl;
            cin >> file;
            if (choice)
            {
                inventorySystem.saveInventory(file);
            }
            else
            {
                inventorySystem.loadInventory(file);
            }
            break;
        case 6: // Exit
            cout << "Exiting Program..." << endl
                 << "Have a nice day!!";
            exit(0);
            break;

        default:
            cout << "Invalid operation! Please enter a valid option." << endl;
            break;
        }
    }
    return 0;
}