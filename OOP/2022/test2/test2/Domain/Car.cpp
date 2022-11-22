//
// Created by Alex Campean on 05.05.2022.
//

#include "Car.h"

Car::Car(int inputNumberOfDoors, Engine *inputEngine) {
    this->numberOfDoors = inputNumberOfDoors;
    this->engine = inputEngine;
}

Car::~Car() {
}

double Car::computePrice() {
    double finalPrice;
    finalPrice = this->engine->getPrice();
    double carBasePrice = this->numberOfDoors == 2? 7000 : 8500;
    finalPrice += carBasePrice;
    return finalPrice;
}
