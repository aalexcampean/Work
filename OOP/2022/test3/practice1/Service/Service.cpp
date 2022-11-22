//
// Created by Alex Campean on 27.05.2022.
//

#include "Service.h"
#include "../Exception/CustomException.h"

ShoppingItem &Service::operator[](int index) {
    return repository->operator[](index);
}

int Service::getShoppingListLength() const {
    return repository->getRepoLength();
}

std::vector<ShoppingItem> Service::getShoppingList() const {
    return repository->getShoppingList();
}

std::vector<ShoppingItem> Service::filterByCategory(const std::string &inputCategory) {
    std::vector<ShoppingItem> allItems = repository->getShoppingList();
    if (inputCategory.empty()) {
        return allItems;
    }
    std::vector<ShoppingItem> filteredItems;
    std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(filteredItems), [&inputCategory](auto &it){
        return it.getCategory() == inputCategory;
    });
    return filteredItems;
}

void Service::addElementService(const std::string &category, const std::string &name, const std::string &quantity) {
    int validatedQuantity;
    size_t pos1;
    try {
        validatedQuantity = std::stoi(quantity, &pos1);
    }
    catch (std::invalid_argument invalidArgument) {
    }

    if (pos1 != quantity.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleInput);
    }

    ShoppingItem newItem(category, name, validatedQuantity);
    this->repository->addElementRepo(newItem);
}

void Service::deleteElementService(const std::string &name) {
    this->repository->deleteElementRepo(name);
}
