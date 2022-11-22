//
// Created by Alex Campean on 06.04.2022.
//

#pragma once
#include "../Domain/Task.h"
#include <vector>

class Repository {
private:
    std::vector<Task> tasks;
public:
    Repository();
    ~Repository();

    /// Getters
    int getRepositorySize() const;
    std::vector<Task> getAllTasks() const;

    /// Add Task
    void addTaskRepository(const Task &task);

    /// Operator Overload
    Task& operator[](int index);
};


