//
// Created by Alex Campean on 05.05.2022.
//

#pragma once
#include "Engine.h"

class ElectricEngine : public Engine {
private:
    int autonomy;
public:
    ElectricEngine(const std::string &inputFuelType, double inputBasePrice, int inputAutonomy);
    ~ElectricEngine();

    double getPrice() override;
    std::string toString() override;
};
