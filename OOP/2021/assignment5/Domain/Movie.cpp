#include "Movie.h"

// Constructor, Destructor

Movie::Movie() {
    this->title = "";
    this->genre = "";
    this->year_of_release = 0;
    this->nr_of_likes = 0;
    this->trailer = "";
}

Movie::Movie(const std::string& title, const std::string& genre, int year_of_release, int nr_of_likes, const std::string& trailer){
    this->title = title;
    this->genre = genre;
    this->year_of_release = year_of_release;
    this->nr_of_likes = nr_of_likes;
    this->trailer = trailer;
}

Movie::Movie(const Movie& m){
    this->title = m.title;
    this->genre = m.genre;
    this->year_of_release = m.year_of_release;
    this->nr_of_likes = m.nr_of_likes;
    this->trailer = m.trailer;
}

Movie::~Movie(){

}

//Operators Overload

Movie& Movie::operator=(const Movie& m) {
    this->title = m.title;
    this->genre = m.genre;
    this->year_of_release = m.year_of_release;
    this->nr_of_likes = m.nr_of_likes;
    this->trailer = m.trailer;

    return *this;
}

bool Movie::operator==(const Movie& m) const{
    return this->title == m.title;
}

bool Movie::operator==(const std::string& given_title) const {
    return this->title == given_title;
}

// Getters

std::string Movie::getTitle() const{
    return this->title;
}

std::string Movie::getGenre() const{
    return this->genre;
}

int Movie::getYearOfRelease() const{
    return this->year_of_release;
}

int Movie::getNrOfLikes() const{
    return this->nr_of_likes;
}

std::string Movie::getTrailer() const{
    return this->trailer;
}

// Setters

void Movie::setGenre(const std::string& new_genre) {
    this->genre = new_genre;
}

void Movie::setYearOfRelease(int new_year_of_release) {
    this->year_of_release = new_year_of_release;
}

void Movie::setNrOfLikes(int new_nr_of_likes) {
    this->nr_of_likes = new_nr_of_likes;
}

void Movie::setTrailer(const std::string& new_trailer) {
    this->trailer = new_trailer;
}

void Movie::setNonUniqueAttributes(const std::string& new_genre, int new_year_of_release, int new_nr_of_likes, const std::string& new_trailer) {
    setGenre(new_genre);
    setYearOfRelease(new_year_of_release);
    setNrOfLikes(new_nr_of_likes);
    setTrailer(new_trailer);
}

std::string Movie::toString() {
    std::string string_representation = "";

    string_representation += "Title: " + this->getTitle() + "  |  ";
    string_representation += "Genre: " + this->getGenre() + "  |  ";
    string_representation += "Year of Release: " + std::to_string(this->getYearOfRelease()) + "  |  ";
    string_representation += "Number of Likes: " + std::to_string(this->getNrOfLikes()) + "  |  ";
    string_representation += "Trailer: " + this->getTrailer();
    string_representation += "\n";

    return string_representation;
}
