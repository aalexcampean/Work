#include "BP.h"
#include <string>

int BP::getSystolicValue() {
    return this->systolicValue;
}

int BP::getDiastolicValue() {
    return this->diastolicValue;
}

bool BP::isNormalValue() {
    if (this->systolicValue < 90 || this->systolicValue > 119) {
        return false;
    }

    if (this->diastolicValue < 60 || this->diastolicValue > 79) {
        return false;
    }
    return true;
}

std::string BP::toString() {
    std::string string_representation = "--- BP   ---   ";
    string_representation += "DATE: " + this->date + "  |  ";
    string_representation += "SYSTOLIC VALUE: " + std::to_string(this->systolicValue) + "  |  ";
    string_representation += "DIASTOLIC VALUE: " + std::to_string(this->diastolicValue);

    return string_representation;
}
