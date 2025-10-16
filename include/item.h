#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <nlohmann/json.hpp>

/**
 * @class Item
 * @brief Represents a trackable item with a name, quantity, and location
 * 
 * The Item class encapsulates a physical item that needs to be tracked across
 * different locations (e.g., home, suitcase, office). It supports quantity
 * management and JSON serialization for data persistence.
 */
class Item {
    private:
        std::string name;
        int quantity;
        std::string location;
        
    public:
        /**
         * @brief Constructs an Item with specified attributes
         * @param name The name of the item
         * @param quantity The quantity of the item
         * @param location The location of the item (defaults to "home")
         */
        Item(const std::string &name, int quantity, const std::string &location = "home");
        
        /**
         * @brief Gets the name of the item
         * @return The item's name
         */
        std::string getName() const;
        
        /**
         * @brief Gets the quantity of the item
         * @return The current quantity
         */
        int getQuantity() const;
        
        /**
         * @brief Gets the location of the item
         * @return The item's current location
         */
        std::string getLocation() const;
        
        /**
         * @brief Sets the quantity of the item
         * @param qty The new quantity value
         */
        void setQuantity(int qty);
        
        /**
         * @brief Sets the location of the item
         * @param loc The new location
         */
        void setLocation(const std::string &loc);
        
        /**
         * @brief Increases the item's quantity by a specified amount
         * @param amount The amount to add
         */
        void addQuantity(int amount);
        
        /**
         * @brief Decreases the item's quantity by a specified amount
         * @param amount The amount to remove (quantity will not go below 0)
         */
        void removeQuantity(int amount);
        
        /**
         * @brief Serializes the item to JSON format
         * @return JSON object representing the item
         */
        nlohmann::json toJson() const;
        
        /**
         * @brief Deserializes an item from JSON format
         * @param j JSON object containing item data
         * @return Item object constructed from JSON
         * @throws json::exception if JSON format is invalid
         */
        static Item fromJson(const nlohmann::json& j);
};

#endif