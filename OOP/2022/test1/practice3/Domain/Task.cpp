//
// Created by Alex Campean on 06.04.2022.
//

#include "Task.h"


Task::Task() {
    this->description = "";
    this->duration = 0;
    this->priority = 0;
}

Task::Task(const std::string &inputDescription, int inputDuration, int inputPriority) {
    this->description = inputDescription;
    this->duration = inputDuration;
    this->priority = inputPriority;
}

Task::~Task() {
}

std::string Task::getDescription() const {
    return this->description;
}

int Task::getDuration() const {
    return this->duration;
}

int Task::getPriority() const {
    return this->priority;
}

bool Task::operator<(const Task &task) const {
    return this->priority < task.priority;
}

bool Task::operator==(const Task &task) const {
    return this->description == task.description;
}

Task &Task::operator=(const Task &task) {
    this->description = task.description;
    this->duration = task.duration;
    this->priority = task.priority;
    return *this;
}
