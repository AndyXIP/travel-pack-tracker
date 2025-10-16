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
    if (quantity < 0) quantity = 0;  // Prevent negative quantities
}

// Convert to JSON format
nlohmann::json Item::toJson() const {
    return {
        {"name", name},
        {"quantity", quantity},
        {"location", location}
    };
}

// Convert from JSON format
Item Item::fromJson(const nlohmann::json& j) {
    return Item(
        j.at("name").get<std::string>(),
        j.at("quantity").get<int>(),
        j.at("location").get<std::string>()
    );
}