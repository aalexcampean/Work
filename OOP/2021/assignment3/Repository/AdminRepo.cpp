#include "AdminRepo.h"
#include <string>

// Constructor, Destructor

AdminRepository::AdminRepository(){
    DynamicArray<Movie> designated_da;
    this->da = designated_da;
}

AdminRepository::AdminRepository(const AdminRepository &amr){
    this->da = amr.da;
}

AdminRepository::~AdminRepository() {
}

// Operators Overload

AdminRepository& AdminRepository::operator=(const AdminRepository &amr){
    this->da = amr.da;
    return *this;
}

Movie& AdminRepository::operator[](int index){
    return this->da[index];
}

// Getter

int AdminRepository::getAdminRepoLength() const{
    return this->da.getLength();
}

int AdminRepository::getAdminRepoCapacity() const{
    return this->da.getCapacity();
}

Movie& AdminRepository::getElementByUniqueField(const std::string &unique_field) {
    return this->da.getElementByUniqueField(unique_field);
}

// Copy Database

int AdminRepository::copyDatabase(Movie* database_copy, const std::string &desired_genre){
    int index = 0;

    if (desired_genre.empty()){
        for (int i = 0; i < this->da.getLength(); i++){
            database_copy[index] = this->da[i];
            index += 1;
        }
    }
    else {
        for (int i = 0; i < this->da.getLength(); i++) {
            if (this->da[i].getGenre().find(desired_genre) != std::string::npos) {
                database_copy[index] = this->da[i];
                index += 1;
            }
        }
    }
    return index;
}

// Add, Delete, Update

void AdminRepository::addElementAdminRepo(Movie &m) {
    if (this->da.getIndex(m.getTitle()) != -1){
        throw std::string("Movie already exists");
    }

    this->da.addElement(m);
}

void AdminRepository::deleteElementAdminRepo(const std::string &title) {
    int index = this->da.getIndex(title);
    if (index == -1){
        throw std::string("Movie does not exist");
    }

    this->da.deleteElement(index);
}

void AdminRepository::updateElementAdminRepo(Movie &m) {
    int index = this->da.getIndex(m.getTitle());
    if (index == -1){
        throw std::string("Movie does not exist");
    }

    this->da.updateElement(m, index);
}



