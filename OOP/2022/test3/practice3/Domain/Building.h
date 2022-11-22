//
// Created by Alex Campean on 05.05.2022.
//
#pragma once
#include <string>

class Building {
protected:
    std::string address;
    int constructionYear;
public:
    Building();
    Building(const std::string &inputAddress, int inputConstructionYear);
    ~Building();

    std::string getAddress() const;
    int getConstructionYear() const;

    virtual bool mustBeRestored() = 0;
    virtual bool mustBeDemolished() = 0;
    virtual std::string toString()=0;
};

