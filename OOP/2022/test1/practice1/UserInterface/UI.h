//
// Created by Alex Campean on 04.04.2022.
//

#include "../Service/Service.h"

class UI {
private:
    Service* service;
public:
    /// Constructors, Destructor
    UI();
    UI(Service* inputService);
    UI(const UI &ui);
    ~UI();

    /// Print Menu
    void printMenu();

    /// Start
    void start();

    /// Add Functionality Ui
    void addFunctionalityUi();

    /// Print All Genes Sorted
    void printAllGenesSorted();
    void printAllGenesWithSequence();
};


