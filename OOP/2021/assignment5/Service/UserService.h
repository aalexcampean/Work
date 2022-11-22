#pragma once
//#include "../MemoryRepository/MemoryRepo.h"
#include "../TextRepository/TextRepo.h"
#include "../CsvRepository/CsvRepo.h"
#include "../HtmlRepository/HtmlRepo.h"

class UserService{
private:
    TextRepo* repo;

public:

    // Constructor, Destructor

    UserService();
    UserService(TextRepo* rep);
    UserService(const UserService &ums);
    ~UserService();

    // Set type of repo

    void setRepoType(const std::string& type);

    // Operators Overload

    UserService& operator=(const UserService &ms);
    friend std::ostream& operator<<(std::ostream& stream, const UserService &service);

    // Find Element

    bool findElement(const std::string &given_title);

    // Add, Delete, Update

    /// <summary>Adds an element to the adminService layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was added and False otherwise</returns
    void addElement(const std::string &title, const std::string &genre, int year_of_release, int nr_of_likes, const std::string &trailer);

    /// <summary>Deletes an element from the adminService layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <returns>True if the element was deleted and False otherwise</returns
    void deleteElement(const std::string &title);

    void openFile();
};

inline std::ostream& operator<<(std::ostream& out, const UserService& service) {
    std::vector<Movie> data_base = service.repo->getDataBase();
    for (auto& it : data_base) {
        out << "Title: " << it.getTitle() << "  |  ";
        out << "Genre: " << it.getGenre() << "  |  ";
        out << "Year of Release: " << std::to_string(it.getYearOfRelease()) << "  |  ";
        out << "Number of Likes: " << std::to_string(it.getNrOfLikes()) << "  |  ";
        out << "Trailer: " << it.getTrailer();
        out << "\n";
    }
    return out;
}