#pragma once
#include <string>

class Measurement {
protected:
    std::string date;

public:
    Measurement(){};
    Measurement(std::string given_date) : date(given_date) {};
    ~Measurement(){};

    std::string getDate();
    virtual bool isNormalValue()=0;
    virtual std::string toString()=0;
};


