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
    ~Service();

    /// Getters
    int getServiceLength();
    std::vector<Building*> getAllBuildings();

    /// Sort, Filter Buildings
    std::vector<Building*> sortBuildingsAscByConstructionYear();
    std::vector<Building*> filterBuildingsMustBeRestored();
    std::vector<Building*> filterBuildingsMustBeDemolished();

    /// Add
    void addBlock(const std::string &address, const std::string &constructionYear, const std::string &totalApartments,
                  const std::string &occupiedApartments);
    void addHouse(const std::string &address, const std::string &constructionYear, const std::string &type,
                  const std::string &isHistorical);
    void addFirstBuildings();

    /// Save to file
    void saveToFilesBuildings(const std::string &fileNameDemolished, const std::string &fileNameRestored);
};