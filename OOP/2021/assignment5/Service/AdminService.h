#pragma once
#include "../TextRepository/TextRepo.h"

class AdminService{
private:
    TextRepo* repo;

public:

    // Constructor, Destructor
    AdminService();
    AdminService(const AdminService &ms);
    ~AdminService();

    // Operators Overload

    AdminService& operator=(const AdminService &ms);
    friend std::ostream& operator<<(std::ostream& out, const AdminService& service);

    // Getters

    int getLength() const;
    Movie& getElementByTitle(const std::string &title);
    std::vector<Movie> getDataBase() const;

    // Copy Database

    /// <summary>Copies from the service into a list the movies with a given genre</summary>
    /// <param name="database_copy">Movie*, the new list</param>
    /// <param name="desired_genre">the given genre</param>
    /// <returns>the length of the new list</returns
    std::vector<Movie> copyDatabase(const std::string &desired_genre);

    // Add, Delete, Update

    /// <summary>Adds an element to the adminService layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was added and False otherwise</returns
    void addElement(const std::string& title, const std::string& genre, const std::string& year_of_release, const std::string& nr_of_likes, const std::string& trailer);

    /// <summary>Deletes an element from the adminService layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <returns>True if the element was deleted and False otherwise</returns
    void deleteElement(const std::string &title);

    /// <summary>Updates an element in the adminService layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was updated and False otherwise</returns
    void updateElement(const std::string &title, const std::string &genre, const std::string& year_of_release, const std::string& nr_of_likes, const std::string &trailer);

    // First 10 Movies

    /// <summary>Populates the adminService->repository->dynamic_array with 10 elements</summary>
    /// <param name=""></param>
    /// <returns></returns
    void firstMovies();
};

inline std::ostream& operator<<(std::ostream& out, const AdminService& service) {
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