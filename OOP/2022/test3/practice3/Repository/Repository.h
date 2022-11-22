//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include <vector>
#include "../Domain/Building.h"

class Repository {
private:
    std::vector<Building*> buildings;
public:
    /// Constructors, Destructor
    Repository()= default;;
    ~Repository()= default;

    /// Getters
    int getRepoLength() const;
    std::vector<Building*> getBuildings() const;

    /// Add
    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="&building">Building, a reference to the building to be added to the repository</param>
    /// <returns></returns
    void addElementRepo(Building *building);

};
