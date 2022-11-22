#pragma once
#include "../DynamicArray/DA.h"
#define _CRT_SECURE_NO_WARNINGS

// The Structure

typedef struct{

    DynamicArray* da;

} Repository;

// Constructor, Destructor

/// <summary>Creates a repository layer</summary>
/// <param name="capacity">int, the capacity of the repository</param>
/// <returns>A pointer to the created repository</returns
Repository* createRepository(int capacity);

/// <summary>Destroys a repository layer and its contents</summary>
/// <param name="er">Repository*, the repository that needs to be destroyed</param>
/// <returns></returns
void destroyRepository(Repository* er);

// Getters

/// <summary>Returns the length of the list of elements stored in the repository</summary>
/// <param name="er">Repository*, the given repository</param>
/// <returns>The int associated to the length of the repository</returns
int getRepoLength(Repository* er);

/// <summary>Returns the capacity of the list of elements stored in the repository</summary>
/// <param name="er">Repository*, the given repository</param>
/// <returns>The int associated to the capacity of the repository</returns
int getRepoCapacity(Repository* er);

/// <summary>Finds an element at a given index in the repository</summary>
/// <param name="er">Repository*, the given repository</param>
/// <returns>A pointer to the elements indicated by the index in the repository</returns
TElem* getElementInRepo(Repository* er, int index);

// Make Repository Deep Copy

/// <summary>Makes a deep copy of the second repository and puts it into the first one</summary>
/// <param name="repo_1">Repository*, the destination repository</param>
/// <param name="repo_2">Repository*, the source repository</param>
/// <returns></returns
void makeRepoDeepCopy(Repository* repo_1, Repository*repo_2);

// Copy Repository

/// <summary>Returns a copy of a repository</summary>
/// <param name="er">Repository*, the given repository</param>
/// <returns>A pointer to the copy of the given repository</returns
Repository* copyRepository(Repository* er);

// Add, Delete, Update

/// <summary>Adds an element to the repository layer</summary>
/// <param name="er">Repository*, the given repository</param>
/// <param name="type">char*, the given type of the element</param>
/// <param name="address">char*, the given address of the element</param>
/// <param name="surface">double, the given surface of the element</param>
/// <param name="price">double, the given price of the element</param>
/// <returns>True if the element was added and False otherwise</returns
int addElementToRepository(Repository* er, char* type, char* address, double surface, double price);

/// <summary>Deletes an element from the repository layer</summary>
/// <param name="er">Repository*, the given repository</param>
/// <param name="adr">Char*, the address of the element that needs to be deleted</param>
/// <returns>True if the element was deleted and False otherwise</returns
int deleteElementFromRepository(Repository* er, char* adr);

/// <summary>Updates an element in the repository layer</summary>
/// <param name="er">Repository*, the given repository</param>
/// <param name="type">char*, the given type of the element</param>
/// <param name="address">char*, the given address of the element</param>
/// <param name="surface">double, the given surface of the element</param>
/// <param name="price">double, the given price of the element</param>
/// <returns>True if the element was updated and False otherwise</returns
int updateElementInRepository(Repository* er, char* type, char* address, double surface, double price);

// Search

/// <summary>Searches for an element in the repository layer by its address</summary>
/// <param name="er">Repository*, the given repository</param>
/// <param name="result_list">TElem*, the new list which will store the result of the search</param>
/// <param name="size_of_list">int*, the size of the result_list</param>
/// <param name="adr">char*, the partial string (the address) that is searched through all elements</param>
/// <returns>The list of results containing in their address the given partial string</returns
void searchElementInRepositoryByAddress(Repository* er, TElem** result_list, int* size_of_list, char* adr);

/// <summary>Searches for an element in the repository layer by its type</summary>
/// <param name="er">Repository*, the given repository</param>
/// <param name="result_list">TElem*, the new list which will store the result of the search</param>
/// <param name="size_of_list">int*, the size of the result_list</param>
/// <param name="adr">char*, the partial string (the type) that is searched through all elements</param>
/// <returns>The list of results containing in their type the given partial string</returns
void searchElementInRepositoryByType(Repository* er, TElem** result_list, int* size_of_list, char* type);