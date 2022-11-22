#pragma once
#include <string>
#include <iostream>
#include <vector>

class Weather {
private:
    int startHour;
    int endHour;
    int precipitation;
    std::string description;

public:
    Weather();
    Weather(int, int, int, std::string);
    ~Weather();

    // getters
    int getStartHour() const;
    int getEndHour() const;
    int getPrecipitation() const;
    std::string getDescription() const;

    // Operators Overload
    bool operator==(const Weather&) const;
    bool operator<(const Weather&) const;
    friend std::ostream& operator<<(std::ostream&, const Weather&);
    friend std::istream& operator>>(std::istream&, Weather&);

    // string representation
    std::string toString();
};

inline std::ostream& operator<<(std::ostream& out, const Weather& w) {
    out << w.startHour << ";";
    out << w.endHour << ";";
    out << w.precipitation << ";";
    out << w.description;
    return out;
}

inline std::istream& operator>>(std::istream& in, Weather& w) {
    std::vector<std::string> fields;
    std::string field;
    for (int i = 0; i < 5; i++) {
        std::getline(in, field, ';');
        fields.push_back(field);
    }

    w.startHour = std::stoi(fields[0]);
    w.endHour = std::stoi(fields[1]);
    w.precipitation = std::stoi(fields[2]);
    w.description = fields[3];
    return in;
}


