//
// Created by Alex Campean on 05.05.2022.
//

#include "Appliance.h"

Appliance::Appliance() {
}

Appliance::Appliance(const std::string &inputId, double inputWeight) {
    this->id = inputId;
    this->weight = inputWeight;
}

Appliance::~Appliance() {
}

std::string Appliance::getId() const {
    return this->id;
}

double Appliance::getWeight() const {
    return this->weight;
}

bool Appliance::operator==(Appliance *appliance) const {
    return this->id == appliance->id;
}
