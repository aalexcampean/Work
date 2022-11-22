#include "EntityValidator.h"
#include "../Exception/CustomException.h"

bool EntityValidator::validateMovie(const std::string& title, const std::string& genre, const std::string& year_of_release, const std::string& nr_of_likes, const std::string& trailer) {
    return validateTitle(title) && validateGenre(genre) && validateYearOfRelease(year_of_release) && validateNrOfLikes(nr_of_likes) && validateTrailer(trailer) ;
}

bool EntityValidator::validateTitle(const std::string& title) {
    if (title.empty()) {
        throw CustomException(0001, "Invalid input for the field title (should be non empty)");
    }
    return true;
}

bool EntityValidator::validateGenre(const std::string& genre) {
    if (genre.empty()) {
        throw CustomException(0001, "Invalid input for the field genre (should be non empty)");
    }
    return true;
}

bool EntityValidator::validateYearOfRelease(const std::string& year_of_release) {
    size_t pos1;
    int validated_year_of_release;
    try {
        validated_year_of_release = std::stoi(year_of_release, &pos1);
    }
    catch (const std::invalid_argument){
    }
    if (pos1 != year_of_release.size()) {
        throw CustomException(0001, "Invalid input for the field year of release (should be a integer value)");
    }
    if (validated_year_of_release < 1000 || validated_year_of_release > 2030) {
        throw CustomException(0001, "Invalid input for the field year of release (should be > 1000 and < 2030)");
    }
    return true;
}

bool EntityValidator::validateNrOfLikes(const std::string& nr_of_likes) {
    size_t pos1;
    int validated_nr_of_likes;
    try {
        validated_nr_of_likes = std::stoi(nr_of_likes, &pos1);
    }
    catch (const std::invalid_argument){
    }
    if (pos1 != nr_of_likes.size()) {
        throw CustomException(0001, "Invalid input for the field number of likes (should be a integer value)");
    }
    if (validated_nr_of_likes < 0) {
        throw CustomException(0001, "Invalid input for the field number of likes (should be > 0)");
    }
    return true;
}

bool EntityValidator::validateTrailer(const std::string &trailer) {
    if (trailer.rfind("https://", 0) != 0) {
        throw CustomException(0001, "Invalid input for the field trailer link (should start with https://)");
    }
    return true;
}
