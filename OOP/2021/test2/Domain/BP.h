#pragma once
#include "Measurement.h"

class BP : public Measurement{
private:
    int systolicValue;
    int diastolicValue;

public:
    BP(){};
    BP(std::string given_date, int given_systolicValue, int given_diastolicValue) : Measurement{given_date}, systolicValue(given_systolicValue), diastolicValue(given_diastolicValue){};
    ~BP(){};

    int getSystolicValue();
    int getDiastolicValue();
    bool isNormalValue()override;
    std::string toString()override;
};
