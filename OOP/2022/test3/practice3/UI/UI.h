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

    void printAllBuildings();
    void printSortedBuildings();

    void addFunctionalityUi();
    void addBlock(const std::string &address, const std::string &constructionYear);
    void addHouse(const std::string &address, const std::string &constructionYear);

    void saveToFile();
};
