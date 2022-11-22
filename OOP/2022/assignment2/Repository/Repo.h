//
// Created by Alex Campean on 16.03.2022.
//
#pragma once
#include "../DynamicArray/DA.h"

typedef struct {
    DynamicArray* da;
} Repository;

// Constructor, Destructor

/// <summary>Creates a repository </summary>
/// <param name="capacity">int, the capacity of the repository</param>
/// <returns>A pointer to the created repository</returns
Repository* createRepository(int capacity);

/// <summary>Destroys a repository and its contents</summary>
/// <param name="repository">Repository*, the repository that needs to be destroyed</param>
/// <returns></returns
void destroyRepository(Repository* repository);

// Getters

/// <summary>Returns the length of the list of elements stored in the repository</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <returns>The int associated to the length of the repository</returns
int getRepoLength(Repository* repository);

/// <summary>Returns the capacity of the list of elements stored in the repository</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <returns>The int associated to the capacity of the repository</returns
int getRepoCapacity(Repository* repository);

/// <summary>Finds an element at a given index in the repository</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <returns>A pointer to the elements indicated by the index in the repository</returns
Country* getElementInRepo(Repository* repository, int index);

/// <summary>Returns the list of items in the repository</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <returns>A pointer to the elements stored in the repository</returns
Country** getElementsInRepo(Repository* repository);

// Make Repository Deep Copy

/// <summary>Makes a deep copy of the second repository and puts it into the first one</summary>
/// <param name="repo_1">Repository*, the destination repository</param>
/// <param name="repo_2">Repository*, the source repository</param>
/// <returns></returns
void makeRepoDeepCopy(Repository* repo1, Repository* repo2);

// Copy Repository

/// <summary>Returns a copy of a repository</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <returns>A pointer to the copy of the given repository</returns
Repository* copyRepository(Repository* repository);

// Add, Delete, Update

/// <summary>Adds an element to the repository</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <param name="country">Country*, the given country that needs to be added to the repository</param>
/// <returns>True if the country was added and False otherwise</returns
int addElementToRepository(Repository* repository, Country* country);

/// <summary>Deletes an element from the repository</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <param name="name">char*, the name of the country that needs to be deleted</param>
/// <returns>True if the country was deleted and False otherwise</returns
int deleteElementFromRepository(Repository* repository, char* name);

/// <summary>Updates an element in the repository layer</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <param name="country">Country*, the given country that needs to be updated in the repository</param>
/// <param name="modify">int, a flag indicating that a country's population need to be modified</param>
/// <returns>True if the country was updated and False otherwise</returns
int updateElementInRepository(Repository* repository, Country* country, int modify);

// Search

/// <summary>Searches for a country in the repo, based on its name</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <param name="name">char*, the given name of the country that needs to be searched for in the repository</param>
/// <returns>The index in the repository, if the country was found and -1 otherwise</returns
int searchCountryByNameInRepo(Repository* repository, char* name);

/// <summary>Filters the countries from the repository based on their name containing a substring</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <param name="result_list">TElem*, the new list which will store the result of the search</param>
/// <param name="size_of_list">int*, the size of the result_list</param>
/// <param name="name_string">char*, the partial string (the name) that is searched through all elements</param>
/// <returns>The list of results containing in their name, the given partial string</returns
void filterRepoByNameContainingString(Repository* repository, Country** result_list, int* size_of_list, char* name_string);

/// <summary>Searches for an element in the repository by its type</summary>
/// <param name="repository">Repository*, the given repository</param>
/// <param name="result_list">TElem*, the new list which will store the result of the search</param>
/// <param name="size_of_list">int*, the size of the result_list</param>
/// <param name="continent">char*, continent that is searched through all elements</param>
/// <returns>The list of results belonging to the given continent</returns
void filterRepoByContinent(Repository* repository, Country** result_list, int* size_of_list, char* continent);