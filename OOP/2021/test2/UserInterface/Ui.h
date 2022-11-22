#pragma once
#include "../Person/Person.h"

class Ui {
private:
    Person person;

public:
    Ui(){};
    ~Ui(){};

    void startUi();
    void printMenu();

    void displayAll();
    void addFunctionality();
    void showIsHealthy();
    void saveToFile();
    bool isNumber(const std::string &s);

};


