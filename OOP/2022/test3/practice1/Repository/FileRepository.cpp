//
// Created by Alex Campean on 27.05.2022.
//

#include "FileRepository.h"
#include "../Exception/CustomException.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileRepository::FileRepository(const std::string &inputFileName) : fileName(inputFileName) {
    this->load();
}

const std::string &FileRepository::getInputFileName() const {
    return fileName;
}

void FileRepository::setInputFileName(const std::string &inputFileName) {
    FileRepository::fileName = inputFileName;
}

void FileRepository::load() {
    std::ifstream input(this->fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        ShoppingItem item;
        if (!(iss >> item)) { break; } // error

        this->addElementRepo(item);
    }
}

void FileRepository::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}

int FileRepository::getRepoLength() const {
    return this->shoppingList.size();
}

std::vector<ShoppingItem> FileRepository::getShoppingList() const {
    return this->shoppingList;
}

void FileRepository::addElementRepo(const ShoppingItem &item) {
    auto it = std::find(shoppingList.begin(), shoppingList.end(), item);
    if (it != shoppingList.end()) {
        throw CustomException(ExceptionTypes::AddException);
    }
    shoppingList.push_back(item);
    this->save();
}

void FileRepository::deleteElementRepo(const std::string &name) {
    auto it = std::find(shoppingList.begin(), shoppingList.end(), name);
    if (it == shoppingList.end()) {
        throw CustomException(ExceptionTypes::DeleteException);
    }

    shoppingList.erase(it);
    this->save();
}

ShoppingItem &FileRepository::operator[](int index) {
    return this->shoppingList[index];
}
