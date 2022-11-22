//
// Created by Alex Campean on 05.05.2022.
//

#include "Repository.h"

int Repository::getRepoLength() const {
    return this->appliances.size();
}

std::vector<Appliance*> Repository::getAppliances() const {
    return this->appliances;
}

void Repository::addElementRepo(Appliance *appliance) {
    if (std::find_if(this->appliances.begin(), this->appliances.end(), [appliance](Appliance* a) {
        return a->getId() == appliance->getId();
    }) != this->appliances.end()) {
        throw std::string("Appliance already exists");
    }
    this->appliances.push_back(appliance);
}
