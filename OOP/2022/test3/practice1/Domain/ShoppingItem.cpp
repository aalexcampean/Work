//
// Created by Alex Campean on 27.05.2022.
//

#include "ShoppingItem.h"

ShoppingItem::ShoppingItem(const std::string &category, const std::string &name, int quantity) : category(category),
                                                                                                 name(name),
                                                                                                 quantity(quantity) {}

const std::string &ShoppingItem::getCategory() const {
    return category;
}

void ShoppingItem::setCategory(const std::string &category) {
    ShoppingItem::category = category;
}

const std::string &ShoppingItem::getName() const {
    return name;
}

void ShoppingItem::setName(const std::string &name) {
    ShoppingItem::name = name;
}

int ShoppingItem::getQuantity() const {
    return quantity;
}

void ShoppingItem::setQuantity(int quantity) {
    ShoppingItem::quantity = quantity;
}

bool ShoppingItem::operator==(const ShoppingItem &rhs) const {
    return name == rhs.name;
}

bool ShoppingItem::operator!=(const ShoppingItem &rhs) const {
    return !(name == rhs.name);
}

bool ShoppingItem::operator==(const std::string &inputName) const {
    return this->name == inputName;
}

bool ShoppingItem::operator!=(const std::string &inputName) const {
    return !(this->name == inputName);
}

std::string ShoppingItem::toString() const {
    return "Category: " + category + "  |  " + "Name: " + name + "  |  " + std::to_string(quantity);
}