//
// Created by Alex Campean on 05.05.2022.
//

#include "ElectricEngine.h"

ElectricEngine::ElectricEngine(const std::string &inputFuelType, double inputBasePrice, int inputAutonomy) : Engine(
        inputFuelType, inputBasePrice) {
    this->autonomy = inputAutonomy;
}

ElectricEngine::~ElectricEngine() {
}

double ElectricEngine::getPrice() {
    double autonomyPrice = this->autonomy * 0.01;
    double finalPrice = this->basePrice = autonomyPrice;
    return finalPrice;
}

std::string ElectricEngine::toString() {
    return "| Electric Engine | Fuel Type: " + this->fuelType + " | "
           + "Base Price: " + std::to_string(this->basePrice) + " | "
           + "Autonomy: " + std::to_string(this->autonomy);
}
