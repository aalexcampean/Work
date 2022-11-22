//
// Created by Alex Campean on 05.05.2022.
//

#include <fstream>
#include "Service.h"
#include "../Domain/House.h"
#include "../Domain/Block.h"

Service::Service(Repository *inputRepository) {
    this->repository = inputRepository;
    this->addFirstBuildings();
}

Service::~Service() {
}

int Service::getServiceLength() {
    return this->repository->getRepoLength();
}

std::vector<Building *> Service::getAllBuildings() {
    return this->repository->getBuildings();
}

std::vector<Building *> Service::sortBuildingsAscByConstructionYear() {
    std::vector<Building*> allBuildings = this->repository->getBuildings();
    std::sort(allBuildings.begin(), allBuildings.end(),[](Building* b1, Building* b2) -> bool {
        return b1->getConstructionYear() < b2->getConstructionYear();
    });
    return allBuildings;
}

std::vector<Building *> Service::filterBuildingsMustBeRestored() {
    std::vector<Building*> allBuildings = this->repository->getBuildings();
    std::vector<Building*> filteredBuildings;
    std::copy_if(allBuildings.begin(), allBuildings.end(), std::back_inserter(filteredBuildings), [](Building* b){
        return b->mustBeRestored();
    });
    return filteredBuildings;
}

std::vector<Building *> Service::filterBuildingsMustBeDemolished() {
    std::vector<Building*> allBuildings = this->repository->getBuildings();
    std::vector<Building*> filteredBuildings;
    std::copy_if(allBuildings.begin(), allBuildings.end(), std::back_inserter(filteredBuildings), [](Building* b){
        return b->mustBeDemolished();
    });
    return filteredBuildings;
}

void Service::addBlock(const std::string &address, const std::string &constructionYear, const std::string &totalApartments,
                       const std::string &occupiedApartments) {
    size_t pos1;
    int validatedConstructionYear = std::stoi(constructionYear, &pos1);

    size_t pos2;
    int validatedTotalApartments = std::stoi(totalApartments, &pos2);

    size_t pos3;
    int validatedOccupiedApartments = std::stoi(occupiedApartments, &pos3);

    Block *block = new Block(address, validatedConstructionYear, validatedTotalApartments, validatedOccupiedApartments);
    this->repository->addElementRepo(block);
}

void Service::addHouse(const std::string &address, const std::string &constructionYear, const std::string &type,
                       const std::string &isHistorical) {
    size_t pos1;
    int validatedConstructionYear = std::stoi(constructionYear, &pos1);

    bool validatedIsHistorical = (isHistorical == "yes");

    House *house = new House(address, validatedConstructionYear, type, validatedIsHistorical);
    this->repository->addElementRepo(house);
}

void Service::addFirstBuildings() {
    this->repository->addElementRepo(new Block("Gheorghe Lazar 19A", 2008, 3, 3));
    this->repository->addElementRepo(new Block("Plopilor 120", 1995, 30, 10));
    this->repository->addElementRepo(new House("Republicii 3", 1930, "one story house", true));
    this->repository->addElementRepo(new House("Aurel Vlaicu 40", 2001, "two story house", false));
}

void Service::saveToFilesBuildings(const std::string &fileNameDemolished, const std::string &fileNameRestored) {
    std::vector<Building*> demolishedBuildings = this->filterBuildingsMustBeDemolished();
    std::vector<Building*> restoredBuildings = this->filterBuildingsMustBeRestored();

    std::ofstream output1(fileNameDemolished);
    for (Building* b : demolishedBuildings) {
        output1 << b->toString() << "\n";
    }
    output1.close();

    std::ofstream output2(fileNameRestored);
    for (Building* b : restoredBuildings) {
        output2 << b->toString() << "\n";
    }
    output2.close();
}
