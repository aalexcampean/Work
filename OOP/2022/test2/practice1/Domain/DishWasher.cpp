//
// Created by Alex Campean on 05.05.2022.
//

#include "DishWasher.h"

DishWasher::DishWasher() {
}

DishWasher::DishWasher(const std::string &inputId, double inputWeight, double inputCycleLength,
                       double inputConsumedElectricity) : Appliance(inputId, inputWeight) {
    this->washingCycleLength = inputCycleLength;
    this->consumedEnergyForOneHour = inputConsumedElectricity;
}

DishWasher::~DishWasher() {
}

double DishWasher::consumedEnergy() {
    return this->consumedEnergyForOneHour * this->washingCycleLength * 8;
}

std::string DishWasher::toString() {
    return "| Dishwasher | ID: " + this->id + " | "
           + "Weight: " + std::to_string(this->weight) + " | "
           + "Washing Cycle Length: " + std::to_string(this->washingCycleLength) + " | "
           + "Hourly Consumed Energy: " + std::to_string(this->consumedEnergyForOneHour);
}
