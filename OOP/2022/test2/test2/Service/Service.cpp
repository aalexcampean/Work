//
// Created by Alex Campean on 05.05.2022.
//

#include <fstream>
#include "Service.h"

Service::Service() {
    this->addInitialCars();
}

Engine *
Service::createEngine(const std::string &engineType, const std::string &fuelType, int autonomy) {
    if (engineType == "electric") {
        return new ElectricEngine("electricity", 3000, autonomy);
    }
    return new TurboEngine(fuelType, 3000);
}

std::vector<Car> Service::getAllCars() {
    return this->cars;
}

std::vector<Car> Service::getCarsWithMaxPrice(double maxPrice) {
    std::vector<Car> filteredCars;
    std::copy_if(this->cars.begin(), this->cars.end(), std::back_inserter(filteredCars), [&maxPrice](Car& car){
        return true;
    });
    return filteredCars;
}

void Service::addCar(int numberOfDoors, const std::string &engineType, const std::string &fuelType, int autonomy) {
    Car car(numberOfDoors, this->createEngine(engineType, fuelType, autonomy));
    this->cars.push_back(car);
}

void Service::addInitialCars() {
    Car car1 = Car(4, createEngine("electric", "diesel", 500));
    Car car2 = Car(4, createEngine("turbo", "diesel", 1200));
    Car car3 = Car(2, createEngine("electric", "gasoline", 150));
    Car car4 = Car(4, createEngine("turbo", "gasoline", 1200));
    this->cars.push_back(car1);
    this->cars.push_back(car2);
    this->cars.push_back(car3);
    this->cars.push_back(car4);
}

void Service::writeToFile(const std::string &fileName, std::vector<Car>& givenCars) {
    std::ofstream output(fileName);
    for (Car &car: givenCars) {
        output << car << "\n";
    }
    output.close();
}
