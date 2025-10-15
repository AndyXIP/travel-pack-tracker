#include "inventory.h"
#include "commands.h"

int main() {
    Inventory inventory;
    CommandHandler commandHandler(inventory);
    
    commandHandler.run();
    
    return 0;
}
