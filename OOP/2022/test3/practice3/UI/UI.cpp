//
// Created by Alex Campean on 05.05.2022.
//

#include <iostream>
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
                this->printAllBuildings();
            } else if (option == "3") {
                this->printSortedBuildings();
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
    std::cout << "------1. Add building" << std::endl;
    std::cout << "------2. Print all buildings" << std::endl;
    std::cout << "------3. Print buildings sorted by construction year" << std::endl;
    std::cout << "------4. Save all buildings based on being ready to be demolished/restored into 2 files" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UI::printAllBuildings() {
    std::cout << "" << std::endl;
    std::vector<Building*> allBuildings = this->service->getAllBuildings();
    for(Building* b : allBuildings) {
        std::cout << b->toString() << std::endl;
    }
}

void UI::printSortedBuildings() {
    std::cout << "" << std::endl;
    std::vector<Building*> sortedBuildings = this->service->sortBuildingsAscByConstructionYear();
    for(Building* b : sortedBuildings) {
        std::cout << b->toString() << std::endl;
    }
}

void UI::addFunctionalityUi() {
    std::string address;
    std::cout << "Building Address: " << std::endl;
    getline(std::cin, address);

    std::string constructionYear;
    std::cout << "Building Construction Year: " << std::endl;
    getline(std::cin, constructionYear);

    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add Block" << std::endl;
    std::cout << "------2. Add House" << std::endl;
    std::cout << "---------------------------" << std::endl;

    std::string option;
    try {
        std::cout << "What do you want to do?" << std::endl;
        getline(std::cin, option);

        if (option == "1") {
            this->addBlock(address, constructionYear);
        } else if (option == "2") {
            this->addHouse(address, constructionYear);
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

void UI::addBlock(const std::string &address, const std::string &constructionYear) {
    std::string totalApartments;
    std::cout << "Block's Number of Apartments: " << std::endl;
    getline(std::cin, totalApartments);

    std::string occupiedApartments;
    std::cout << "Block's Number of Occupied Apartments: " << std::endl;
    getline(std::cin, occupiedApartments);

    this->service->addBlock(address, constructionYear, totalApartments, occupiedApartments);

    /// Printing A Message That The Block Has Been Added Successfully
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Block added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void UI::addHouse(const std::string &address, const std::string &constructionYear) {
    std::string type;
    std::cout << "House Type(one story house/two stories house/duplex): " << std::endl;
    getline(std::cin, type);

    std::string isHistorical;
    std::cout << "Is a Historic House: " << std::endl;
    getline(std::cin, isHistorical);

    this->service->addHouse(address, constructionYear, type, isHistorical);

    /// Printing A Message That The House Has Been Added Successfully
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "House added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void UI::saveToFile() {
    std::string demolishedFileName;
    std::cout << "File Name for Demolished Buildings: " << std::endl;
    getline(std::cin, demolishedFileName);

    std::string restoredFileName;
    std::cout << "File Name for Restored Buildings: " << std::endl;
    getline(std::cin, restoredFileName);

    this->service->saveToFilesBuildings(demolishedFileName, restoredFileName);
}
