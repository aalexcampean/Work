//
// Created by Alex Campean on 03.04.2022.
//

#include "BaseService.h"

BaseService::BaseService(BaseRepository* repository) {
    this->repository = repository;
}

BaseService::BaseService(const BaseService &service) {
    this->repository = service.repository;
}

BaseService::~BaseService() {
}

BaseService &BaseService::operator=(const BaseService &service) {
    this->repository = service.repository;
    return *this;
}

Dog& BaseService::operator[](int index) {
    return this->repository->operator[](index);
}

int BaseService::getServiceLength() const {
    return this->repository->getRepoLength();
}

int BaseService::getServiceCapacity() const {
    return this->repository->getRepoCapacity();
}

void BaseService::addElementService(const std::string &breed, const std::string &name, double age, const std::string &image) {
    Dog designatedDog(breed, name, age, image);
    this->repository->addElementRepo(designatedDog);
}

void BaseService::deleteElementService(const std::string &image) {
    this->repository->deleteElementRepo(image);
}
