//
// Created by Alex Campean on 03.04.2022.
//

#include "AdminRepository.h"

/// Constructors, Destructor
AdminRepository::AdminRepository() {
}

AdminRepository::AdminRepository(const AdminRepository &repository): BaseRepository(repository) {
}

AdminRepository::~AdminRepository() {
}

/// Copy Database
int AdminRepository::copyDatabase(Dog* databaseCopy, const std::string &desiredBreed, double desiredAge){
    int index = 0;
    if (desiredBreed.empty()){
        for (int i = 0; i < this->da.getLength(); i++){
            databaseCopy[index] = this->da[i];
            index += 1;
        }
    }
    else {
        for (int i = 0; i < this->da.getLength(); i++) {
            if (this->da[i].getBreed().find(desiredBreed) != std::string::npos) {
                if (this->da[i].getAge() < desiredAge) {
                    databaseCopy[index] = this->da[i];
                    index += 1;
                }
            }
        }
    }
    return index;
}

/// Update
void AdminRepository::updateElementAdminRepo(Dog &dog) {
    int index = this->da.getIndex(dog.getImage());
    if (index == -1){
        throw std::string("Dog does not exist");
    }

    this->da.updateElement(dog);
}
