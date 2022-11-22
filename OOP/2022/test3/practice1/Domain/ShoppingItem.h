//
// Created by Alex Campean on 27.05.2022.
//

#pragma once
#include <vector>
#include <string>
#include <ostream>

class ShoppingItem {
private:
    std::string category;
    std::string name;
    int quantity;
public:
    ShoppingItem(){};
    ShoppingItem(const std::string &category, const std::string &name, int quantity);
    ~ShoppingItem(){};

    const std::string &getCategory() const;
    void setCategory(const std::string &category);

    const std::string &getName() const;
    void setName(const std::string &name);

    int getQuantity() const;
    void setQuantity(int quantity);

    std::string toString() const;

    bool operator==(const ShoppingItem &rhs) const;
    bool operator!=(const ShoppingItem &rhs) const;

    bool operator==(const std::string &inputName) const;
    bool operator!=(const std::string &inputName) const;

    friend std::ostream &operator<<(std::ostream &os, const ShoppingItem &item);
    friend std::istream& operator>>(std::istream& in, ShoppingItem &item);
};

inline std::ostream &operator<<(std::ostream &os, const ShoppingItem &item) {
    os << item.category << "," << item.name << "," << item.quantity;
    return os;
}

inline std::istream& operator>>(std::istream& in, ShoppingItem &item) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 3; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    item.category = fields[0];
    item.name = fields[1];
    item.quantity = std::stoi(fields[2]);
    return in;
}
