#include "item.h"

Item::Item(const std::string &name, int quantity, const std::string &location)
    : name(name), quantity(quantity), location(location) {}

std::string Item::getName() const {
    return name;
}

int Item::getQuantity() const {
    return quantity;
}

std::string Item::getLocation() const {
    return location;
}

void Item::setQuantity(int qty) {
    quantity = qty;
}

void Item::setLocation(const std::string &loc) {
    location = loc;
}

void Item::addQuantity(int amount) {
    quantity += amount;
}

void Item::removeQuantity(int amount) {
    quantity -= amount;
    if (quantity < 0) quantity = 0;
}