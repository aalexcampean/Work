//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include "../Service/Service.h"

class UI {
private:
    Service* service;
public:
    UI(Service *inputService);
    ~UI();

    void startUI();

    void printMenu();

    void printAllAppliances();
    void printSortedAppliances();

    void addFunctionalityUi();
    void addDishWasher(const std::string &id, const std::string &weight);
    void addRefrigerator(const std::string &id, const std::string &weight);

    void saveToFile();
};
