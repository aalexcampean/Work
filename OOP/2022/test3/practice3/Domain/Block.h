//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include "Building.h"
#include <string>

class Block : public Building {
private:
    int totalApartments;
    int occupiedApartments;
public:
    Block();
    Block(const std::string &inputAddress, int inputConstructionYear, int inputTotalApartments, int inputOccupiedApartments);
    ~Block();

    bool mustBeRestored() override;
    bool mustBeDemolished() override;
    std::string toString() override;
};
