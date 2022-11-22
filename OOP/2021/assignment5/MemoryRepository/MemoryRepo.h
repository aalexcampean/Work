#pragma once
#include "../Domain/Movie.h"
#include <vector>

class MemoryRepo{
protected:
    std::vector<Movie> db;

public:

    // Constructor, Destructor

    MemoryRepo();
    MemoryRepo(const MemoryRepo &mr);
    ~MemoryRepo();

    // Operators Overload

    MemoryRepo& operator=(const MemoryRepo &repo);
    Movie& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const MemoryRepo &repo);

    // Getter

    int getLength() const;
    std::vector<Movie> getDataBase() const;
    Movie& getElementByTitle(const std::string &title);

    // Add, Delete, Update

    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was added and False otherwise</returns
    void addElement(Movie &m);

    /// <summary>Deletes an element from the repository layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <returns>True if the element was deleted and False otherwise</returns
    void deleteElement(const std::string &title);

    /// <summary>Updates an element in the repository layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was updated and False otherwise</returns
    void updateElement(Movie &m);

    virtual void save(){};
};

inline std::ostream& operator<<(std::ostream& stream, const MemoryRepo &repo) {
    for (auto& it : repo.db) {
        stream << it << "\n";
    }
    return stream;
}