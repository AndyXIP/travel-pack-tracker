#ifndef COMMANDS_H
#define COMMANDS_H

#include "inventory.h"
#include <string>

class CommandHandler {
    private:
        Inventory& inventory;
        void printMenu();
        
    public:
        CommandHandler(Inventory& inv);
        void addItemCommand();
        void removeItemCommand();
        void moveItemCommand();
        void updateQuantityCommand();
        void listAllItemsCommand();
        void listItemsByLocationCommand();
        void findItemCommand();
        void run();
};

#endif
