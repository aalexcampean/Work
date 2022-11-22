//
// Created by Alex Campean on 03.04.2022.
//

#include "InMemoryRepository.h"
#include "../../Exception/CustomException.h"

/// Constructors, Destructor
InMemoryRepository::InMemoryRepository() {
    std::vector<Dog> designated_da;
    this->dogs = designated_da;
}

InMemoryRepository::InMemoryRepository(const InMemoryRepository &mr) {
    this->dogs = mr.dogs;
}

InMemoryRepository::~InMemoryRepository() {
}

/// Getters
int InMemoryRepository::getRepoLength() const {
    return this->dogs.size();
}

std::vector<Dog> InMemoryRepository::getDogs() const {
    return this->dogs;
}

Dog &InMemoryRepository::getDogByImage(const std::string &image) {
    auto it = std::find(this->dogs.begin(), this->dogs.end(), image);
    return *it;
}

/// Add, Delete, Update
void InMemoryRepository::addElementRepo(const Dog &dog) {
    auto it = std::find(this->dogs.begin(), this->dogs.end(), dog);
    if (it != this->dogs.end()) {
        throw CustomException(ExceptionTypes::AddException);
    }
    this->dogs.push_back(dog);
    this->save();
}

void InMemoryRepository::deleteElementRepo(const std::string& image) {
    auto it = std::find(this->dogs.begin(), this->dogs.end(), image);
    if (it == this->dogs.end()) {
        throw CustomException(ExceptionTypes::DeleteException);
    }

    this->dogs.erase(it);
    this->save();
}

void InMemoryRepository::updateElementAdminRepo(const Dog &dog) {
    auto it = std::find(this->dogs.begin(), this->dogs.end(), dog);
    if (it == this->dogs.end()) {
        throw CustomException(ExceptionTypes::UpdateException);
    }
    *it = dog;
    this->save();
}

/// Operators Overload
InMemoryRepository &InMemoryRepository::operator=(const InMemoryRepository& repository) {
    this->dogs = repository.dogs;
    return *this;
}

Dog &InMemoryRepository::operator[](int index) {
    return this->dogs[index];
}
