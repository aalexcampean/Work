//
// Created by Alex Campean on 03.04.2022.
//

#include "AdminService.h"
#include "../Domain/Validator/DogValidator.h"

AdminService::AdminService(TextFileRepository* repository): UserService(repository) {
}

AdminService::AdminService(const AdminService &service): UserService(service) {
}

AdminService::~AdminService() {
}

TextFileRepository *AdminService::getRepoState() {
    return this->repository;
}

std::vector<Dog> AdminService::filterByBreedAndAge(const std::string &inputBreed, double inputAge) {
    std::vector<Dog> allDogs = this->repository->getDogs();
    if (inputBreed.empty()) {
        return allDogs;
    }
    std::vector<Dog> filteredDogs;
    std::copy_if(allDogs.begin(), allDogs.end(), std::back_inserter(filteredDogs), [&inputBreed, inputAge](auto &it){
        return it.getBreed() == inputBreed && it.getAge() == inputAge;
    });
    return filteredDogs;
}

void AdminService::updateElementService(const std::string &breed, const std::string &name, std::string age,
                                        const std::string &image) {
    DogValidator::validateDog(breed, name, age, image);

    size_t pos2;
    double validatedAge = std::stod(age, &pos2);

    Dog designatedDog(breed, name, validatedAge, image);
    this->repository->updateElementAdminRepo(designatedDog);
}
