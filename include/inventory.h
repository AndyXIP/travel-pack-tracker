#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <optional>
#include "item.h"

class Inventory {
    private:
        std::vector<Item> items;
    public:
        Inventory() = default;
        void addItem(const Item &item);
        bool removeItem(const std::string &name);
        bool removeItemQuantity(const std::string &name, int amount);
        std::optional<Item> findItem(const std::string &name) const;
        Item* findItemPtr(const std::string &name);
        bool updateItemQuantity(const std::string &name, int newQuantity);
        bool updateItemLocation(const std::string &name, const std::string &newLocation);
        bool moveItem(const std::string &name, const std::string &fromLoc, const std::string &toLoc, int quantity = -1);
        std::vector<Item> getItemsByLocation(const std::string &location) const;
        const std::vector<Item>& getAllItems() const;
        int getTotalItems() const;
        void listItems() const;
        void listItemsByLocation(const std::string &location) const;
        bool saveToFile(const std::string& filename) const;
        bool loadFromFile(const std::string& filename);
};

#endif