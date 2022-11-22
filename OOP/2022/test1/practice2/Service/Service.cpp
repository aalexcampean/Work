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

int Service::getServiceLength() const {
    return this->repository->getRepositoryLength();
}

std::vector<Project> Service::getAllProjectsService() const {
    return this->repository->getAllProjects();
}

std::vector<Project> Service::getAllProjectsSortedDecreasingByDate() const {
    std::vector<Project> allProjects = this->repository->getAllProjects();
    std::sort(allProjects.begin(), allProjects.end());
//    reverse(allProjects.begin(), allProjects.end());
    return allProjects;
}

std::vector<Project> Service::getAllFinishedProjects() const {
    std::vector<Project> allProjects = this->repository->getAllProjects();
    std::vector<Project> finishedProjects;
    std::copy_if(allProjects.begin(), allProjects.end(), std::back_inserter(finishedProjects), [](auto &it){
        return it.getIsDone();
    });
    return finishedProjects;
}

void
Service::addProjectService(const std::string &inputName, const std::string &inputCustomer, int inputDay, int inputMonth,
                           int inputYear, double inputCost, bool inputIsDone) {
    Date inputDate(inputDay, inputMonth, inputYear);
    Project inputProject(inputName, inputCustomer, inputDate, inputCost, inputIsDone);
    this->repository->addProjectRepository(inputProject);
}

double Service::computeTotalCostForFinishedProjects() {
    std::vector<Project> finishedProjects = this->getAllFinishedProjects();
    double finalSum;
    std::for_each(finishedProjects.begin(), finishedProjects.end(), [&finalSum](auto &it){
        finalSum += it.getCost();
    });
    return finalSum;
}

void Service::addInitialEntries() {
    this->addProjectService("Stairs", "Flin", 20, 8, 2018, 18, true);
    this->addProjectService("Website", "Spitalul Judetean Cluj", 6, 1, 2017, 122, true);
    this->addProjectService("Data Archiving", "Spitalul Judetean Cluj", 6, 6, 2020, 200, true);
    this->addProjectService("Website", "Valuations", 1, 9, 2018, 2.3, true);
}

