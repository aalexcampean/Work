//
// Created by Alex Campean on 05.05.2022.
//

#include "Refrigerator.h"

Refrigerator::Refrigerator() {
}

Refrigerator::Refrigerator(const std::string &inputId, double inputWeight, const std::string &inputClass,
                           bool inputFreezer) : Appliance(inputId, inputWeight) {
    this->electricityUsageClass = inputClass;
    this->hasFreezer = inputFreezer;
}

Refrigerator::~Refrigerator() {
}

double Refrigerator::consumedEnergy() {
    double consumedEnergy = 30;
    if (this->electricityUsageClass == "A") {
        consumedEnergy *= 3;
    } else if (this->electricityUsageClass == "A+") {
        consumedEnergy *= 2.5;
    } else {
        consumedEnergy *= 2;
    }

    return this->hasFreezer ? consumedEnergy + 20 : consumedEnergy;
}

std::string Refrigerator::toString() {
    return "| Refrigerator | ID: " + this->id + " | "
           + "Weight: " + std::to_string(this->weight) + " | "
           + "Electricity Class: " + this->electricityUsageClass + " | "
           + "Freezer: " + (this->hasFreezer ? "yes" : "no");
}
