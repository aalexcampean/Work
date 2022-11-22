//
// Created by Alex Campean on 06.04.2022.
//

#include "../Service/Service.h"

class Ui {
private:
    Service* service;
public:
    Ui();
    Ui(Service* inputService);
    ~Ui();

    /// Print Menu
    void printMenu();

    /// Start
    void start();

    /// Delete Functionality Ui
    void deleteFunctionalityUi();

    /// Prints
    void printAllBills();
    void printAllPaidBillsSortedByDate();
    void printTotalSumForUnpaidBills();
};


