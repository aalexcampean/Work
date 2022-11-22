//
// Created by Alex Campean on 04.04.2022.
//

#include "UI.h"
#include <iostream>
#include <regex>

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

UI::UI() {
    this->service = new Service;
}


UI::UI(Service *inputService) {
    this->service = inputService;
}

UI::UI(const UI &ui) {
    this->service = ui.service;
}

UI::~UI() {
}

void UI::printMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add gene" << std::endl;
    std::cout << "------2. Show all genes" << std::endl;
    std::cout << "------3. Show genes with sequence" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void UI::start() {
    bool done = false;
    std::string option;
    this->service->addFirstEntries();

    while (!done) {
        try {
            this->printMenu();
            std::cout << "What do you want to do?" << std::endl;
            getline(std::cin, option);

            if (option == "1") {
                this->addFunctionalityUi();
            } else if (option == "2") {
                this->printAllGenesSorted();
            } else if (option == "3") {
                this->printAllGenesWithSequence();
            } else if (option == "0") {
                done = true;
            } else {
                std::cout << "No such command!" << std::endl;
                std::cout << "" << std::endl;
            }
        } catch (std::string error) {
            std::cout << "" << std::endl;
            std::cout << BOLDRED << error << RESET << std::endl;
            std::cout << "" << std::endl;
        }
    }

}

void UI::addFunctionalityUi() {
    std::string inputOrganism;
    std::string inputName;
    std::string inputSequence;

    std::cout << "" << std::endl;
    std::cout << "Organism Name: ";
    getline(std::cin, inputOrganism);

    /// Validating Organism Name Input
    if (inputOrganism.empty()) {
        throw std::string("Invalid empty organism name\n");
    }

    std::cout << "Gene Name: ";
    getline(std::cin, inputName);

    /// Validating Name Input
    if (inputName.empty()) {
        throw std::string("Invalid empty gene name\n");
    }

    std::cout << "Gene Sequence: ";
    getline(std::cin, inputSequence);

    /// Validating Sequence Input
//    const std::regex pattern("[ACGT]");
//
//    if (inputSequence.empty()) {
//        throw std::string("Invalid empty organism sequence\n");
//    }
//
//    if (!std::regex_match(inputSequence, pattern)) {
//        throw std::string("Invalid sequence, should only contain these letters: A, C, G, T\n");
//    }

    /// Adding the gene with the validating input to the service
    this->service->addGeneService(inputOrganism, inputName, inputSequence);

    /// Printing a message indicating that the addition was successful
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Gene added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void UI::printAllGenesSorted() {
    std::vector<Gene> sortedGenes = this->service->getAllSortedAscendingByOrganism();
    std::cout << "" << std::endl;
    std::for_each(sortedGenes.begin(), sortedGenes.end(), [](auto &it){std::cout << it.toString() << std::endl;});
}

void UI::printAllGenesWithSequence() {
    std::string inputSequence;
    std::cout << "Gene Sequence: ";
    getline(std::cin, inputSequence);

    std::vector<Gene> filteredGenes = this->service->getAllGenesContainingSequence(inputSequence);
    std::cout << "" << std::endl;
    std::for_each(filteredGenes.begin(), filteredGenes.end(), [](auto &it){std::cout << it.toString() << std::endl;});
}

