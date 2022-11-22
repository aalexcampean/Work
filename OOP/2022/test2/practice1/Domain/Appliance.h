//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include <string>

class Appliance {
protected:
    std::string id;
    double weight;
public:
    /// Constructors, Destructors
    Appliance();
    Appliance(const std::string &inputId, double inputWeight);
    ~Appliance();

    /// Getters
    std::string getId() const;
    double getWeight() const;

    virtual double consumedEnergy()=0;
    virtual std::string toString()=0;

    /// Operator overload
    bool operator==(Appliance *appliance) const;
};
