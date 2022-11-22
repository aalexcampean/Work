//
// Created by Alex Campean on 05.05.2022.
//
#pragma once

#include <string>

class Engine {
protected:
    std::string fuelType;
    double basePrice;
public:
    Engine(const std::string &inputFuelType, double inputBasePrice);
    ~Engine();

    /// Getters
    std::string getFuelType() const;
    double getBasePrice() const;

    virtual double getPrice()=0;
    virtual std::string toString()=0;
};