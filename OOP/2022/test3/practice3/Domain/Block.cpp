//
// Created by Alex Campean on 05.05.2022.
//

#include "Block.h"

Block::Block() {
}

Block::Block(const std::string &inputAddress, int inputConstructionYear, int inputTotalApartments, int inputOccupiedApartments) : Building(inputAddress, inputConstructionYear) {
    this->totalApartments = inputTotalApartments;
    this->occupiedApartments = inputOccupiedApartments;
}

Block::~Block() {
}

bool Block::mustBeRestored() {
    int buildingAge = 2020 - this->constructionYear;
    double occupancyPercentage = this->occupiedApartments / this->totalApartments * 100;
    return (buildingAge > 40 and occupancyPercentage > 80);
}

bool Block::mustBeDemolished() {
    double occupancyPercentage = this->occupiedApartments / this->totalApartments * 100;
    return occupancyPercentage < 5;
}

std::string Block::toString() {
    return "| Block | Address: " + this->address + " | "
    + "Construction Year: " + std::to_string(this->constructionYear) + " | "
    + "Total Apartments: " + std::to_string(this->totalApartments) + " | "
    + "Occupied Apartments: " + std::to_string(this->occupiedApartments);
}
