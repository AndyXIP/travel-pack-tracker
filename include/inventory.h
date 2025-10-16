#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <optional>
#include "item.h"

/**
 * @class Inventory
 * @brief Manages a collection of items across multiple locations
 * 
 * The Inventory class provides comprehensive item management functionality including
 * CRUD operations, location-based queries, and persistent storage. It automatically
 * merges items when adding duplicates at the same location.
 */
class Inventory {
    private:
        std::vector<Item> items;
        
    public:
        /**
         * @brief Constructs an empty inventory
         */
        Inventory() = default;
        
        /**
         * @brief Adds an item to the inventory
         * 
         * If an item with the same name exists at the same location, their quantities
         * are merged. Otherwise, the item is added as a new entry.
         * 
         * @param item The item to add
         */
        void addItem(const Item &item);
        
        /**
         * @brief Removes an item completely from the inventory
         * @param name The name of the item to remove
         * @return true if the item was found and removed, false otherwise
         */
        bool removeItem(const std::string &name);
        
        /**
         * @brief Removes a specific quantity of an item
         * 
         * If the remaining quantity reaches zero or below, the item is removed entirely.
         * 
         * @param name The name of the item
         * @param amount The quantity to remove
         * @return true if the item was found and updated, false otherwise
         */
        bool removeItemQuantity(const std::string &name, int amount);
        
        /**
         * @brief Finds an item by name (read-only)
         * @param name The name of the item to find
         * @return std::optional containing the item if found, std::nullopt otherwise
         */
        std::optional<Item> findItem(const std::string &name) const;
        
        /**
         * @brief Finds an item by name and returns a mutable pointer
         * @param name The name of the item to find
         * @return Pointer to the item if found, nullptr otherwise
         */
        Item* findItemPtr(const std::string &name);
        
        /**
         * @brief Updates the quantity of an item
         * @param name The name of the item
         * @param newQuantity The new quantity value
         * @return true if the item was found and updated, false otherwise
         */
        bool updateItemQuantity(const std::string &name, int newQuantity);
        
        /**
         * @brief Updates the location of an item
         * @param name The name of the item
         * @param newLocation The new location
         * @return true if the item was found and updated, false otherwise
         */
        bool updateItemLocation(const std::string &name, const std::string &newLocation);
        
        /**
         * @brief Moves an item (or partial quantity) between locations
         * 
         * Can move all units or a specific quantity. If moving partial quantity,
         * the original item is split into two entries.
         * 
         * @param name The name of the item to move
         * @param fromLoc The source location
         * @param toLoc The destination location
         * @param quantity The quantity to move (-1 for all items, default: -1)
         * @return true if successful, false if item not found at source location
         */
        bool moveItem(const std::string &name, const std::string &fromLoc, 
                     const std::string &toLoc, int quantity = -1);
        
        /**
         * @brief Gets all items at a specific location
         * @param location The location to query
         * @return Vector of items at the specified location
         */
        std::vector<Item> getItemsByLocation(const std::string &location) const;
        
        /**
         * @brief Gets all items in the inventory
         * @return Const reference to the items vector
         */
        const std::vector<Item>& getAllItems() const;
        
        /**
         * @brief Gets the total number of unique items
         * @return The count of items in the inventory
         */
        int getTotalItems() const;
        
        /**
         * @brief Displays all items in a formatted list
         */
        void listItems() const;
        
        /**
         * @brief Displays items at a specific location
         * @param location The location to filter by
         */
        void listItemsByLocation(const std::string &location) const;
        
        /**
         * @brief Saves the inventory to a JSON file
         * @param filename Path to the output file
         * @return true if successful, false on error
         */
        bool saveToFile(const std::string& filename) const;
        
        /**
         * @brief Loads the inventory from a JSON file
         * 
         * Replaces all current items with those from the file.
         * 
         * @param filename Path to the input file
         * @return true if successful, false if file doesn't exist or on error
         */
        bool loadFromFile(const std::string& filename);
};

#endif