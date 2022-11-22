//
// Created by Alex Campean on 05.05.2022.
//

#include "Appliance.h"

class DishWasher : public Appliance{
private:
    double washingCycleLength;
    double consumedEnergyForOneHour;
public:
    DishWasher();
    DishWasher(const std::string &inputId, double inputWeight, double inputCycleLength, double inputConsumedElectricity);
    ~DishWasher();

    double consumedEnergy() override;
    std::string toString() override;
};

