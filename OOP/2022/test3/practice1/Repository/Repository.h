//
// Created by Alex Campean on 27.05.2022.
//
#pragma once
#include <vector>
#include <ostream>
#include "ShoppingItem.h"


class Repository {
protected:
    std::vector<ShoppingItem> shoppingList;
public:
    Repository(){};
    Repository(const Repository &repository): shoppingList(repository.shoppingList){};
    ~Repository(){};

    virtual int getRepoLength() const = 0;
    virtual std::vector<ShoppingItem> getShoppingList() const = 0;

    /// Add, Delete
    virtual void addElementRepo(const ShoppingItem& item) = 0;
    virtual void deleteElementRepo(const std::string& name) = 0;

    /// Operators Overload
    virtual ShoppingItem& operator[](int index) = 0;
    friend std::ostream &operator<<(std::ostream &os, const Repository &repository);
};

inline std::ostream &operator<<(std::ostream &os, const Repository &repository) {
    os << "shoppingList: ";
    for (const auto& it: repository.shoppingList) {
        os << it << "\n";
    }
    return os;
}