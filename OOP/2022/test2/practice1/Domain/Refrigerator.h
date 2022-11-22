//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include "Appliance.h"

class Refrigerator : public Appliance{
private:
    std::string electricityUsageClass;
    bool hasFreezer;
public:
    Refrigerator();
    Refrigerator(const std::string &inputId, double inputWeight, const std::string &inputClass, bool inputFreezer);
    ~Refrigerator();

    double consumedEnergy() override;
    std::string toString() override;
};
