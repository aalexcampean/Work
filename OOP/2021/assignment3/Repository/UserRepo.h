#pragma once
#include "../Domain/Movie.h"
#include "../DynamicArray/Da.h"

class UserRepository{
private:
    DynamicArray<Movie> da;

public:

    // Constructor, Destructor

    UserRepository();
    UserRepository(const UserRepository &mr);
    ~UserRepository();

    // Operators Overload

    UserRepository& operator=(const UserRepository &mr);
    Movie& operator[](int index);

    // Getter

    int getUserRepoLength() const;
    int getUserRepoCapacity() const;

    // Add, Delete, Update

    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="&m">Movie, a reference to the movie element that needs to be added to the repository</param>
    /// <returns></returns
    void addElementUserRepo(Movie &m);

    /// <summary>Deletes an element from the repository layer</summary>
    /// <param name="title">string, the title of the movie that needs to be deleted from the repo</param>
    /// <returns></returns
    void deleteElementUserRepo(const std::string &title);

};
