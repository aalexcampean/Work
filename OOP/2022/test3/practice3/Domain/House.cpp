//
// Created by Alex Campean on 05.05.2022.
//

#include "House.h"

House::House() {
}

House::House(const std::string &inputAddress, int inputConstructionYear, const std::string &inputType, bool inputIsHistorical) : Building(inputAddress, inputConstructionYear) {
    this->type = inputType;
    this->isHistorical = inputIsHistorical;
}

House::~House() {
}

bool House::mustBeRestored() {
    int buildingAge = 2020 - this->constructionYear;
    return buildingAge > 100;
}

bool House::mustBeDemolished() {
    return !this->isHistorical;
}

std::string House::toString() {
    return "| House | Address: " + this->address + " | "
           + "Construction Year: " + std::to_string(this->constructionYear) + " | "
           + "Type: " + this->type + " | "
           + "Is Historical: " + (this->isHistorical? "yes" : "no");
}
