//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "../Domain/Dog.h"
#include "../DynamicArray/Da.h"

class BaseRepository {
protected:
    DynamicArray<Dog> da;

public:
    /// Constructors, Destructor
    BaseRepository();
    BaseRepository(const BaseRepository &mr);
    ~BaseRepository();

    /// Getters
    size_t getRepoLength() const;
    size_t getRepoCapacity() const;

    /// Copy Database

    /// <summary>Copies from the repo into a list the dogs of a given breed</summary>
    /// <param name="databaseCopy">Dog*, the copy of the database</param>
    /// <param name="&desiredBreed">std::string, the given breed</param>
    /// <returns>The length of the newly copied list of dogs</returns
    virtual int copyDatabase(Dog* databaseCopy, const std::string &desiredBreed, double desiredAge) = 0;

    /// Add, Delete, Update

    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="&dog">Dog, a reference to the dog to be added to the repository</param>
    /// <returns></returns
    void addElementRepo(Dog& dog);
    /// <summary>Deletes an element from the repository layer</summary>
    /// <param name="&image">string, the image of the dog to be deleted from the repository</param>
    /// <returns></returns
    void deleteElementRepo(const std::string& image);
    /// <summary>Updates an element in the repository layer</summary>
    /// <param name="&dog">Dog, the dog to be updated</param>
    /// <returns></returns
    virtual void updateElementAdminRepo(Dog &dog) = 0;

    /// Operators Overload
    BaseRepository& operator=(const BaseRepository &mr);
    Dog& operator[](int index);
};


