//
// Created by Alex Campean on 06.04.2022.
//

#include "Ui.h"

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDRED     "\033[1m\033[31m"

Ui::Ui() {
    this->service = new Service;
}

Ui::Ui(Service *inputService) {
    this->service = inputService;
}

Ui::~Ui() {
}

void Ui::printMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "------1. Add project" << std::endl;
    std::cout << "------2. Show all sorted projects by date" << std::endl;
    std::cout << "------3. Find total cost of all finished projects" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void Ui::start() {
    bool done = false;
    std::string option;
    this->service->addInitialEntries();

    while (!done) {
        try {
            this->printMenu();
            std::cout << "What do you want to do?" << std::endl;
            getline(std::cin, option);

            if (option == "1") {
                this->addFunctionalityUi();
            } else if (option == "2") {
                this->printAllProjectsSorted();
            } else if (option == "3") {
                this->printTotalCostForFinishedProjects();
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

void Ui::addFunctionalityUi() {
    std::string inputName;
    std::string inputCustomer;

    std::string inputDay;
    std::string inputMonth;
    std::string inputYear;

    std::string inputCost;
    std::string inputIsDone;

    std::cout << "" << std::endl;
    std::cout << "Project Name: ";
    getline(std::cin, inputName);

    /// Validating Organism Name Input
    if (inputName.empty()) {
        throw std::string("Invalid empty project name\n");
    }

    std::cout << "Project Customer: ";
    getline(std::cin, inputCustomer);

    /// Validating Name Input
    if (inputCustomer.empty()) {
        throw std::string("Invalid empty customer name\n");
    }

    std::cout << "Project Year: ";
    getline(std::cin, inputYear);
    size_t pos1;
    int validYear = std::stoi(inputYear, &pos1);


    std::cout << "Project Month: ";
    getline(std::cin, inputMonth);
    size_t pos2;
    int validMonth = std::stoi(inputMonth, &pos1);

    std::cout << "Project Day: ";
    getline(std::cin, inputDay);
    size_t pos3;
    int validDay = std::stoi(inputDay, &pos1);
    
    std::cout << "Project Cost: ";
    getline(std::cin, inputCost);
    size_t pos4;
    int validCost = std::stod(inputCost, &pos1);

    std::cout << "Project Done(true/false): ";
    getline(std::cin, inputIsDone);
    bool validIsDone = inputIsDone == "true"? true : false;

    this->service->addProjectService(inputName, inputCustomer, validDay, validMonth, validYear, validCost, validIsDone);

    /// Printing a message indicating that the addition was successful
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Project added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void Ui::printAllProjectsSorted() {
    std::vector<Project> sortedProjects = this->service->getAllProjectsSortedDecreasingByDate();
    std::cout << "" << std::endl;
    std::for_each(sortedProjects.begin(), sortedProjects.end(), [](auto &it){
        std::cout << it << std::endl;
    });
}

void Ui::printTotalCostForFinishedProjects() {
    double totalCost = this->service->computeTotalCostForFinishedProjects();
    std::cout << "" << std::endl;
    std::cout << "Total cost is: " << std::fixed << std::setprecision(2) << totalCost;
}
