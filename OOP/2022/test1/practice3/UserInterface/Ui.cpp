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
    std::cout << "------1. Add task" << std::endl;
    std::cout << "------2. Show all sorted task by priority" << std::endl;
    std::cout << "------3. Find total duration for all tasks with priority less than" << std::endl;
    std::cout << "------0. Exit" << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void Ui::start() {
    bool done = false;
    std::string option;
    this->service->firstEntries();

    while (!done) {
        try {
            this->printMenu();
            std::cout << "What do you want to do?" << std::endl;
            getline(std::cin, option);

            if (option == "1") {
                this->addFunctionalityUi();
            } else if (option == "2") {
                this->printAllTasksSorted();
            } else if (option == "3") {
                this->printTotalDurationForTasksWithPriority();
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
    std::string inputDescription;
    std::string inputDuration;
    std::string inputPriority;

    std::cout << "" << std::endl;
    std::cout << "Task Description: ";
    getline(std::cin, inputDescription);

    std::cout << "Task Duration: ";
    getline(std::cin, inputDuration);

    std::cout << "Task Priority: ";
    getline(std::cin, inputPriority);

    this->service->addTaskService(inputDescription, inputDuration, inputPriority);

    /// Printing a message indicating that the addition was successful
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Task added successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void Ui::printAllTasksSorted() {
    std::vector<Task> sortedTasks = this->service->getAllTasksSortedDescendingByPriority();
    std::cout << "" << std::endl;
    std::for_each(sortedTasks.begin(), sortedTasks.end(), [](auto &it){
        std::cout << it << std::endl;
    });
}

void Ui::printTotalDurationForTasksWithPriority() {
    std::string inputPriority;

    std::cout << "" << std::endl;
    std::cout << "Desired Priority: ";
    getline(std::cin, inputPriority);

    int totalDuration = this->service->computeDurationForTasksWithPriorityLessThan(inputPriority);
    std::cout << "" << std::endl;
    std::cout << "Total cost is: " << totalDuration;
}
