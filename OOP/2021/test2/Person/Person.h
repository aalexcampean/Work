#pragma once
#include "../Domain/Measurement.h"
#include "vector"

class Person {
private:
    std::string name;
    std::vector<Measurement*> measurements;

public:
    Person(){};
    ~Person(){};

    std::string getName() const;
    std::vector<Measurement*> getAllMeasurements() const;
    std::vector<Measurement*> getMeasurementByMonth(int given_month);
    std::vector<Measurement*> getMeasurementsNewerThan(std::string given_date);

    void addMeasurements(Measurement* m);
    bool isHealthy(int given_month);
    std::vector<std::string> splitDate(std::string s, std::string delimiter);

    void writeToFile(std::string filename, std::string(date));
    void addFirstMeasurements();




};


