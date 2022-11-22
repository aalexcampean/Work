//
// Created by Alex Campean on 05.05.2022.
//

#include "UI.h"

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

UI::UI(Service *inputService) {
    this->service = inputService;

}

UI::~UI() {
}

void UI::startUI() {
    bool ok = false;
    std::string option;

    while (!ok) {
        try {
            this->printMenu();
            std::cout << "What do you want to do?" << std::endl;
            getline(std::cin, option);

            if (option == "1") {
                this->addFunctionalityUi();
            } else if (option == "2") {
                this->printAllCars();
            } else if (option == "3") {
                this->saveToFile();
            } else if (option == "0") {
                std::cout << "" << std::endl;
                std::cout << "Bye bye!" << std::endl;
                ok = true;
            } else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        catch (std::string &exception) {
            std::cout << "" << std::endl;
            std::cout << BOLDRED << exception << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

void UI::printMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add Car" << std::endl;
    std::cout << "------2. Print all cars" << std::endl;
    std::cout << "------3. Save all cars cheaper than..., to a file" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UI::printAllCars() {
    std::cout << "" << std::endl;
    std::vector<Car> allCars = this->service->getAllCars();
    for (auto& car : allCars) {
        std::cout << car << std::endl;
    }
}

void UI::addFunctionalityUi() {
    std::string numberOfDoors;
    std::cout << "Car's Number Of Doors: " << std::endl;
    getline(std::cin, numberOfDoors);

    size_t pos1;
    int validatedNumberOfDoors = std::stoi(numberOfDoors, &pos1);

    std::string engineType;
    std::cout << "Car's Engine Type: " << std::endl;
    getline(std::cin, engineType);

    std::string fuelType;
    std::cout << "Car's Fuel Type: " << std::endl;
    getline(std::cin, fuelType);

    std::string autonomy;
    std::cout << "Car's Autonomy(for Electric Cars): " << std::endl;
    getline(std::cin, autonomy);

    size_t pos2;
    int validatedAutonomy = std::stoi(autonomy, &pos2);

    this->service->addCar(validatedNumberOfDoors, engineType, fuelType, validatedAutonomy);
}

void UI::saveToFile() {
    std::string fileName;
    std::cout << "File Name: " << std::endl;
    getline(std::cin, fileName);

    std::string maxPrice;
    std::cout << "Maximum Price: " << std::endl;
    getline(std::cin, maxPrice);

    size_t pos1;
    double validatedPrice = std::stod(maxPrice, &pos1);

    std::vector<Car> filteredCars = this->service->getCarsWithMaxPrice(validatedPrice);
    this->service->writeToFile(fileName, filteredCars);
}
