//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include "Engine.h"
#include <iostream>

class Car {
private:
    int numberOfDoors;
    Engine* engine;
public:
    Car(int inputNumberOfDoors, Engine* inputEngine);
    ~Car();

    double computePrice();
    friend std::ostream& operator<<(std::ostream& out, const Car &ca);
};
inline std::ostream& operator<<(std::ostream& out, const Car &car) {
    out << car.numberOfDoors << " | ";
    out << car.engine->toString();
    return out;
}