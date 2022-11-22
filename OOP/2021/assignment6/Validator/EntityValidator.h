#include <exception>
#include <string>

class EntityValidator{
public:
    static bool validateMovie(const std::string& title, const std::string& genre, const std::string& year_of_release, const std::string& nr_of_likes, const std::string& trailer);
    static bool validateTitle(const std::string& title);
    static bool validateGenre(const std::string& genre);
    static bool validateYearOfRelease(const std::string& year_of_release);
    static bool validateNrOfLikes(const std::string& nr_of_likes);
    static bool validateTrailer(const std::string& trailer);
};

