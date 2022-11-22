//
// Created by Alex Campean on 03.04.2022.
//

#include "BaseRepository.h"

/// Constructors, Destructor
BaseRepository::BaseRepository() {
    DynamicArray<Dog> designated_da;
    this->da = designated_da;
}

BaseRepository::BaseRepository(const BaseRepository &mr) {
    this->da = mr.da;
}

BaseRepository::~BaseRepository() {
}

/// Getters
size_t BaseRepository::getRepoLength() const {
    return this->da.getLength();
}

size_t BaseRepository::getRepoCapacity() const {
    return this->da.getCapacity();
}

/// Add, Delete, Update
void BaseRepository::addElementRepo(Dog &dog) {
    if (this->da.getIndex(dog) != -1){
        throw std::string("Dog already exists");
    }

    this->da.addElement(dog);
}

void BaseRepository::deleteElementRepo(const std::string& image) {
    int index = this->da.getIndex(image);
    if (index == -1){
        throw std::string("Dog does not exist");
    }

    this->da.deleteElement(index);
}

/// Operators Overload
BaseRepository &BaseRepository::operator=(const BaseRepository& repository) {
    this->da = repository.da;
    return *this;
}

Dog &BaseRepository::operator[](int index) {
    return this->da[index];
}
