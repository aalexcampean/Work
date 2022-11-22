//
// Created by Alex Campean on 16.03.2022.
//
#pragma once
#include "../Domain/Country.h"

typedef Country TElem;
typedef char* UniqueField;

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
/// <param name="da">DynamicArray*, the dynamic array that needs to be destroyed</param>
/// <returns></returns
void destroyDynamicArray(DynamicArray* da);

// Resize

/// <summary>Resizes a given dynamic array, by doubling its capacity and reallocation all its elements</summary>
/// <param name="da">DynamicArray*, the dynamic array that needs to be resized</param>
/// <returns></returns
void resizeDynamicArray(DynamicArray* da);

// Getters

/// <summary>Returns the length of the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>The int associated to the field "total_elements" of the given Dynamic Array</returns
int getDaLength(DynamicArray* da);

/// <summary>Returns the capacity of the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>The int associated to the field "capacity" of the given dynamic array</returns
int getDaCapacity(DynamicArray* da);

/// <summary>Finds an element at a given index in the list of elements</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>A pointer to the elements indicated by the index in the list of elements</returns
TElem* getElementInDa(DynamicArray* da, int index);

/// <summary>Returns the list of items</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>A pointer to the array of elements</returns
TElem** getElements(DynamicArray* da);

// Make Dynamic Array Deep Copy

/// <summary>Makes a deep copy of the second dynamic array and puts it into the first one</summary>
/// <param name="da_1">DynamicArray*, the destination dynamic array</param>
/// <param name="da_2">DynamicArray*, the source dynamic array</param>
/// <returns></returns
void makeDaDeepCopy(DynamicArray* da1, DynamicArray* da2);

// Copy Dynamic Array

/// <summary>Returns a copy of a given dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <returns>A pointer to the copy of the given dynamic array</returns
DynamicArray* copyDynamicArray(DynamicArray* da);

// Add, Delete, Update

/// <summary>Adds an element to the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="elem">TElem*, the given element</param>
/// <returns>True if the element was added and False otherwise</returns
int addElement(DynamicArray* da, TElem* elem);

/// <summary>Deletes an element from the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="filed">UniqueField, the unique field of the element that needs to be deleted</param>
/// <returns>True if the element was deleted and False otherwise</returns
int deleteElement(DynamicArray* da, UniqueField filed);

/// <summary>Updates an element in the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="elem">TElem*, the given element</param>
/// <param name="modify">int, a flag indicating that a country's population need to be modified</param>
/// <returns>True if the element was updated and False otherwise</returns
int updateElement(DynamicArray* da, TElem* elem, int modify);

// Search

/// <summary>Searches for an element in the dynamic array</summary>
/// <param name="da">DynamicArray*, the given dynamic array</param>
/// <param name="field">UniqueField, the unique field of the elements that need to be search for</param>
/// <returns>True the index of the element if it exists and -1 otherwise</returns
int searchElementInDynamicArray(DynamicArray* da, UniqueField field);