//
// Created by Alex Campean on 03.04.2022.
//

#include "UserService.h"

UserService::UserService(): BaseService(new UserRepository) {
}

UserService::UserService(BaseRepository *repository) : BaseService(repository) {
}

UserService::UserService(const UserService &service): BaseService(service) {
}

UserService::~UserService() {
}

int UserService::copyDatabase(Dog *databaseCopy, const std::string &desiredBreed, double desiredAge) {
    return 0;
}

void UserService::updateElementService(const std::string &breed, const std::string &name, double age,
                                       const std::string &image) {
}

void UserService::firstDogs() {
}
