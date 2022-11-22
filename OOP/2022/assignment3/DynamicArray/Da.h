//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include <string>
#include <iostream>

typedef std::string uniqueType;

template<typename T>
class DynamicArray {
private:
    T* list;
    int nr_of_elements;
    int capacity;

public:
    /// Constructors, Destructor
    DynamicArray(int capacity = 10);
    DynamicArray(const DynamicArray &da);
    ~DynamicArray();

    /// Getters
    size_t getLength() const;
    size_t getCapacity() const;
    int getIndex(const uniqueType &uniqueIdentifier) const;
    int getIndex(const T &elem) const;

    /// Add, Delete, Update

    /// <summary>Adds an element in the dynamic array</summary>
    /// <param name="elem">T, the element to be added to the Dynamic Array</param>
    /// <returns></returns
    void addElement(T &elem);

    /// <summary>Deletes an element from the dynamic array</summary>
    /// <param name="index">int, the index of the element to be deleted</param>
    /// <returns></returns
    void deleteElement(int index);

    /// <summary>Updates an element in the dynamic array</summary>
    /// <param name="elem">T, the title to be updated in the Dynamic Array</param>
    /// <returns></returns
    void updateElement(T &elem);

    /// Operators Overload
    DynamicArray& operator=(const DynamicArray &da);
    T& operator[](int index);

private:
    /// Resize
    void resizeDynamicArray(double factor = 2);
};

/// Methods' definition

/// Constructor, Destructor
template<typename T>
DynamicArray<T>::DynamicArray(int capacity) {
    this->nr_of_elements = 0;
    this->capacity = capacity;
    this->list = new T[capacity];
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->list;
    this->list = nullptr;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &da) {
    for (int i = 0; i < this->nr_of_elements; i++){
        da.list[i] = this->list[i];
    }

    da.nr_of_elements = this->nr_of_elements;
    da.capacity = this->capacity;
    return* da;
}

/// Resize
template<typename T>
void DynamicArray<T>::resizeDynamicArray(double factor){
    this->capacity *= factor;

    T* new_list = new T[this->capacity];
    for (int i = 0; i < this->nr_of_elements; i++) {
        new_list[i] = this->list[i];
    }

    delete[] this->list;
    this->list = new_list;
}

/// Operators Overload
template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &da) {
    for (int i = 0; i < da.nr_of_elements; i++){
        this->list[i] = da.list[i];
    }

    this->nr_of_elements = da.nr_of_elements;
    this->capacity = da.capacity;

    return *this;
}

template<typename T>
T& DynamicArray<T>::operator[](int index) {
    if (index > this->nr_of_elements - 1 || index < 0){
        throw std::string("Index out of range");
    }
    return this->list[index];
}

/// Getters
template<typename T>
size_t DynamicArray<T>::getLength() const{
    return this->nr_of_elements;
}

template<typename T>
size_t DynamicArray<T>::getCapacity() const{
    return this->capacity;
}

template<typename T>
int DynamicArray<T>::getIndex(const uniqueType &uniqueIdentifier) const{
    int index = 0;
    while (index < this->nr_of_elements){
        if (this->list[index] == uniqueIdentifier) {
            return index;
        }
        else {
            index += 1;
        }
    }

    return -1;
}

template<typename T>
int DynamicArray<T>::getIndex(const T &elem) const{
    int index = 0;
    while (index < this->nr_of_elements){
        if (this->list[index] == elem) {
            return index;
        }
        else {
            index += 1;
        }
    }

    return -1;
}

/// Add, Delete, Update
template<typename T>
void DynamicArray<T>::addElement(T &elem) {
    if (this->nr_of_elements == this->capacity) {
        this->resizeDynamicArray();
    }

    this->list[this->nr_of_elements] = elem;
    this->nr_of_elements += 1;
}

template<typename T>
void DynamicArray<T>::deleteElement(int index) {
    this->list[index] = this->list[nr_of_elements - 1];
    this->nr_of_elements -= 1;
}

template<typename T>
void DynamicArray<T>::updateElement(T &elem) {
    this->list[this->getIndex(elem)] = elem;
}