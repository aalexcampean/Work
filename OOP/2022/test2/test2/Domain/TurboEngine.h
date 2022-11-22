//
// Created by Alex Campean on 05.05.2022.
//
#pragma once

#include "Engine.h"

class TurboEngine : public Engine {
public:
    TurboEngine(const std::string &inputFuelType, double inputBasePrice);
    ~TurboEngine();

    double getPrice() override;
    std::string toString() override;
};
