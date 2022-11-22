//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <vector>
#include "../Domain/Task.h"
#include "../Observer.h"

class TaskRepo : public Subject {
private:
    std::vector<Task> tasks;
    std::string fileName;

    void load();
    void save();
public:
    TaskRepo(const std::string &filename = "Tasks.txt");
    ~TaskRepo(){};

    int getLength();
    std::vector<Task> getAll() const;
    void addTask(const Task &task);
    void deleteTask(int id);
    void startTask(int id, int programmerId);
    void closeTask(int id);

    Task& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const TaskRepo &repository);

};

inline std::ostream& operator<<(std::ostream& stream, const TaskRepo &repository) {
    for (auto& it : repository.getAll()) {
        stream << it << "\n";
    }
    return stream;
}
