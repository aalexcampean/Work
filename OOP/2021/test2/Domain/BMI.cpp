#include "BMI.h"

double BMI::getValue() {
    return this->value;
}

bool BMI::isNormalValue() {
    if (this->value < 18.5 || this->value > 25) {
        return false;
    }
    return true;
}

std::string BMI::toString() {
    std::string string_representation = "--- BMI   ---   ";
    string_representation += "DATE: " + this->date + "  |  ";
    string_representation += "VALUE: " + std::to_string(this->value);

    return string_representation;
}
