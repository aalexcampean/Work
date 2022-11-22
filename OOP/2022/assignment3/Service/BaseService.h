//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "../Repository/BaseRepository.h"


class BaseService {
protected:
    BaseRepository* repository;

public:
    /// Constructors, Destructor
    BaseService(BaseRepository* repository);
    BaseService(const BaseService &service);
    ~BaseService();

    /// Operators Overload
    BaseService& operator=(const BaseService &service);
    Dog& operator[](int index);

    /// Getters
    int getServiceLength() const;
    int getServiceCapacity() const;

    /// Copy Database

    /// <summary>Copies from the service into a list the dogs of a given breed</summary>
    /// <param name="databaseCopy">Movie*, the new list</param>
    /// <param name="desiredBreed">the given breed</param>
    /// <returns>the length of the new list</returns
    virtual int copyDatabase(Dog* databaseCopy, const std::string &desiredBreed, double desiredAg) = 0;

    /// Add, Delete, Update

    /// <summary>Adds an element to the service layer</summary>
    /// <param name="breed">string, the breed of the dog</param>
    /// <param name="name">string, the name of the dog</param>
    /// <param name="age">double, the age of the dog</param>
    /// <param name="image">string, the link to the image of the dog</param>
    /// <returns></returns
    void addElementService(const std::string &breed, const std::string &name, double age, const std::string &image);
    /// <summary>Deletes an element from the service layer</summary>
    /// <param name="image">string, the link to the image of the dog</param>
    /// <returns></returns
    void deleteElementService(const std::string &image);
    /// <summary>Updates an element in the service layer</summary>
    /// <param name="breed">string, the breed of the dog</param>
    /// <param name="name">string, the name of the dog</param>
    /// <param name="age">double, the age of the dog</param>
    /// <param name="image">string, the link to the image of the dog</param>
    /// <returns></returns
    virtual void updateElementService(const std::string &breed, const std::string &name, double age, const std::string &image) = 0;

    /// First 10 Dogs

    /// <summary>Populates the service with 10 entries</summary>
    /// <returns></returns
    virtual void firstDogs() = 0;
};


