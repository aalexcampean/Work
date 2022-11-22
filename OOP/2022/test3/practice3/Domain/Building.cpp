//
// Created by Alex Campean on 05.05.2022.
//

#include "Building.h"

Building::Building() {
}

Building::Building(const std::string &inputAddress, int inputConstructionYear) {
    this->address = inputAddress;
    this->constructionYear = inputConstructionYear;
}

Building::~Building() {
}

std::string Building::getAddress() const {
    return this->address;
}

int Building::getConstructionYear() const {
    return this->constructionYear;
}
