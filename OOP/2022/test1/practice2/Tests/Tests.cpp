//
// Created by Alex Campean on 06.04.2022.
//

#include "Tests.h"
#include "../Service/Service.h"

void testAll() {
    testAddRepository();
    testAddService();

    testSortAllProjects();
    testComputedCostOfFinishedProjects();
}

void testAddRepository() {
    Repository repository;
    assert(repository.getRepositoryLength() == 0);

    Date date1(20, 8, 2018);
    Project project1("Stairs", "Flin", date1, 18, false);
    repository.addProjectRepository(project1);
    assert(repository.getRepositoryLength() == 1);


    Date date2(6, 1, 2017);
    Project project2("Website", "Spitalul Judetean Cluj", date2, 122, true);
    repository.addProjectRepository(project2);
    assert(repository.getRepositoryLength() == 2);

    Date date3(10, 5, 2016);
    Project project3("Website", "Spitalul Judetean Cluj", date3, 144, false);
    try {
        repository.addProjectRepository(project3);
    } catch (std::string error) {
//        std::cout << error;
    }
    assert(repository.getRepositoryLength() == 2);
}

void testAddService() {
    Service service;
    assert(service.getServiceLength() == 0);

    service.addProjectService("Stairs", "Flin", 20, 8, 2018, 18, false);
    assert(service.getServiceLength() == 1);
    service.addProjectService("Website", "Spitalul Judetean Cluj", 6, 1, 2017, 122, true);
    assert(service.getServiceLength() == 2);

    try {
        service.addProjectService("Website", "Spitalul Judetean Cluj", 10, 5, 2016, 144, false);
    } catch (std::string error) {
//        std::cout << error;
    }
    assert(service.getServiceLength() == 2);
}

void testComputedCostOfFinishedProjects() {
    Service service;
    service.addInitialEntries();
    assert(service.getServiceLength() == 4);

    double finalCost = service.computeTotalCostForFinishedProjects();
    assert(finalCost == 342.3);
}

void testSortAllProjects() {
    Service service;
    service.addInitialEntries();
    assert(service.getServiceLength() == 4);

    std::vector<Project> sortedProjects = service.getAllProjectsSortedDecreasingByDate();

    Date firstDate(6, 1, 2017);
    Project firstProject("Website", "Spitalul Judetean Cluj", firstDate, 122, true);
    assert(sortedProjects[0] == firstProject);

    Date lastDate(6, 6, 2020);
    Project lastProject("Data Archiving", "Spitalul Judetean Cluj", lastDate, 200, true);
    assert(sortedProjects[3] == lastProject);
}
