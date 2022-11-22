//
// Created by Alex Campean on 06.04.2022.
//

#include "Service.h"

Service::Service() {
    this->repository = new Repository;
}

Service::Service(Repository *inputRepository) {
    this->repository = inputRepository;
}

Service::~Service() {
}

int Service::getServiceSize() const {
    return this->repository->getRepositorySize();
}

std::vector<Task> Service::getAllTasksSortedDescendingByPriority() const {
    std::vector<Task> allTasks = this->repository->getAllTasks();
    std::sort(allTasks.begin(), allTasks.end());
    std::reverse(allTasks.begin(), allTasks.end());
    return allTasks;
}

std::vector<Task> Service::getAllTasksWithPriorityLessThan(int inputPriority) const {
    std::vector<Task> allTasks = this->repository->getAllTasks();
    std::vector<Task> tasksWithPriorityLessThan;
    std::copy_if(allTasks.begin(), allTasks.end(), std::back_inserter(tasksWithPriorityLessThan), [&inputPriority](auto &it){
        return it.getPriority() < inputPriority;
    });
    return tasksWithPriorityLessThan;
}

void Service::addTaskService(const std::string &inputDescription, const std::string &inputDuration, const std::string &inputPriority) {
    if (inputDescription.empty()) {
        throw std::string("Invalid empty description");
    }
    size_t pos1;
    int validDuration = std::stoi(inputDuration, &pos1);
    size_t pos2;
    int validPriority = std::stoi(inputPriority, &pos2);

    Task inputTask(inputDescription, validDuration, validPriority);
    this->repository->addTaskRepository(inputTask);
}

int Service::computeDurationForTasksWithPriorityLessThan(const std::string &inputPriority) const {
    size_t pos2;
    int validPriority = std::stoi(inputPriority, &pos2);

    std::vector<Task> tasksWithPriorityLessThan = this->getAllTasksWithPriorityLessThan(validPriority);
    int totalDuration = 0;
    std::for_each(tasksWithPriorityLessThan.begin(), tasksWithPriorityLessThan.end(), [&totalDuration](auto &it){
        totalDuration += it.getDuration();
    });
    return totalDuration;
}

void Service::firstEntries() {
    this->addTaskService("Solve_OOP_assignment", "120", "1");
    this->addTaskService("Respond_to_emails", "45", "2");
    this->addTaskService("Eat_sushi", "30", "3");
    this->addTaskService("Visit_parents", "240", "1");
    this->addTaskService("Buy_a_jacket", "120", "2");
}
