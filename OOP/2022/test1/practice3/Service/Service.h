//
// Created by Alex Campean on 06.04.2022.
//

#pragma once
#include "../Repository/Repository.h"

class Service {
private:
    Repository *repository;
public:
    Service();
    Service(Repository * inputRepository);
    ~Service();

    /// Getters
    int getServiceSize() const;
    std::vector<Task> getAllTasksSortedDescendingByPriority() const;
    std::vector<Task> getAllTasksWithPriorityLessThan(int inputPriority) const;

    /// Add Task
    void addTaskService(const std::string &inputDescription, const std::string &inputDuration, const std::string &inputPriority);

    /// Compute Total Duration for Tasks with duration less than
    int computeDurationForTasksWithPriorityLessThan(const std::string &inputPriority) const;

    /// Add First Entries
    void firstEntries();
};


