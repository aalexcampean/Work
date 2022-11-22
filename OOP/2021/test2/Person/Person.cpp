#include "Person.h"
#include "../Exception/CustomException.h"
#include "BMI.h"
#include "BP.h"

std::string Person::getName() const {
    return this->name;
}

std::vector<Measurement*> Person::getAllMeasurements() const {
    return this->measurements;
}

std::vector<Measurement*> Person::getMeasurementByMonth(int given_month) {
    std::vector<Measurement*> measurements_this_month;
    for (auto it : this->measurements) {
        std::vector<std::string> measurement_date = this->splitDate(it->getDate(), "/");
        if (std::stoi(measurement_date[1]) == given_month) {
            measurements_this_month.push_back(it);
        }
    }
    return measurements_this_month;
}

std::vector<Measurement*> Person::getMeasurementsNewerThan(std::string given_date){
    std::vector<Measurement*> measurements_newer_than;
    for (auto it : this->measurements) {
        std::vector<std::string> measurement_date = this->splitDate(it->getDate(), "/");
        std::vector<std::string> given = this->splitDate(given_date, "/");
        if ((measurement_date[1] > given[1]) || ((measurement_date[1] == given[1]) && (measurement_date[0] > given[0]))) {
            measurements_newer_than.push_back(it);
        }
    }
    return measurements_newer_than;
}

void Person::addMeasurements(Measurement *m) {
    auto it = find(this->measurements.begin(), this->measurements.end(), m);
    if (it != this->measurements.end()) {
        throw CustomException(0002, "Movie already exists");
    }
    this->measurements.push_back(m);
}

bool Person::isHealthy(int given_month) {
    std::vector<Measurement*> measurements_this_month;
    for (auto it : this->measurements) {
        std::vector<std::string> measurement_date = this->splitDate(it->getDate(), "/");
        if (std::stoi(measurement_date[1]) == given_month) {
            if (!it->isNormalValue()) {
                return false;
            }
        }
    }
    return true;
}

void Person::writeToFile(std::string filename, std::string date) {

}

std::vector<std::string> Person::splitDate(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void Person::addFirstMeasurements() {
    Measurement* m = new BMI{ "22/4/2021", 19.4};
    Measurement* m1 = new BMI{ "12/4/2021", 25.6 };
    Measurement* m2 = new BMI{ "02/02/2021", 23.4 };
    Measurement* m3 = new BP{ "12/02/2021", 100, 70 };
    Measurement* m4 = new BP{ "22/05/2021", 100, 89 };
    this->addMeasurements(m);
    this->addMeasurements(m1);
    this->addMeasurements(m2);
    this->addMeasurements(m3);
    this->addMeasurements(m4);
}
//vector<string> v = split (str, delimiter);
