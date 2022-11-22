//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <string>
#include <vector>
#include <ostream>

class Task {
private:
    int id;
    static int current_id;

    std::string description;
    std::string status;
    int programmerId;
public:
    Task(){};
    Task(const std::string &description);
    ~Task(){};

    int getId() const;

    const std::string &getDescription() const;
    void setDescription(const std::string &description);

    const std::string &getStatus() const;
    void setStatus(const std::string &status);

    int getProgrammerId() const;
    void setProgrammerId(int programmerId);

    std::string toString() const;

    bool operator==(const Task &task) const;
    bool operator==(int inputId) const;
    friend std::ostream &operator<<(std::ostream &os, const Task &task);
    friend std::istream& operator>>(std::istream& in, Task &task);
};

inline std::ostream &operator<<(std::ostream &os, const Task &task) {
    os << task.id << "," << task.description << "," << task.status;
    if (task.status == "in progress" || task.status == "closed") {
        os << "," << task.programmerId;
    }

    return os;
}

inline std::istream &operator>>(std::istream &in, Task &task) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 3; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    task.id = std::stoi(fields[0]);
    task.description = fields[1];
    task.status = fields[2];
    task.programmerId = 0;

    if (fields[2] == "in progress" || fields[2] == "closed") {
        std::getline(in, field, ',');
        fields.push_back(field);
        task.programmerId = std::stoi(fields[3]);
    }

    return in;
}