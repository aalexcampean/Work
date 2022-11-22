//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include "../../Domain/Dog.h"
#include <vector>

class InMemoryRepository {
protected:
    std::vector<Dog> dogs;

public:
    /// Constructors, Destructor
    InMemoryRepository();
    InMemoryRepository(const InMemoryRepository &mr);
    ~InMemoryRepository();

    /// Getters
    int getRepoLength() const;
    std::vector<Dog> getDogs() const;
    Dog& getDogByImage(const std::string &image);

    /// Add, Delete, Update

    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="&dog">Dog, a reference to the dog to be added to the repository</param>
    /// <returns></returns
    void addElementRepo(const Dog& dog);
    /// <summary>Deletes an element from the repository layer</summary>
    /// <param name="&image">string, the image of the dog to be deleted from the repository</param>
    /// <returns></returns
    void deleteElementRepo(const std::string& image);
    /// <summary>Updates an element in the repository layer</summary>
    /// <param name="&dog">Dog, the dog to be updated</param>
    /// <returns></returns
    void updateElementAdminRepo(const Dog &dog);

    /// Operators Overload
    InMemoryRepository& operator=(const InMemoryRepository &mr);
    Dog& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const InMemoryRepository &repository);

    /// Pure Virtual Methods
    virtual void save() = 0;
};

inline std::ostream& operator<<(std::ostream& stream, const InMemoryRepository &repository) {
    for (auto& it : repository.getDogs()) {
        stream << it << "\n";
    }
    return stream;
}


