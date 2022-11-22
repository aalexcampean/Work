#pragma once
#include "../Domain/Estate.h"
#define _CRT_SECURE_NO_WARNINGS

typedef Estate TElem;

// The Structure

typedef struct{

    TElem** list;
    int total_elements;
    int capacity;

} DynamicArray;

// Constructor, Destructor

/// <summary>Creates a dynamic array with its contents and its specific fields</summary>
/// <param name="capacity">Int, maximum capacity for the dynamic array</param>
/// <returns>A pointer to the created dynamic array</returns
DynamicArray* createDynamicArray(int capacity);

/// <summary>Destroys a dynamic array and its specific fields</summary>
/// <param name="da">DynamicArray*, the dynamic array the needs to be destroyed</param>
/// <returns></returns
void destroyDynamicArray(DynamicArray* da);

// Resize

/// <summary>Resizes a given dynamic by doubling its capacity and reallocation all its elements</summary>
/// <param name="da">DynamicArray*, the dynamic array the needs to be resized</param>
/// <returns></returns
void resizeDynamicArray(DynamicArray* da);

// Getters

/// <summary>Returns the "total_elements" field of the element</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>The int associated to the field "total_elements" of the given Dynamic Array</returns
int getDaLength(DynamicArray* da);

/// <summary>Returns the "capacity" field of the element</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>The int associated to the field "capacity" of the given dynamic array</returns
int getDaCapacity(DynamicArray* da);

/// <summary>Finds an element at a given index in the list of elements</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>A pointer to the elements indicated by the index in the list of elements</returns
TElem* getElementInDa(DynamicArray* da, int index);

// Make Dynamic Array Deep Copy

/// <summary>Makes a deep copy of the second dynamic array and puts it into the first one</summary>
/// <param name="da_1">DynamicArray*, the destination dynamic array</param>
/// <param name="da_2">DynamicArray*, the source dynamic array</param>
/// <returns></returns
void makeDaDeepCopy(DynamicArray* da_1, DynamicArray* da_2);

// Copy Dynamic Array

/// <summary>Returns a copy of a given dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>A pointer to the copy of the given dynamic array</returns
DynamicArray* copyDynamicArray(DynamicArray* da);

// Add, Delete, Update

/// <summary>Adds an element to the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="e">TElem, the given element</param>
/// <returns>True if the element was added and False otherwise</returns
int addElementInDynamicArray(DynamicArray* da, char* type, char* address, double surface, double price);

/// <summary>Deletes an element from the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="adr">Char*, the address of the element that needs to be deleted</param>
/// <returns>True if the element was deleted and False otherwise</returns
int deleteElementFromDynamicArray(DynamicArray* da, char* adr);

/// <summary>Updates an element in the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="e">TElem, the given element</param>
/// <returns>True if the element was updated and False otherwise</returns
int updateElementInDynamicArray(DynamicArray* da, char* type, char* address, double surface, double price);

// Search

/// <summary>Searches for an element in the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="adr">Char*, the address of the elements that need to be search for</param>
/// <returns>True if the element was found and False otherwise</returns
int searchElementInDynamicArray(DynamicArray* da, char* adr);