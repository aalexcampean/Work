#pragma once
#include "../Repository/Repo.h"
#define _CRT_SECURE_NO_WARNINGS

// The Structure

typedef struct {

    Repository* repository;

} Service;

// Constructor, Destructor

/// <summary>Creates a service layer</summary>
/// <param name="capacity">int, the capacity of the service</param>
/// <returns>A pointer to the created service</returns
Service* createService(int capacity);

/// <summary>Destroys a service layer and its contents</summary>
/// <param name="es">Service*, the service that needs to be destroyed</param>
/// <returns></returns
void destroyService(Service* es);

// Getters

/// <summary>Returns the length of the list of elements stored in the service</summary>
/// <param name="es">Service*, the given service</param>
/// <returns>The int associated to the length of the service</returns
int getServiceLength(Service* es);

/// <summary>Returns the capacity of the list of elements stored in the service</summary>
/// <param name="es">Service*, the given service</param>
/// <returns>The int associated to the capacity of the service</returns
int getServiceCapacity(Service* es);

/// <summary>Finds an element at a given index in the service</summary>
/// <param name="es">Service*, the given service</param>
/// <returns>A pointer to the elements indicated by the index in the service</returns
TElem* getElementInService(Service* es, int index);

// Add, Delete, Update

/// <summary>Adds an element to the service layer</summary>
/// <param name="es">Service*, the given service</param>
/// <param name="type">char*, the given type of the element</param>
/// <param name="address">char*, the given address of the element</param>
/// <param name="surface">double, the given surface of the element</param>
/// <param name="price">double, the given price of the element</param>
/// <returns>True if the element was added and False otherwise</returns
int addElementToService(Service* es, char* type, char* address, double surface, double price);

/// <summary>Deletes an element from the service layer</summary>
/// <param name="es">Service*, the given service</param>
/// <param name="adr">Char*, the address of the element that needs to be deleted</param>
/// <returns>True if the element was deleted and False otherwise</returns
int deleteElementFromService(Service* es, char* adr);

/// <summary>Updates an element in the service layer</summary>
/// <param name="es">Service*, the given service</param>
/// <param name="type">char*, the given type of the element</param>
/// <param name="address">char*, the given address of the element</param>
/// <param name="surface">double, the given surface of the element</param>
/// <param name="price">double, the given price of the element</param>
/// <returns>True if the element was updated and False otherwise</returns
int updateElementInService(Service* es, char* type, char* address, double surface, double price);

// Create the first 10 Elements

/// <summary>Populates the service->repository->dynamic_array with 10 elements</summary>
/// <param name="es">Service*, the given service</param>
/// <returns></returns
void populateListWithElements(Service* es);

// Search

/// <summary>Searches for an element in the service layer by its address ot by its type</summary>
/// <param name="es">Service*, the given service</param>
/// <param name="result_list">TElem*, the new list which will store the result of the search</param>
/// <param name="size_of_list">int*, the size of the result_list</param>
/// <param name="adr_type">char*, the partial string (the address ot the type) that is searched through all elements</param>
/// <returns>The list of results containing in their address or type the given partial string</returns
void searchElementInServiceByAddressOrType(Service* es, TElem** result_list, int* size_of_list, char* adr_type);

// Sort

/// <summary>Sorts a list by its type</summary>
/// <param name="given_list">TElem*, the given list that needs to be sorted</param>
/// <param name="size_of_list">int*, the size of the given_list</param>
/// <param name="option">char*, the option of sorting ascending or descending</param>
/// <returns>The sorted list</returns
void sortElementsByPrice(TElem** given_list, int size_of_list, char* option);

/// <summary>Sorts a list by its surface</summary>
/// <param name="given_list">TElem**, the given list that needs to be sorted</param>
/// <param name="size_of_list">int*, the size of the given_list</param>
/// <param name="option">char*, the option of sorting ascending or descending</param>
/// <returns>The sorted list</returns
void sortElementsBySurface(TElem** given_list, int size_of_list, char* option);

// Copy

/// <summary>Copies a given list into another</summary>
/// <param name="given_list">TElem**, the source list</param>
/// <param name="given_list">TElem**, the destination list</param>
/// <param name="size_of_list">int*, the size of the given_list</param>
/// <returns>The copied list</returns
void copyListOfElements(TElem** given_list, TElem** new_list, int size_of_list);

// Filter

/// <summary>Filters a list by its surface (all elements with a smaller / grater surface)</summary>
/// <param name="given_list">TElem**, the given list</param>
/// <param name="size_of_list">int*, the size of the given_list</param></param>
/// <param name="given_surface">Double, the surface which all the elements are filtered against</param>
/// <returns>The filtered list</returns
void filterElementsBySurface(TElem** given_list, int* size_of_list, double given_surface);

/// <summary>Filters a list by its price (all elements with a equal price)</summary>
/// <param name="given_list">TElem**, the given list</param>
/// <param name="size_of_list">int*, the size of the given_list</param></param>
/// <param name="given_price">Double, the price which all the elements are filtered against</param>
/// <returns>The filtered list</returns
void filterElementsByPrice(TElem** given_list, int* size_of_list, double given_price);