#include "inventory.h"
#include <iostream>
#include <algorithm>

void Inventory::addItem(const Item &item) {
    // Check if item already exists at this location
    auto existingItem = findItemPtr(item.getName());
    if (existingItem && existingItem->getLocation() == item.getLocation()) {
        // If exists at same location, add to quantity
        existingItem->addQuantity(item.getQuantity());
    } else {
        // Otherwise add as new item
        items.push_back(item);
    }
}

bool Inventory::removeItem(const std::string &name) {
    auto it = std::find_if(items.begin(), items.end(),
        [&name](const Item &item) { return item.getName() == name; });
    
    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    return false;
}

bool Inventory::removeItemQuantity(const std::string &name, int amount) {
    auto item = findItemPtr(name);
    if (item) {
        item->removeQuantity(amount);
        if (item->getQuantity() <= 0) {
            removeItem(name);
        }
        return true;
    }
    return false;
}

std::optional<Item> Inventory::findItem(const std::string &name) const {
    auto it = std::find_if(items.begin(), items.end(),
        [&name](const Item &item) { return item.getName() == name; });
    
    if (it != items.end()) {
        return *it;
    }
    return std::nullopt;
}

Item* Inventory::findItemPtr(const std::string &name) {
    auto it = std::find_if(items.begin(), items.end(),
        [&name](const Item &item) { return item.getName() == name; });
    
    if (it != items.end()) {
        return &(*it);
    }
    return nullptr;
}

bool Inventory::updateItemQuantity(const std::string &name, int newQuantity) {
    auto item = findItemPtr(name);
    if (item) {
        item->setQuantity(newQuantity);
        return true;
    }
    return false;
}

bool Inventory::updateItemLocation(const std::string &name, const std::string &newLocation) {
    auto item = findItemPtr(name);
    if (item) {
        item->setLocation(newLocation);
        return true;
    }
    return false;
}

bool Inventory::moveItem(const std::string &name, const std::string &fromLoc, const std::string &toLoc, int quantity) {
    auto item = findItemPtr(name);
    if (item && item->getLocation() == fromLoc) {
        if (quantity == -1 || quantity >= item->getQuantity()) {
            // Move all
            item->setLocation(toLoc);
        } else {
            // Split item - move some quantity
            item->removeQuantity(quantity);
            items.push_back(Item(name, quantity, toLoc));
        }
        return true;
    }
    return false;
}

std::vector<Item> Inventory::getItemsByLocation(const std::string &location) const {
    std::vector<Item> result;
    for (const auto &item : items) {
        if (item.getLocation() == location) {
            result.push_back(item);
        }
    }
    return result;
}

const std::vector<Item>& Inventory::getAllItems() const {
    return items;
}

int Inventory::getTotalItems() const {
    return items.size();
}

void Inventory::listItems() const {
    if (items.empty()) {
        std::cout << "No items in inventory.\n";
        return;
    }
    
    std::cout << "\nAll Items:\n";
    std::cout << "----------------------------------------\n";
    for (const auto &item : items) {
        std::cout << "- " << item.getName() 
                  << " (Qty: " << item.getQuantity() 
                  << ", Location: " << item.getLocation() << ")\n";
    }
    std::cout << "----------------------------------------\n";
}

void Inventory::listItemsByLocation(const std::string &location) const {
    auto locationItems = getItemsByLocation(location);
    
    if (locationItems.empty()) {
        std::cout << "No items at " << location << ".\n";
        return;
    }
    
    std::cout << "\nItems at " << location << ":\n";
    std::cout << "----------------------------------------\n";
    for (const auto &item : locationItems) {
        std::cout << "- " << item.getName() 
                  << " (Qty: " << item.getQuantity() << ")\n";
    }
    std::cout << "----------------------------------------\n";
}
