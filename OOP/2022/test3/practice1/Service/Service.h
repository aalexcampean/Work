//
// Created by Alex Campean on 27.05.2022.
//
#pragma once
#include "FileRepository.h"

class Service {
private:
    FileRepository *repository;
public:
    /// Constructors, Destructor
    Service(FileRepository* repository): repository(repository){};
    Service(const Service &service): repository(service.repository){};
    ~Service(){};

    /// Getters
    ShoppingItem& operator[](int index);
    int getShoppingListLength() const;
    std::vector<ShoppingItem> getShoppingList() const;

    /// Filtering
    std::vector<ShoppingItem> filterByCategory(const std::string &inputCategory);

    /// Add, Delete
    void addElementService(const std::string &category, const std::string &name, const std::string &quantity);
    void deleteElementService(const std::string &name);
};

