//
// Created by Alex Campean on 03.04.2022.
//

#include "AdminService.h"

AdminService::AdminService(): BaseService(new AdminRepository) {
}

AdminService::AdminService(BaseRepository* repository): BaseService(repository) {
}

AdminService::AdminService(const AdminService &service): BaseService(service) {
}

AdminService::~AdminService() {
}

int AdminService::copyDatabase(Dog *databaseCopy, const std::string &desiredBreed, double desiredAge) {
    return this->repository->copyDatabase(databaseCopy, desiredBreed, desiredAge);
}

void AdminService::updateElementService(const std::string &breed, const std::string &name, double age,
                                        const std::string &image) {
    Dog designatedDog(breed, name, age, image);
    this->repository->updateElementAdminRepo(designatedDog);
}

void AdminService::firstDogs() {
    this->addElementService("Golden Retriever", "Max", 3, "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    this->addElementService("French Bulldog", "Elysees", 1, "https://pbs.twimg.com/media/FKGTAuAUcAEBXGZ.jpg");
    this->addElementService("German Shepherd", "Lola", 5, "https://www.akc.org/wp-content/uploads/2016/06/German-Shepherd-Dog-laying-down-in-the-backyard.jpeg");
    this->addElementService("Doberman", "Abel", 2.6, "https://www.petplace.com/static/d4eb1d31d9e22d830a0097e3e8dcdf3d/98569/AdobeStock_142438416.jpg");
    this->addElementService("Chow Chow", "Michael", 1, "https://familist.ro/wp-content/uploads/2011/10/Chow-Chow-c%C3%A2inele-cu-liba-albastr%C4%83.jpg");
    this->addElementService("Akita Inu", "Norra", 2, "https://i.pinimg.com/550x/6f/ce/bd/6fcebd437c9a93d111174c4a29819d2c.jpg");
    this->addElementService("Corgi", "Sir", 1.3, "https://cdn.buttercms.com/ZF8K2t8hT8OoNR3W42bX");
    this->addElementService("Dalmatian", "George", 2.6, "https://img.a1.ro/0/2011/7/7/47440/138355386687ac9383.jpg");
    this->addElementService("Hound", "Alfred", 4, "https://imagesvc.meredithcorp.io/v3/mm/image?url=https%3A%2F%2Fstatic.onecms.io%2Fwp-content%2Fuploads%2Fsites%2F47%2F2020%2F10%2F26%2Fbloodhound-WL002292-2000.jpg");
    this->addElementService("Shitzu", "Tobby", 3, "https://i.pinimg.com/474x/99/a6/b6/99a6b6b52a81dfa3f9ccb396fe51da54.jpg");
    this->addElementService("Chiwawa", "Pedro", 1.7, "https://cdn.pixabay.com/photo/2016/04/27/14/05/chihuahua-1356693_1280.jpg");
}
