#include "UserRepo.h"
#include <string>

// Constructor, Destructor

UserRepository::UserRepository(){
    DynamicArray<Movie> designated_da;
    this->da = designated_da;
}

UserRepository::UserRepository(const UserRepository &mr){
    this->da = mr.da;
}

UserRepository::~UserRepository() {
}

// Operators Overload

UserRepository& UserRepository::operator=(const UserRepository &mr){
    this->da = mr.da;
    return *this;
}

Movie& UserRepository::operator[](int index){
    return this->da[index];
}

// Getter

int UserRepository::getUserRepoLength() const{
    return this->da.getLength();
}

int UserRepository::getUserRepoCapacity() const{
    return this->da.getCapacity();
}

// Add, Delete, Update

void UserRepository::addElementUserRepo(Movie &m) {
    if (this->da.getIndex(m.getTitle()) != -1){
        throw std::string("Movie already exists");
    }

    this->da.addElement(m);
}

void UserRepository::deleteElementUserRepo(const std::string &title) {
    int index = this->da.getIndex(title);
    if (index == -1){
        throw std::string("Movie does not exist");
    }

    this->da.deleteElement(index);
}


