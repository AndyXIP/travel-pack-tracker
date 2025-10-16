#ifndef COMMANDS_H
#define COMMANDS_H

#include "inventory.h"
#include <string>
#include <vector>

class CommandHandler {
    private:
        Inventory& inventory;
        void addCommand(const std::vector<std::string>& args);
        void removeCommand(const std::vector<std::string>& args);
        void moveCommand(const std::vector<std::string>& args);
        void listCommand(const std::vector<std::string>& args);
        void findCommand(const std::vector<std::string>& args);
        void helpCommand();
        
    public:
        CommandHandler(Inventory& inv);
        bool execute(int argc, char* argv[]);
};

#endif
