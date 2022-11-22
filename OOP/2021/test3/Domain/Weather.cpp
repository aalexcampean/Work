#include <string>
#include "Weather.h"

Weather::Weather() {
    this->startHour = 0;
    this->endHour = 0;
    this->precipitation = 0;
    this->description = "";
}

Weather::Weather(int givenStartHour, int givenEndHour, int givenPrecipitation, std::string givenDescription) {
    this->startHour = givenStartHour;
    this->endHour = givenEndHour;
    this->precipitation = givenPrecipitation;
    this->description = givenDescription;
}

Weather::~Weather() {

}

int Weather::getStartHour() const {
    return this->startHour;
}

int Weather::getEndHour() const {
    return this->endHour;
}

int Weather::getPrecipitation() const {
    return this->precipitation;
}

std::string Weather::getDescription() const {
    return this->description;
}

bool Weather::operator==(const Weather &w) const {
    if (this->startHour == w.startHour && this->endHour == w.endHour && this->precipitation == w.precipitation && this->description == w.description)
        return true;
    return false;
}

bool Weather::operator<(const Weather& w) const {
    if (this->startHour < w.startHour && this->endHour < w.endHour)
        return true;
    return false;
}

std::string Weather::toString() {
    std::string string_representation = "";

    string_representation += "Start Hour: " + std::to_string(this->startHour) + "  |  ";
    string_representation += "End Hour: " + std::to_string(this->endHour) + "  |  ";
    string_representation += "Precipitation Probability: " + std::to_string(this->precipitation) + "  |  ";
    string_representation += "Description: " + this->description;
    string_representation += "\n";

    return string_representation;
}

