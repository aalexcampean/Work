//
// Created by Alex Campean on 16.03.2022.
//
#pragma once
#include "../Repository/Repo.h"

typedef struct {
    Repository* repository;
} Service;

// Constructor, Destructor

/// <summary>Creates a service layer</summary>
/// <param name="capacity">int, the capacity of the service</param>
/// <returns>A pointer to the created service</returns
Service* createService(int capacity);

/// <summary>Destroys a service layer and its contents</summary>
/// <param name="service">Service*, the service that needs to be destroyed</param>
/// <returns></returns
void destroyService(Service* service);

// Getters

/// <summary>Returns the length of the list of elements stored in the service</summary>
/// <param name="service">Service*, the given service</param>
/// <returns>The int associated to the length of the service</returns
int getServiceLength(Service* service);

/// <summary>Returns the capacity of the list of elements stored in the service</summary>
/// <param name="service">Service*, the given service</param>
/// <returns>The int associated to the capacity of the service</returns
int getServiceCapacity(Service* service);

/// <summary>Finds an element at a given index in the service</summary>
/// <param name="service">Service*, the given service</param>
/// <returns>A pointer to the elements indicated by the index in the service</returns
Country* getElementInService(Service* service, int index);

/// <summary>Returns the list of items in the service</summary>
/// <param name="service">Service*, the given service</param>
/// <returns>A pointer to the elements stored in the service</returns
Country** getElementsInService(Service* service);

/// <summary>Returns the repository of the service</summary>
/// <param name="service">Service*, the given service</param>
/// <returns>A pointer to the repository stored in the service</returns
Repository* getRepository(Service* service);

// Add, Delete, Update

/// <summary>Adds a country to the service</summary>
/// <param name="service">Service*, the given service</param>
/// <param name="name">char*, the given name of the country</param>
/// <param name="continent">char*, the given continent of the country</param>
/// <param name="population">double, the given population of the country</param>
/// <returns>True if the element was added and False otherwise</returns
int addElementToService(Service* service, char* name, char* continent, double population);

/// <summary>Deletes a country from the service</summary>
/// <param name="service">Service*, the given service</param>
/// <param name="name">Char*, the name of the country that needs to be deleted</param>
/// <returns>True if the country was deleted and False otherwise</returns
int deleteElementFromService(Service* service, char* name);

/// <summary>Updates an country in the service</summary>
/// <param name="service">Service*, the given service</param>
/// <param name="name">char*, the given name of the country</param>
/// <param name="continent">char*, the given continent of the country</param>
/// <param name="population">double, the given population of the country</param>
/// <returns>True if the element was updated and False otherwise</returns
int updateElementInService(Service* service, char* name, char* continent, double population);

/// <summary>Updates an country in the service</summary>
/// <param name="service">Service*, the given service</param>
/// <param name="name1">char*, the given name of the home country</param>
/// <param name="continent1">char*, the given continent of the home country</param>
/// <param name="population">double, the given population of the country</param>
/// <param name="name2">char*, the given name of the destination country</param>
/// <param name="continent2">char*, the given continent of the destination country</param>
/// <returns>True if the elements were updated and False otherwise</returns
int updateElementsInService(Service* es, char* name1, char* continent1, double population, char* name2, char* continent2);

// Create the first 10 Elements

/// <summary>Populates the service->repository->dynamic_array with 10 elements</summary>
/// <param name="service">Service*, the given service</param>
/// <returns></returns
void populateServiceWithEntries(Service* service);

// Sort

/// <summary>Sorts a list by its population</summary>
/// <param name="given_list">TElem*, the given list that needs to be sorted</param>
/// <param name="size_of_list">int*, the size of the given_list</param>
/// <param name="option">char*, the option of sorting ascending or descending</param>
/// <returns>The sorted list</returns
void sortElementsByPopulation(Country** given_list, int size_of_list, char* option);

// Copy

/// <summary>Copies a given list into another</summary>
/// <param name="given_list">TElem**, the source list</param>
/// <param name="given_list">TElem**, the destination list</param>
/// <param name="size_of_list">int*, the size of the given_list</param>
/// <returns>The copied list</returns
void shallowCopyListOfElements(Country** given_list, Country** new_list, int size_of_list);

// Filter

/// <summary>Filters a list by whether a string is found in the name or not</summary>
/// <param name="given_list">TElem**, the given list</param>
/// <param name="size_of_list">int*, the size of the given_list</param></param>
/// <param name="name">char*, the string which all the elements' names are filtered against</param>
/// <returns>The filtered list</returns
void filterServiceByNameContainingString(Service* service, Country** given_list, int* size_of_list, char* name);

/// <summary>Filters a list by whether a country is found in the provided continent or not</summary>
/// <param name="given_list">TElem**, the given list</param>
/// <param name="size_of_list">int*, the size of the given_list</param></param>
/// <param name="continent">char*, the continent which all the elements are filtered against</param>
/// <returns>The filtered list</returns
void filterServiceByContinent(Service* service, Country** given_list, int* size_of_list, char* continent);


/// <summary>Filters a list by its population (all elements with a grater population than the provided value)</summary>
/// <param name="given_list">TElem**, the given list</param>
/// <param name="size_of_list">int*, the size of the given_list</param></param>
/// <param name="population">double, the population value which all the elements are filtered against</param>
/// <returns>The filtered list</returns
void filterElementsByPopulation(Country** given_list, int* size_of_list, double population);
