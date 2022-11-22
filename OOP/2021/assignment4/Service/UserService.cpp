#include "UserService.h"

// Constructor, Destructor

UserService::UserService() {
    this->repo = new TextRepo;
}

UserService::UserService(TextRepo* rep) {
    this->repo = rep;
}

UserService::UserService(const UserService &ums){
    this->repo = ums.repo;
}

UserService::~UserService() {
}

// Set type of repo

void UserService::setRepoType(const std::string& type) {
    if (type == "csv") {
        delete this->repo;
        this->repo = new CsvRepo;
    }
    else if (type == "html") {
        delete this->repo;
        this->repo = new HtmlRepo;
    }
    else {

    }
}

// Operators Overload

UserService& UserService::operator=(const UserService &ums) {
    this->repo = ums.repo;
    return *this;
}

// Find Element

bool UserService::findElement(const std::string &given_title) {
    std::vector<Movie> database = this->repo->getDataBase();
    auto it = find_if(database.begin(), database.end(), [given_title](const Movie& m) {return m.getTitle() == given_title;});

    if (it != database.end()){
        return true;
    }
    return false;
}

// Add, Delete, Update

void UserService::addElement(const std::string &title, const std::string &genre, int year_of_release, int nr_of_likes, const std::string &trailer) {
    Movie designated_movie(title, genre, year_of_release, nr_of_likes, trailer);
    this->repo->addElement(designated_movie);
}

void UserService::deleteElement(const std::string &title) {
    this->repo->deleteElement(title);
}

void UserService::openFile() {
    this->repo->openFile();
}
