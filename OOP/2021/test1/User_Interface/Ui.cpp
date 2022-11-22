#include "Ui.h"
#include <iostream>
#include <string>
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

Ui::Ui() {
    Service designated_service;
    this->service = designated_service;
}

Ui::Ui(Ui &ui) {
    this->service = ui.service;
}

Ui::~Ui() {

}

void Ui::start() {
    this->service.firstGenes();
    bool ok = false;
    std::string option;

    while (!ok) {
        try {
            this->printStartMenu();
            getline(std::cin, option);

            if (option == "1") {
                this->addFunctionalityUi();
            } else if (option == "2") {
                this->printGenesInDatabase();
            } else if (option == "0") {
                std::cout << "---------------------------" << std::endl;
                std::cout << "Byes Bye" << std::endl;
                std::cout << "---------------------------" << std::endl;
                ok = true;
            } else {
                std::cout << "No such command" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        catch (std::string exp) {
            std::cout << "" << std::endl;
            std::cout << BOLDRED << exp << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }
}

void Ui::printStartMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add Gene" << std::endl;
    std::cout << "------2. Display All Genes" << std::endl;
    std::cout << "------2. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void Ui::printGenesInDatabase() {
    std::cout << "" << std::endl;
    for (int i = 0; i < this->service.getLength(); i++) {
        std::cout << this->service[i].toString() << std::endl;
    }
}

void Ui::addFunctionalityUi() {
    std::string input_organism;
    std::string input_name;
    std::string input_sequence;

    std::cout << "" << std::endl;
    std::cout << "Organism: ";
    getline(std::cin, input_organism);

    std::cout << "Name: ";
    getline(std::cin, input_name);

    std::cout << "Sequence: ";
    getline(std::cin, input_sequence);

    // actually calling the add function for the validated input
    this->service.addElementService(input_organism, input_name, input_sequence);

    // printing a message that the movie was successfully added
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Gene added" << RESET << std::endl;
    std::cout << "" << std::endl;
}
