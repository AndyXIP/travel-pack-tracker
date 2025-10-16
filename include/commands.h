#ifndef COMMANDS_H
#define COMMANDS_H

#include "inventory.h"
#include <string>
#include <vector>

/**
 * @class CommandHandler
 * @brief Handles command-line interface operations for inventory management
 * 
 * The CommandHandler class parses command-line arguments and executes the appropriate
 * inventory operations. It supports commands for adding, removing, moving, listing,
 * and finding items, as well as displaying help information.
 * 
 * Supported commands:
 * - add: Add items to inventory
 * - remove: Remove items from inventory
 * - move: Move items between locations
 * - list: Display items (all or by location)
 * - find: Search for specific items
 * - help: Display usage information
 */
class CommandHandler {
    private:
        Inventory& inventory;
        
        /**
         * @brief Executes the 'add' command
         * @param args Command arguments: [name, quantity, location]
         */
        void addCommand(const std::vector<std::string>& args);
        
        /**
         * @brief Executes the 'remove' command
         * @param args Command arguments: [name] or [name, quantity]
         */
        void removeCommand(const std::vector<std::string>& args);
        
        /**
         * @brief Executes the 'move' command
         * @param args Command arguments: [name, quantity|"all", from_location, to_location]
         */
        void moveCommand(const std::vector<std::string>& args);
        
        /**
         * @brief Executes the 'list' command
         * @param args Command arguments: [] for all items, or [location] to filter
         */
        void listCommand(const std::vector<std::string>& args);
        
        /**
         * @brief Executes the 'find' command
         * @param args Command arguments: [name]
         */
        void findCommand(const std::vector<std::string>& args);
        
        /**
         * @brief Displays help information with command usage examples
         */
        void helpCommand();
        
    public:
        /**
         * @brief Constructs a CommandHandler with an inventory reference
         * @param inv Reference to the inventory to operate on
         */
        CommandHandler(Inventory& inv);
        
        /**
         * @brief Parses and executes a command from command-line arguments
         * 
         * The first argument (after program name) is the command, and remaining
         * arguments are passed to the specific command handler.
         * 
         * @param argc Number of command-line arguments
         * @param argv Array of command-line argument strings
         * @return true if a valid command was executed, false otherwise
         */
        bool execute(int argc, char* argv[]);
};

#endif
