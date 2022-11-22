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

    /// Add Functionality Ui
    void addFunctionalityUi();

    /// Print All Genes Sorted
    void printAllProjectsSorted();
    void printTotalCostForFinishedProjects();
};


