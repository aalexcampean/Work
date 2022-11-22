#pragma once
#include "../Repository/UserRepo.h"

class UserService{
private:
    UserRepository repo;

public:

    // Constructor, Destructor

    UserService();
    UserService(const UserService &ms);
    ~UserService();

    // Operators Overload

    UserService& operator=(const UserService &ms);
    Movie& operator[](int index);

    // Getters

    int getUserServiceLength() const;
    int getUserServiceCapacity() const;

    // Add, Delete, Update

    /// <summary>Adds an element to the adminService layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was added and False otherwise</returns
    void addElementUserService(const std::string &title, const std::string &genre, int year_of_release, int nr_of_likes, const std::string &trailer);

    /// <summary>Deletes an element from the adminService layer</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <returns>True if the element was deleted and False otherwise</returns
    void deleteElementUserService(const std::string &title);
};
