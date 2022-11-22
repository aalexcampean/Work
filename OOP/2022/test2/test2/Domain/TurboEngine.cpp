//
// Created by Alex Campean on 05.05.2022.
//

#include "TurboEngine.h"

TurboEngine::TurboEngine(const std::string &inputFuelType, double inputBasePrice) : Engine(inputFuelType,
                                                                                           inputBasePrice) {
}

TurboEngine::~TurboEngine() {
}

double TurboEngine::getPrice() {
    double priceBasedOnFuel = this->fuelType == "gasoline" ? 100 : 150;
    double finalPrice = this->basePrice + 0.01 * priceBasedOnFuel;
    return finalPrice;
}

std::string TurboEngine::toString() {
    return "| Turbo Engine | Fuel Type: " + this->fuelType + " | "
           + "Base Price: " + std::to_string(this->basePrice);
}
