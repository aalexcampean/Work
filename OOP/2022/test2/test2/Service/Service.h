//
// Created by Alex Campean on 05.05.2022.
//
#pragma once

#include <vector>
#include "../Domain/Car.h"
#include "../Domain/ElectricEngine.h"
#include "../Domain/TurboEngine.h"

class Service {
private:
    std::vector<Car> cars;
    Engine* createEngine(const std::string &engineType, const std::string &fuelType, int autonomy);
public:
    Service();
    ~Service()=default;

    /// Getters
    std::vector<Car> getAllCars();
    std::vector<Car> getCarsWithMaxPrice(double maxPrice);

    /// Add
    void addCar(int numberOfDoors, const std::string &engineType, const std::string &fuelType, int autonomy);
    void addInitialCars();

    /// WriteToFile
    void writeToFile(const std::string &fileName, std::vector<Car>& givenCars);
};