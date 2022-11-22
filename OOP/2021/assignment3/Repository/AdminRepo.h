#pragma once
#include "../Domain/Movie.h"
#include "../DynamicArray/Da.h"

class AdminRepository{
private:
    DynamicArray<Movie> da;

public:

    // Constructor, Destructor

    AdminRepository();
    AdminRepository(const AdminRepository &mr);
    ~AdminRepository();

    // Operators Overload

    AdminRepository& operator=(const AdminRepository &mr);
    Movie& operator[](int index);

    // Getter

    int getAdminRepoLength() const;
    int getAdminRepoCapacity() const;
    Movie& getElementByUniqueField(const std::string &unique_field);

    // Copy Database

    /// <summary>Copies from the repo into a list the movies with a given genre</summary>
    /// <param name="database_copy">Movie*, the new list</param>
    /// <param name="desired_genre">the given genre</param>
    /// <returns>the length of the new list</returns
    int copyDatabase(Movie* database_copy, const std::string &desired_genre);

    // Add, Delete, Update

    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was added and False otherwise</returns
    void addElementAdminRepo(Movie &m);

    /// <summary>Deletes an element from the repository layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <returns>True if the element was deleted and False otherwise</returns
    void deleteElementAdminRepo(const std::string &title);

    /// <summary>Updates an element in the repository layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was updated and False otherwise</returns
    void updateElementAdminRepo(Movie &m);
};