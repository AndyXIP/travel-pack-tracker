#include "commands.h"
#include <iostream>
#include <string>
#include <vector>

CommandHandler::CommandHandler(Inventory& inv) : inventory(inv) {}

void CommandHandler::helpCommand() {
    std::cout << "Travel Pack Tracker - CLI Usage:\n\n";
    std::cout << "Commands:\n";
    std::cout << "  add <name> <quantity> <location>    Add item to inventory\n";
    std::cout << "      Example: add socks 2 home\n\n";
    std::cout << "  remove <name> [quantity]            Remove item (or reduce quantity)\n";
    std::cout << "      Example: remove socks\n";
    std::cout << "      Example: remove socks 1\n\n";
    std::cout << "  move <name> <quantity> <from> <to>  Move items between locations\n";
    std::cout << "      Example: move socks 2 home suitcase\n";
    std::cout << "      Example: move socks all home suitcase\n\n";
    std::cout << "  list [location]                     List all items or by location\n";
    std::cout << "      Example: list\n";
    std::cout << "      Example: list home\n\n";
    std::cout << "  find <name>                         Find specific item\n";
    std::cout << "      Example: find socks\n\n";
    std::cout << "  help                                Show this help message\n";
}

void CommandHandler::addCommand(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cout << "Usage: add <name> <quantity> <location>\n";
        std::cout << "Example: add socks 2 home\n";
        return;
    }
    
    std::string name = args[0];
    int quantity;
    
    // Parse quantity (handle non-numeric input)
    try {
        quantity = std::stoi(args[1]);
    } catch (...) {
        std::cout << "Error: Quantity must be a number\n";
        return;
    }
    
    std::string location = args[2];
    
    inventory.addItem(Item(name, quantity, location));
    std::cout << "✓ Added " << quantity << "x " << name << " at " << location << "\n";
}

void CommandHandler::removeCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Usage: remove <name> [quantity]\n";
        std::cout << "Example: remove socks\n";
        std::cout << "Example: remove socks 1\n";
        return;
    }
    
    std::string name = args[0];
    
    if (args.size() == 1) {
        // Remove entire item
        if (inventory.removeItem(name)) {
            std::cout << "✓ Removed " << name << "\n";
        } else {
            std::cout << "✗ Item '" << name << "' not found\n";
        }
    } else {
        // Remove specific quantity
        int quantity;
        try {
            quantity = std::stoi(args[1]);
        } catch (...) {
            std::cout << "Error: Quantity must be a number\n";
            return;
        }
        
        if (inventory.removeItemQuantity(name, quantity)) {
            std::cout << "✓ Removed " << quantity << "x " << name << "\n";
        } else {
            std::cout << "✗ Item '" << name << "' not found\n";
        }
    }
}

void CommandHandler::moveCommand(const std::vector<std::string>& args) {
    if (args.size() < 4) {
        std::cout << "Usage: move <name> <quantity|all> <from> <to>\n";
        std::cout << "Example: move socks 2 home suitcase\n";
        std::cout << "Example: move socks all home suitcase\n";
        return;
    }
    
    std::string name = args[0];
    int quantity = -1; // -1 means move all
    
    // Parse quantity or handle "all" keyword
    if (args[1] != "all") {
        try {
            quantity = std::stoi(args[1]);
        } catch (...) {
            std::cout << "Error: Quantity must be a number or 'all'\n";
            return;
        }
    }
    
    std::string fromLoc = args[2];
    std::string toLoc = args[3];
    
    if (inventory.moveItem(name, fromLoc, toLoc, quantity)) {
        if (quantity == -1) {
            std::cout << "✓ Moved all " << name << " from " << fromLoc << " to " << toLoc << "\n";
        } else {
            std::cout << "✓ Moved " << quantity << "x " << name << " from " << fromLoc << " to " << toLoc << "\n";
        }
    } else {
        std::cout << "✗ Failed to move. Check item name and location.\n";
    }
}

void CommandHandler::listCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        // List all items
        inventory.listItems();
    } else {
        // List items at specific location
        std::string location = args[0];
        inventory.listItemsByLocation(location);
    }
}

void CommandHandler::findCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Usage: find <name>\n";
        std::cout << "Example: find socks\n";
        return;
    }
    
    std::string name = args[0];
    auto item = inventory.findItem(name);
    
    if (item.has_value()) {
        std::cout << "\n✓ Found: " << item->getName() << "\n";
        std::cout << "  Quantity: " << item->getQuantity() << "\n";
        std::cout << "  Location: " << item->getLocation() << "\n";
    } else {
        std::cout << "✗ Item '" << name << "' not found\n";
    }
}

bool CommandHandler::execute(int argc, char* argv[]) {
    // If no arguments provided, show help
    if (argc < 2) {
        helpCommand();
        return false;
    }
    
    std::string command = argv[1];
    
    // Build args vector from remaining command-line arguments
    std::vector<std::string> args;
    for (int i = 2; i < argc; i++) {
        args.push_back(argv[i]);
    }
    
    // Route to appropriate command handler
    if (command == "add") {
        addCommand(args);
    } else if (command == "remove") {
        removeCommand(args);
    } else if (command == "move") {
        moveCommand(args);
    } else if (command == "list") {
        listCommand(args);
    } else if (command == "find") {
        findCommand(args);
    } else if (command == "help") {
        helpCommand();
    } else {
        std::cout << "Unknown command: " << command << "\n";
        std::cout << "Run 'help' to see available commands\n";
        return false;
    }
    
    return true;
}
