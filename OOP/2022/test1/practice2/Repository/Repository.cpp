//
// Created by Alex Campean on 06.04.2022.
//

#include "Repository.h"

Repository::Repository() {
}

Repository::~Repository() {
}

int Repository::getRepositoryLength() const {
    return this->projects.size();
}

std::vector<Project> Repository::getAllProjects() const {
    return this->projects;
}

void Repository::addProjectRepository(const Project &project) {
    auto it = std::find(this->projects.begin(), this->projects.end(), project);
    if (it != this->projects.end()) {
        throw std::string("Project already exists");
    }
    this->projects.push_back(project);
}

Project &Repository::operator[](int index) {
    return this->projects[index];
}
