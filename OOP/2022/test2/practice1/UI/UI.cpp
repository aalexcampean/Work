//
// Created by Alex Campean on 05.05.2022.
//

#include "UI.h"
#include <iostream>

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
                this->printAllAppliances();
            } else if (option == "3") {
                this->printSortedAppliances();
            } else if (option == "4") {
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
    std::cout << "------1. Add appliance" << std::endl;
    std::cout << "------2. Print all appliances" << std::endl;
    std::cout << "------3. Print appliances sorted by weight" << std::endl;
    std::cout << "------4. Save all appliances consuming less than, to a file" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UI::printAllAppliances() {
    std::cout << "" << std::endl;
    std::vector<Appliance*> allAppliances = this->service->getAllAppliances();
    for (auto it : allAppliances) {
        std::cout << it->toString() << std::endl;
    }
}

void UI::printSortedAppliances() {
    std::cout << "" << std::endl;
    std::vector<Appliance*> sortedAppliances = this->service->sortAppliancesByWeight();
    for (auto it : sortedAppliances) {
        std::cout << it->toString() << std::endl;
    }
}

void UI::addFunctionalityUi() {
    std::string id;
    std::cout << "Appliance ID: " << std::endl;
    getline(std::cin, id);

    std::string weight;
    std::cout << "Appliance Weight: " << std::endl;
    getline(std::cin, weight);

    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add Dish Washer" << std::endl;
    std::cout << "------2. Add Refrigerator" << std::endl;
    std::cout << "---------------------------" << std::endl;

    std::string option;
    try {
        std::cout << "What do you want to do?" << std::endl;
        getline(std::cin, option);

        if (option == "1") {
            this->addDishWasher(id, weight);
        } else if (option == "2") {
            this->addRefrigerator(id, weight);
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

void UI::addDishWasher(const std::string &id, const std::string &weight) {
    std::string washingCycleLength;
    std::cout << "DishWasher Washing Cycle Length: " << std::endl;
    getline(std::cin, washingCycleLength);

    std::string consumedEnergyForOneHour;
    std::cout << "DishWasher Consumed Energy/Hour: " << std::endl;
    getline(std::cin, consumedEnergyForOneHour);

    this->service->addDishWasherService(id, weight, washingCycleLength, consumedEnergyForOneHour);

    /// Printing A Message That The DishWasher Has Been Added Successfully
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "DishWasher added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void UI::addRefrigerator(const std::string &id, const std::string &weight) {
    std::string electricityUsageClass;
    std::cout << "Refrigerator Electricity Usage Class(A, A+, A++): " << std::endl;
    getline(std::cin, electricityUsageClass);

    std::string hasFreezer;
    std::cout << "Refrigerator Has Freezer(yes, no): " << std::endl;
    getline(std::cin, hasFreezer);

    this->service->addFridgeService(id, weight, electricityUsageClass, hasFreezer);

    /// Printing A Message That The Refrigerator Has Been Added Successfully
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Refrigerator added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void UI::saveToFile() {
    std::string fileName;
    std::cout << "File Name: " << std::endl;
    getline(std::cin, fileName);

    std::string consumption;
    std::cout << "Maximum Consumption: " << std::endl;
    getline(std::cin, consumption);

    this->service->saveToFileAppliancesWithConsumption(consumption, fileName);
}
