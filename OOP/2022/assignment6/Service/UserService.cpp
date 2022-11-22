//
// Created by Alex Campean on 03.04.2022.
//

#include "UserService.h"
#include "../Repository/CSV/CSVRepository.h"
#include "../Repository/HTML/HTMLRepository.h"
#include "../Domain/Validator/DogValidator.h"

UserService::UserService(TextFileRepository* repository) {
    this->repository = repository;
}

UserService::UserService(const UserService &service) {
    this->repository = service.repository;
}

UserService::~UserService() {
}

/// Set Repository Type
void UserService::setRepositoryType(const std::string& type) {
    if (type == "csv") {
        this->repository = new CSVRepository();
    }
    else if (type == "html") {
        this->repository = new HTMLRepository();
    }
    else {
    }
}

UserService &UserService::operator=(const UserService &service) {
    this->repository = service.repository;
    return *this;
}

Dog& UserService::operator[](int index) {
    return this->repository->operator[](index);
}

int UserService::getServiceLength() const {
    return this->repository->getRepoLength();
}

std::vector<Dog> UserService::getRepository() const {
    return this->repository->getDogs();
}

std::vector<Dog> UserService::filterByBreed(const std::string &inputBreed) {
    std::vector<Dog> allDogs = this->repository->getDogs();
    if (inputBreed.empty()) {
        return allDogs;
    }
    std::vector<Dog> filteredDogs;
    std::copy_if(allDogs.begin(), allDogs.end(), std::back_inserter(filteredDogs), [&inputBreed](auto &it){
        return it.getBreed() == inputBreed;
    });
    return filteredDogs;
}

void UserService::addElementService(const std::string &breed, const std::string &name, std::string age, const std::string &image) {
    DogValidator::validateDog(breed, name, age, image);

    size_t pos2;
    double validatedAge = std::stod(age, &pos2);

    Dog designatedDog(breed, name, validatedAge, image);
    this->repository->addElementRepo(designatedDog);
}

void UserService::deleteElementService(const std::string &image) {
    DogValidator::validateImage(image);
    this->repository->deleteElementRepo(image);
}

Dog &UserService::getDogByImage(const std::string &image) {
    return this->repository->getDogByImage(image);
}

void UserService::openFile() {
    this->repository->openFile();
}
