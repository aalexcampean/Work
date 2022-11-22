//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include <vector>
#include "../Domain/Appliance.h"

class Repository {
private:
    std::vector<Appliance*> appliances;
public:
    /// Constructors, Destructor
    Repository()= default;;
    ~Repository()= default;

    /// Getters
    int getRepoLength() const;
    std::vector<Appliance*> getAppliances() const;

    /// Add
    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="&appliance">Appliance, a reference to the appliance to be added to the repository</param>
    /// <returns></returns
    void addElementRepo(Appliance *appliance);
};
