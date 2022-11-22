#include "UserService.h"

// Constructor, Destructor

UserService::UserService() {
    UserRepository designated_repo;
    this->repo = designated_repo;
}

UserService::UserService(const UserService &ums) {
    this->repo = ums.repo;
}

UserService::~UserService() {
}

// Operators Overload

UserService& UserService::operator=(const UserService &ums) {
    this->repo = ums.repo;
    return *this;
}

Movie& UserService::operator[](int index) {
    return this->repo[index];
}

// Getters

int UserService::getUserServiceLength() const {
    return this->repo.getUserRepoLength();
}

int UserService::getUserServiceCapacity() const {
    return this->repo.getUserRepoCapacity();
}

// Add, Delete, Update

void UserService::addElementUserService(const std::string &title, const std::string &genre, int year_of_release, int nr_of_likes, const std::string &trailer) {
    Movie designated_movie(title, genre, year_of_release, nr_of_likes, trailer);
    this->repo.addElementUserRepo(designated_movie);
}

void UserService::deleteElementUserService(const std::string &title) {
    this->repo.deleteElementUserRepo(title);
}
