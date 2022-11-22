#pragma once
#include "Measurement.h"

class BMI : public Measurement{
private:
    double value;

public:
    BMI(){};
    BMI(std::string given_date, double given_value) : Measurement{given_date}, value(given_value){};
    ~BMI(){};

    double getValue();
    bool isNormalValue()override;
    std::string toString()override;

};
