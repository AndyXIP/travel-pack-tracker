#include "commands.h"
#include <iostream>
#include <string>

CommandHandler::CommandHandler(Inventory& inv) : inventory(inv) {}

void CommandHandler::printMenu() {
    std::cout << "\n=== Travel Pack Tracker ===\n";
    std::cout << "1. Add item\n";
    std::cout << "2. Remove item\n";
    std::cout << "3. Move item between locations\n";
    std::cout << "4. Update item quantity\n";
    std::cout << "5. List all items\n";
    std::cout << "6. List items by location\n";
    std::cout << "7. Find item\n";
    std::cout << "8. Exit\n";
    std::cout << "Choose an option: ";
}

void CommandHandler::addItemCommand() {
    std::string name, location;
    int quantity;
    
    std::cout << "Enter item name: ";
    std::getline(std::cin, name);
    std::cout << "Enter quantity: ";
    std::cin >> quantity;
    std::cin.ignore();
    std::cout << "Enter location (e.g., home, suitcase, office): ";
    std::getline(std::cin, location);
    
    inventory.addItem(Item(name, quantity, location));
    std::cout << "Item added successfully!\n";
}

void CommandHandler::removeItemCommand() {
    std::string name;
    std::cout << "Enter item name to remove: ";
    std::getline(std::cin, name);
    
    if (inventory.removeItem(name)) {
        std::cout << "Item removed successfully!\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void CommandHandler::moveItemCommand() {
    std::string name, fromLoc, toLoc;
    int qty;
    
    std::cout << "Enter item name: ";
    std::getline(std::cin, name);
    std::cout << "From location: ";
    std::getline(std::cin, fromLoc);
    std::cout << "To location: ";
    std::getline(std::cin, toLoc);
    std::cout << "Quantity to move (-1 for all): ";
    std::cin >> qty;
    std::cin.ignore();
    
    if (inventory.moveItem(name, fromLoc, toLoc, qty)) {
        std::cout << "Item moved successfully!\n";
    } else {
        std::cout << "Failed to move item. Check item name and location.\n";
    }
}

void CommandHandler::updateQuantityCommand() {
    std::string name;
    int qty;
    
    std::cout << "Enter item name: ";
    std::getline(std::cin, name);
    std::cout << "Enter new quantity: ";
    std::cin >> qty;
    std::cin.ignore();
    
    if (inventory.updateItemQuantity(name, qty)) {
        std::cout << "Quantity updated successfully!\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void CommandHandler::listAllItemsCommand() {
    inventory.listItems();
}

void CommandHandler::listItemsByLocationCommand() {
    std::string location;
    std::cout << "Enter location: ";
    std::getline(std::cin, location);
    inventory.listItemsByLocation(location);
}

void CommandHandler::findItemCommand() {
    std::string name;
    std::cout << "Enter item name: ";
    std::getline(std::cin, name);
    
    auto item = inventory.findItem(name);
    if (item.has_value()) {
        std::cout << "\nFound: " << item->getName() 
                  << "\n  Quantity: " << item->getQuantity()
                  << "\n  Location: " << item->getLocation() << "\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void CommandHandler::run() {
    std::string choice;
    
    std::cout << "Welcome to Travel Pack Tracker!\n";
    std::cout << "Track your items across home, suitcases, and more.\n";
    
    while (true) {
        printMenu();
        std::getline(std::cin, choice);
        
        if (choice == "1") {
            addItemCommand();
        } else if (choice == "2") {
            removeItemCommand();
        } else if (choice == "3") {
            moveItemCommand();
        } else if (choice == "4") {
            updateQuantityCommand();
        } else if (choice == "5") {
            listAllItemsCommand();
        } else if (choice == "6") {
            listItemsByLocationCommand();
        } else if (choice == "7") {
            findItemCommand();
        } else if (choice == "8") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }
}
