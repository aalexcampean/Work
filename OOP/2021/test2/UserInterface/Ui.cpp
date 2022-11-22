#include "Ui.h"
#include "../Exception/CustomException.h"
#include "BMI.h"
#include "BP.h"
#include <iostream>
#include <sstream>
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

void Ui::startUi() {
    bool ok = false;
    std::string option;
    this->person.addFirstMeasurements();

    while (!ok) {
        try {
            this->printMenu();
            std::cout << "What do you want to do?" << std::endl;
            getline(std::cin, option);

            if (option == "1") {
                this->addFunctionality();
            } else if (option == "2") {
                this->displayAll();
            } else if (option == "3") {
                this->showIsHealthy();
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
        catch (const CustomException &e){
            std::cout << "" << std::endl;
            std::cout << BOLDRED << e.what() << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

void Ui::printMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add measurement" << std::endl;
    std::cout << "------2. Show all measurements" << std::endl;
    std::cout << "------3. Show if person is healthy" << std::endl;
    std::cout << "------4. Save to file all measurements after a given date" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}


void Ui::displayAll() {
    for (auto it : this->person.getAllMeasurements()) {
        std::cout << it->toString() << std::endl;
    }
}

void Ui::addFunctionality() {
    std::string date;
    std::cout << "MEASUREMENT DATE (day/month/year): " << std::endl;
    getline(std::cin, date);

    std::string option;
    std::cout << "What would you like to add?" << std::endl;
    std::cout << "1. BP" << std::endl;
    std::cout << "2. BMI" << std::endl;
    getline(std::cin, option);

    if (option == "1") {
        std::string systolicValue;
        std::cout << "SYSTOLIC VALUE: " << std::endl;
        getline(std::cin, systolicValue);

        if (!this->isNumber(systolicValue)) {
            throw CustomException(0001, "Invalid input for the field systolic value (should be an integer value)");
        }

        std::string diastolicValue;
        std::cout << "DIASTOLIC VALUE: " << std::endl;
        getline(std::cin, diastolicValue);

        if (!this->isNumber(systolicValue)) {
            throw CustomException(0001, "Invalid input for the field diastolic value (should be an integer value)");
        }

        Measurement* m = new BP{date, std::stoi(systolicValue), std::stoi(diastolicValue)};
        this->person.addMeasurements(m);

    }
    else {
        std::string value;
        std::cout << "VALUE: " << std::endl;
        getline(std::cin, value);

        if (!this->isNumber(value)) {
            throw CustomException(0001, "Invalid input for the field value (should be a double value)");
        }

        Measurement* m = new BMI{date, std::stod(value)};
        this->person.addMeasurements(m);
    }
}

void Ui::showIsHealthy() {
    std::string month;
    std::cout << "MONTH: " << std::endl;
    getline(std::cin, month);
    if (!this->isNumber(month)) {
        throw CustomException(0001, "Invalid input for the field month (should be an integer value)");
    }

    if (this->person.isHealthy(std::stoi(month))) {
        std::cout << "Is Healthy" << std::endl;
    }
    else {
        std::cout << "Is Not Healthy" << std::endl;
    }
}

void Ui::saveToFile() {

}

bool Ui::isNumber(const std::string &s) {
    long double ld;
    return((std::istringstream(s) >> ld >> std::ws).eof());
}
