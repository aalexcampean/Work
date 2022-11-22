//
// Created by Alex Campean on 05.05.2022.
//

#include "Engine.h"

Engine::Engine(const std::string &inputFuelType, double inputBasePrice) {
    this->fuelType = inputFuelType;
    this->basePrice = inputBasePrice;
}

Engine::~Engine() {
}

std::string Engine::getFuelType() const {
    return this->fuelType;
}

double Engine::getBasePrice() const {
    return this->basePrice;
}
