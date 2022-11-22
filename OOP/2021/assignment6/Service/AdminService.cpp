#include "AdminService.h"
#include "../Validator/EntityValidator.h"

// Constructor, Destructor

AdminService::AdminService() {
    this->repo = new TextRepo{"Database.txt"};
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

// Getters

int AdminService::getLength() const {
    return this->repo->getLength();
}

Movie& AdminService::getElementByTitle(const std::string &title) {
    return this->repo->getElementByTitle(title);
}

std::vector<Movie> AdminService::getDataBase() const {
    return this->repo->getDataBase();
}

TextRepo *AdminService::getRepoState() {
    return this->repo;
}

// Copy Database

std::vector<Movie> AdminService::copyDatabase(const std::string &desired_genre){
    std::vector<Movie> database_copy;
    std::vector<Movie> database = this->repo->getDataBase();
    if (desired_genre.empty()){
//        database_copy.insert(database_copy.end(), database.begin(), database.end());
        std::for_each(database.begin(), database.end(),[&database_copy](auto &it){database_copy.push_back(it);});
    }
    else {
        std::for_each(database.begin(), database.end(),[&database_copy, desired_genre](auto &it){if (it.getGenre() == desired_genre) database_copy.push_back(it);});
    }
    return database_copy;
}

// Add, Delete, Update

void AdminService::addElement(const std::string &title, const std::string &genre, const std::string& year_of_release, const std::string& nr_of_likes, const std::string &trailer) {
    if (EntityValidator::validateMovie(title, genre, year_of_release, nr_of_likes, trailer)) {
        size_t pos2;
        int validated_year_of_release = std::stoi(year_of_release, &pos2);
        int validated_nr_of_likes = std::stoi(nr_of_likes, &pos2);

        Movie designated_movie(title, genre, validated_year_of_release, validated_nr_of_likes, trailer);
        this->repo->addElement(designated_movie);
    }
}

void AdminService::deleteElement(const std::string &title) {
    if (EntityValidator::validateTitle(title)){
        this->repo->deleteElement(title);
    }
}

void AdminService::updateElement(const std::string &title, const std::string &genre, const std::string& year_of_release, const std::string& nr_of_likes, const std::string &trailer) {
    if (EntityValidator::validateMovie(title, genre, year_of_release, nr_of_likes, trailer)) {
        size_t pos2;
        int validated_year_of_release = std::stoi(year_of_release, &pos2);
        int validated_nr_of_likes = std::stoi(nr_of_likes, &pos2);

        Movie designated_movie(title, genre, validated_year_of_release, validated_nr_of_likes, trailer);
        this->repo->updateElement(designated_movie);
    }
}

// First 10 Movies

void AdminService::firstMovies() {
    this->addElement("Climax", "Horror/Musical", "2018", "0", "https://youtu.be/gNp0jlfbgqM");
    this->addElement("Amélie", "Comedy Romance/Love", "2001", "0", "https://youtu.be/HUECWi5pX7o");
    this->addElement("Little Joe", "SF/Drama", "2018", "0", "https://youtu.be/eYfKlNBLLeQ");
    this->addElement("La science des rêves", "Surrealistic Science Fantasy/Comedy", "2006", "0","https://youtu.be/dHtE0szIip0");
    this->addElement("Irréversible", "Psychological Thriller/Drama", "2002", "0","https://youtu.be/ZoDtJjqkfxU");
    this->addElement("Fallen Angels", "Crime/Drama", "1995", "0", "https://youtu.be/dtum6XVH3HI");
    this->addElement("Instinct", "Drama/Thriller", "2019", "0", "https://www.youtube.com/watch?v=0OIetiMoseA");
    this->addElement("Love", "Erotic Drama", "2015", "0", "https://youtu.be/62yCdFzP9Mc");
    this->addElement("Garçon Chiffon", "Comedy/Drama", "2020", "0", "https://youtu.be/Ghdso2T9qwA");
    this->addElement("Queen of Hearts", "Drama", "2019", "0", "https://youtu.be/MaxIbXW23NA");
}


