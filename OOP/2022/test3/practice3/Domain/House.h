//
// Created by Alex Campean on 05.05.2022.
//
#pragma on]
#include "Building.h"

class House : public Building{
private:
    std::string type;
    bool isHistorical;
public:
    House();
    House(const std::string &inputAddress, int inputConstructionYear, const std::string &inputType, bool inputIsHistorical);
    ~House();

    bool mustBeRestored() override;
    bool mustBeDemolished() override;
    std::string toString() override;
};
