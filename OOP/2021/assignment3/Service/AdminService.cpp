#include "AdminService.h"

// Constructor, Destructor

AdminService::AdminService() {
    AdminRepository designated_repo;
    this->repo = designated_repo;
}

AdminService::AdminService(const AdminService &ms) {
    this->repo = ms.repo;
}

AdminService::~AdminService() {
}

// Operators Overload

AdminService& AdminService::operator=(const AdminService &ms) {
    this->repo = ms.repo;
    return *this;
}

Movie& AdminService::operator[](int index) {
    return this->repo[index];
}

// Getters

int AdminService::getAdminServiceLength() const {
    return this->repo.getAdminRepoLength();
}

int AdminService::getAdminServiceCapacity() const {
    return this->repo.getAdminRepoCapacity();
}

Movie& AdminService::getElementByUniqueField(const std::string &unique_field) {
    return this->repo.getElementByUniqueField(unique_field);
}

// Copy Database

int AdminService::copyDatabase(Movie* database_copy, const std::string &desired_genre){
    return this->repo.copyDatabase(database_copy, desired_genre);
}

// Add, Delete, Update

void AdminService::addElementAdminService(const std::string &title, const std::string &genre, int year_of_release, int nr_of_likes, const std::string &trailer) {
    Movie designated_movie(title, genre, year_of_release, nr_of_likes, trailer);
    this->repo.addElementAdminRepo(designated_movie);
}

void AdminService::deleteElementAdminService(const std::string &title) {
    this->repo.deleteElementAdminRepo(title);
}

void AdminService::updateElementAdminService(const std::string &title, const std::string &genre, int year_of_release, int nr_of_likes, const std::string &trailer) {
    Movie designated_movie(title, genre, year_of_release, nr_of_likes, trailer);
    this->repo.updateElementAdminRepo(designated_movie);
}

// First 10 Movies

void AdminService::firstMovies() {
    this->addElementAdminService("Climax", "Horror/Musical", 2018, 0, "https://youtu.be/gNp0jlfbgqM");
    this->addElementAdminService("Amélie", "Comedy Romance/Love", 2001, 0, "https://youtu.be/HUECWi5pX7o");
    this->addElementAdminService("Little Joe", "SF/Drama", 2018, 0, "https://youtu.be/eYfKlNBLLeQ");
    this->addElementAdminService("La science des rêves", "Surrealistic Science Fantasy/Comedy", 2006, 0,"https://youtu.be/dHtE0szIip0");
    this->addElementAdminService("Irréversible", "Psychological Thriller/Drama", 2002, 0,"https://youtu.be/ZoDtJjqkfxU");
    this->addElementAdminService("Fallen Angels", "Crime/Drama", 1995, 0, "https://youtu.be/dtum6XVH3HI");
    this->addElementAdminService("Instinct", "Drama/Thriller", 2019, 0, "https://www.youtube.com/watch?v=0OIetiMoseA");
    this->addElementAdminService("Love", "Erotic Drama", 2015, 0, "https://youtu.be/62yCdFzP9Mc");
    this->addElementAdminService("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
    this->addElementAdminService("Queen of Hearts", "Drama", 2019, 0, "https://youtu.be/MaxIbXW23NA");
}
