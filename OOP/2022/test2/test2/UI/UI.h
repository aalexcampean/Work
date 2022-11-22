//
// Created by Alex Campean on 05.05.2022.
//
#include "../Service/Service.h"

class UI {
private:
    Service* service;
public:
    UI(Service *inputService);
    ~UI();

    void startUI();

    void printMenu();

    void printAllCars();

    void addFunctionalityUi();

    void saveToFile();
};