//
// Created by Alex Campean on 10.06.2022.
//

#include "TaskRepo.h"
#include "../Exception/CustomException.h"

#include <iostream>
#include <fstream>
#include <sstream>


TaskRepo::TaskRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

void TaskRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Task task;
        if (!(iss >> task)) { break; } // error

        tasks.push_back(task);
    }
}

void TaskRepo::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}

int TaskRepo::getLength() {
    return tasks.size();
}

std::vector<Task> TaskRepo::getAll() const {
    return tasks;
}

void TaskRepo::addTask(const Task &task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        throw CustomException(ExceptionTypes::AddException);
    }
    tasks.push_back(task);
    this->save();
    this->notify();
}

void TaskRepo::deleteTask(int id) {
    auto it = std::find(tasks.begin(), tasks.end(), id);
    if (it == tasks.end()) {
        throw CustomException(ExceptionTypes::DeleteException);
    }

    tasks.erase(it);
    this->save();
    this->notify();
}

void TaskRepo::startTask(int id, int programmerId) {
    auto it = std::find(tasks.begin(), tasks.end(), id);
    if (it == tasks.end()) {
        throw CustomException(ExceptionTypes::DeleteException);
    }
    it->setStatus("in progress");
    it->setProgrammerId(programmerId);
    this->save();
    this->notify();
}

void TaskRepo::closeTask(int id) {
    auto it = std::find(tasks.begin(), tasks.end(), id);
    if (it == tasks.end()) {
        throw CustomException(ExceptionTypes::DeleteException);
    }
    it->setStatus("closed");
    this->save();
    this->notify();
}

Task &TaskRepo::operator[](int index) {
    return tasks[index];
}
