#include "inventory.h"
#include "commands.h"
#include <iostream>

int main() {
    const std::string filename = "inventory.json";
    
    Inventory inventory;
    
    // Load existing data if available
    if (inventory.loadFromFile(filename)) {
        std::cout << "Loaded existing inventory from " << filename << "\n";
        std::cout << "Total items: " << inventory.getTotalItems() << "\n";
    } else {
        std::cout << "Starting with empty inventory.\n";
    }
    
    CommandHandler commandHandler(inventory);
    commandHandler.run();
    
    // Save data on exit
    if (inventory.saveToFile(filename)) {
        std::cout << "Inventory saved to " << filename << "\n";
    } else {
        std::cerr << "Warning: Failed to save inventory!\n";
    }
    
    return 0;
}
