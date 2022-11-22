//
// Created by Alex Campean on 11.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <ostream>

class Writer {
private:
    int id;
    static int currentId;

    std::string name;
    std::string expertise;
public:
    Writer(){};
    Writer(const std::string &name, const std::string &expertise);
    ~Writer(){};

    int getId() const;

    const std::string &getName() const;
    void setName(const std::string &name);

    const std::string &getExpertise() const;
    void setExpertise(const std::string &expertise);

    std::string toString();

    bool operator==(const Writer &writer) const;
    friend std::ostream &operator<<(std::ostream &os, const Writer &writer);
    friend std::istream& operator>>(std::istream& in, Writer &writer);
};

inline std::ostream &operator<<(std::ostream &os, const Writer &writer) {
    os << writer.id << "," << writer.name << "," << writer.expertise;

    return os;
}

inline std::istream &operator>>(std::istream &in, Writer &writer) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 3; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    writer.id = std::stoi(fields[0]);
    writer.name = fields[1];
    writer.expertise = fields[2];
    return in;
}

