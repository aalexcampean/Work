//
// Created by Alex Campean on 05.05.2022.
//
#include "Service.h"
#include "../Domain/Refrigerator.h"
#include "../Domain/DishWasher.h"
#include <iostream>
#include <fstream>
#include <sstream>

Service::Service(Repository *inputRepository) {
    this->repository = inputRepository;
    this->addFirstEntries();
}

Service::Service(const Service &service) {
    this->repository = service.repository;
}

Service::~Service() {
}

int Service::getServiceLength() const {
    return this->repository->getRepoLength();
}

std::vector<Appliance*> Service::getAllAppliances() const {
    return this->repository->getAppliances();
}

/// Sort, Filter Appliances
std::vector<Appliance *> Service::sortAppliancesByWeight() const {
    std::vector<Appliance*> allAppliances = this->repository->getAppliances();
    std::sort(allAppliances.begin(), allAppliances.end(),[](Appliance* a1, Appliance* a2) -> bool {
             return a1->getWeight() < a2->getWeight();
    });
    return allAppliances;
}

std::vector<Appliance *> Service::filterAppliancesByConsumptionLessThan(double consumption) const {
    std::vector<Appliance*> allAppliances = this->repository->getAppliances();
    std::vector<Appliance*> filteredAppliances;
    std::copy_if(allAppliances.begin(), allAppliances.end(), std::back_inserter(filteredAppliances), [consumption](Appliance* a){
        return a->consumedEnergy() < consumption;
    });
    return filteredAppliances;
}

/// Add Appliances
void Service::addFridgeService(const std::string &id, const std::string &weight, const std::string &electricityClass,
                               const std::string &hasFreezer) {
    size_t pos2;
    double validatedWeight = std::stod(weight, &pos2);

    bool validatedHasFreezer = (hasFreezer == "yes");

    Refrigerator *refrigerator = new Refrigerator(id, validatedWeight, electricityClass, validatedHasFreezer);
    this->repository->addElementRepo(refrigerator);
}

void Service::addDishWasherService(const std::string &id, const std::string &weight, const std::string &washingLength,
                                   const std::string &consumedEnergy) {
    size_t pos1;
    double validatedWeight = std::stod(weight, &pos1);

    size_t pos2;
    double validatedWashingLength = std::stod(washingLength, &pos2);

    size_t pos3;
    double validatedConsumedEnergy = std::stod(consumedEnergy, &pos3);

    DishWasher *dishWasher = new DishWasher(id, validatedWeight, validatedConsumedEnergy, validatedWashingLength);
    this->repository->addElementRepo(dishWasher);
}

void Service::addFirstEntries() {
    this->repository->addElementRepo(new DishWasher("1", 28, 2, 50));
    this->repository->addElementRepo(new DishWasher("2", 50, 5, 150));
    this->repository->addElementRepo(new Refrigerator("3", 80, "A++", true));
    this->repository->addElementRepo(new Refrigerator("4", 75, "A", false));
}

void Service::saveToFileAppliancesWithConsumption(const std::string &consumption, const std::string &fileName) {
    size_t pos1;
    double validatedConsumption = std::stod(consumption, &pos1);

    std::vector<Appliance*> filteredAppliances = this->filterAppliancesByConsumptionLessThan(validatedConsumption);

    std::ofstream output(fileName);
    for (Appliance* a : filteredAppliances) {
        output << a->toString() << "\n";
    }
    output.close();
}