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
    std::cout << "------1. Delete bill" << std::endl;
    std::cout << "------2. Show all bills" << std::endl;
    std::cout << "------3. Show all paid bills sorted by date" << std::endl;
    std::cout << "------4. Find total sum of all unpaid bills" << std::endl;
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
                this->deleteFunctionalityUi();
            } else if (option == "2") {
                this->printAllBills();
            } else if (option == "3") {
                this->printAllPaidBillsSortedByDate();
            } else if (option == "4") {
                this->printTotalSumForUnpaidBills();
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

void Ui::deleteFunctionalityUi() {
    std::string inputSerialNumber;

    std::cout << "" << std::endl;
    std::cout << "Bill Serial Number: ";
    getline(std::cin, inputSerialNumber);

    this->service->deleteBillService(inputSerialNumber);

    /// Printing a message indicating that the deletion was successful
    std::cout << "" << std::endl;
    std::cout << BOLDGREEN << "Bill deleted successfully" << RESET << std::endl;
    std::cout << "" << std::endl;
}

void Ui::printAllBills() {
    std::vector<Bill> sortedBills = this->service->getAllService();
    std::cout << "" << std::endl;
    std::for_each(sortedBills.begin(), sortedBills.end(), [](auto &it){
        std::cout << it << std::endl;
    });
}

void Ui::printAllPaidBillsSortedByDate() {
    std::vector<Bill> sortedBills = this->service->getAllPaidBillsSortedByDueDate();
    std::cout << "" << std::endl;
    std::for_each(sortedBills.begin(), sortedBills.end(), [](auto &it){
        std::cout << it << std::endl;
    });
}

void Ui::printTotalSumForUnpaidBills() {
    double totalSum = this->service->computeTotalSumForUnpaidBills();
    std::cout << "" << std::endl;
    std::cout << "Total sum is: " << std::fixed << std::setprecision(2) << totalSum;
}
