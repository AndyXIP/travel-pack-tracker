#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
    private:
        std::string name;
        int quantity;
        std::string location;
    public:
        Item(const std::string &name, int quantity, const std::string &location = "home");
        std::string getName() const;
        int getQuantity() const;
        std::string getLocation() const;
        void setQuantity(int qty);
        void setLocation(const std::string &loc);
        void addQuantity(int amount);
        void removeQuantity(int amount);
};

#endif