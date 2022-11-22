//
// Created by Alex Campean on 03.04.2022.
//

#include "UserRepository.h"

UserRepository::UserRepository(): BaseRepository() {
}

UserRepository::UserRepository(const UserRepository &repository): BaseRepository(repository) {
}

UserRepository::~UserRepository() {
}

int UserRepository::copyDatabase(Dog *databaseCopy, const std::string &desiredBreed, double desiredAge) {
    return 0;
}

void UserRepository::updateElementAdminRepo(Dog &dog) {
}
