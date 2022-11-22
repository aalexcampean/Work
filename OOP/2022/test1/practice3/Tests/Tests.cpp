//
// Created by Alex Campean on 06.04.2022.
//

#include "Tests.h"
#include "../Service/Service.h"

void testAll() {
    testAddRepository();
    testAddService();
    testTotalDurationTasksWithPriorityLessThan();
}

void testAddRepository() {
    Repository repository;
    assert(repository.getRepositorySize() == 0);

    Task task1("Solve_OOP_assignment", 120, 1);
    repository.addTaskRepository(task1);
    assert(repository.getRepositorySize() == 1);

    Task task2("Respond_to_emails", 45, 2);
    repository.addTaskRepository(task2);
    assert(repository.getRepositorySize() == 2);

    Task task3("Respond_to_emails", 50, 1);
    try {
        repository.addTaskRepository(task3);
    } catch (std::string error) {
//        std::cout << error;
    }
    assert(repository.getRepositorySize() == 2);
}

void testAddService() {
    Service service;
    assert(service.getServiceSize() == 0);

    service.firstEntries();
    assert(service.getServiceSize() == 5);
}

void testTotalDurationTasksWithPriorityLessThan() {
    Service service;
    service.firstEntries();
    int totalPriority = service.computeDurationForTasksWithPriorityLessThan("2");
    assert(totalPriority == 360);
}
