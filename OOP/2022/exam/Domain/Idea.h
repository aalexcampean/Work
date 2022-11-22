//
// Created by Alex Campean on 11.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <ostream>

class Idea {
private:
    int id;
    static int currentId;

    std::string description;
    std::string status;
    std::string creator;
    int act;
public:
    Idea(){};
    Idea(const std::string &description, const std::string &creator, int act);
    ~Idea(){};

    int getId() const;

    int getAct() const;
    void setAct(int act);

    const std::string &getDescription() const;
    void setDescription(const std::string &description);

    const std::string &getStatus() const;
    void setStatus(const std::string &status);

    const std::string &getCreator() const;
    void setCreator(const std::string &creator);

    std::string toString();

    bool operator==(Idea &idea) const;
    bool operator==(int inputId) const;
    friend std::ostream &operator<<(std::ostream &os, const Idea &idea);
    friend std::istream& operator>>(std::istream& in, Idea &idea);
};

inline std::ostream &operator<<(std::ostream &os, const Idea &idea) {
    os << idea.id << "," << idea.description << "," << idea.status << "," << idea.creator << "," << idea.act;

    return os;
}

inline std::istream &operator>>(std::istream &in, Idea &idea) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 5; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    idea.id = std::stoi(fields[0]);
    idea.description = fields[1];
    idea.status = fields[2];
    idea.creator = fields[3];
    idea.act = std::stoi(fields[4]);
    return in;
}