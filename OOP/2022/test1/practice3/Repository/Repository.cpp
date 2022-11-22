//
// Created by Alex Campean on 06.04.2022.
//

#include "Repository.h"

Repository::Repository() {
}

Repository::~Repository() {
}

int Repository::getRepositorySize() const {
    return this->tasks.size();
}

std::vector<Task> Repository::getAllTasks() const {
    return this->tasks;
}

void Repository::addTaskRepository(const Task &task) {
    auto it = std::find(this->tasks.begin(), this->tasks.end(), task);
    if (it != this->tasks.end()) {
        throw std::string("Task already exists");
    }
    this->tasks.push_back(task);
}

Task &Repository::operator[](int index) {
    return this->tasks[index];
}
