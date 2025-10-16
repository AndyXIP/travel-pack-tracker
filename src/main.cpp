#include "inventory.h"
#include "commands.h"
#include <iostream>

int main(int argc, char* argv[]) {
    const std::string filename = "inventory.json";
    
    Inventory inventory;
    inventory.loadFromFile(filename);
    CommandHandler commandHandler(inventory);
    commandHandler.execute(argc, argv);
    inventory.saveToFile(filename);
    
    return 0;
}
