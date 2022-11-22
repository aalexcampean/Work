//
// Created by Alex Campean on 05.05.2022.
//

#include "Repository.h"

int Repository::getRepoLength() const {
    return this->buildings.size();
}

std::vector<Building *> Repository::getBuildings() const {
    return this->buildings;
}

void Repository::addElementRepo(Building *building) {
    if (std::find_if(this->buildings.begin(), this->buildings.end(), [building](Building* b) {
        return b->getAddress() == building->getAddress();
    }) != this->buildings.end()) {
        throw std::string("Building already exists");
    }
    this->buildings.push_back(building);
}
