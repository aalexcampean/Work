//
// Created by Alex Campean on 06.04.2022.
//

#pragma once
#include <string>
#include <iostream>

class Task {
private:
    std::string description;
    int duration;
    int priority;
public:
    Task();
    Task(const std::string &inputDescription, int inputDuration, int inputPriority);
    ~Task();

    /// Getters
    std::string getDescription() const;
    int getDuration() const;
    int getPriority() const;

    /// Operator Overload
    bool operator<(const Task &task) const;
    bool operator==(const Task &task) const;
    Task& operator=(const Task &task);
    friend std::ostream& operator<<(std::ostream& out, const Task& task);
};
inline std::ostream& operator<<(std::ostream& out, const Task& task) {
    out << task.description << " | ";
    out << task.duration << " | ";
    out << task.priority;
    return out;
}