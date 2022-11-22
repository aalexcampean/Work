//
// Created by Alex Campean on 10.06.2022.
//

#include "Task.h"

Task::Task(const std::string &description) : id(current_id++),
                                             description(description) {
    status = "open";
    programmerId = 0;
}

int Task::getId() const {
    return id;
}

const std::string &Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string &description) {
    Task::description = description;
}

const std::string &Task::getStatus() const {
    return status;
}

void Task::setStatus(const std::string &status) {
    Task::status = status;
}

int Task::getProgrammerId() const {
    return programmerId;
}

void Task::setProgrammerId(int programmerId) {
    Task::programmerId = programmerId;
}

bool Task::operator==(const Task &task) const {
    return id == task.id;
}

bool Task::operator==(int inputId) const {
    return id == inputId;
}

std::string Task::toString() const {
    std::string stringRepresentation = "ID: " + std::to_string(id) + " -  Description: " + description + " -  Status: " + status;
    if (status == "in progress" || status == "closed") {
        stringRepresentation += " -  Programmer ID: " + std::to_string(programmerId);
    }
    return stringRepresentation;
}
