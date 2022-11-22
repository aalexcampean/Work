//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include "../Repository/Repository.h"

class Service {
private:
    Repository *repository;
public:
    Service(Repository *inputRepository);
    Service(const Service &service);
    ~Service();

    /// Getters
    int getServiceLength() const;
    std::vector<Appliance*> getAllAppliances() const;

    /// Sort, Filter Appliances
    std::vector<Appliance*> sortAppliancesByWeight() const;
    std::vector<Appliance*> filterAppliancesByConsumptionLessThan(double consumption) const;

    /// Add
    void addFridgeService(const std::string &id, const std::string &weight, const std::string &electricityClass, const std::string &hasFreezer);
    void addDishWasherService(const std::string &id, const std::string &weight, const std::string &washingLength, const std::string &consumedEnergy);
    void addFirstEntries();

    /// Save to file
    void saveToFileAppliancesWithConsumption(const std::string &consumption, const std::string &fileName);
};
