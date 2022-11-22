//
// Created by Alex Campean on 06.04.2022.
//

#include "../Repository/Repository.h"

class Service {
private:
    Repository *repository;
public:
    Service();
    Service(Repository *inputRepository);
    ~Service();

    /// Getters
    int getServiceLength() const;
    std::vector<Project> getAllProjectsService() const;
    std::vector<Project> getAllProjectsSortedDecreasingByDate() const;
    std::vector<Project> getAllFinishedProjects() const;

    /// Add Project
    void addProjectService(const std::string &inputName, const std::string &inputCustomer, int inputDay, int inputMonth, int inputYear, double inputCost, bool inputIsDone);

    /// Find Total Finished Projects Cost
    double computeTotalCostForFinishedProjects();

    /// Initial Entries
    void addInitialEntries();
};


