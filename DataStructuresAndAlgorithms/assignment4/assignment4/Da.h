#pragma once
#include <string>
#include <iostream>

template<typename T>
class DynamicArray {
private:

    T* list;
    int nr_of_elements;
    int capacity;

public:

    // Constructor, Destructor

    DynamicArray(int capacity = 10);
    DynamicArray(const DynamicArray &da);
    ~DynamicArray();

    void resizeDynamicArray(double factor = 2);

    // Operators Overload
    DynamicArray& operator=(const DynamicArray &da);
    T& operator[](int index);

    // Getters

    int Length() const;
    int Capacity() const;
    int getIndex(T& elem) const;

    // Setters

    void setLength(int given_length);
    void setCapacity(int given_capacity);

    // Add, Delete

    void addElement(T &elem);
    void removeElement(T &elem);
};

// Constructor, Destructor

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

// Resize

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

// Operators Overload

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
        throw std::exception();
    }
    return this->list[index];
}

// Getter

template<typename T>
int DynamicArray<T>::Length() const{
    return this->nr_of_elements;
}

template<typename T>
int DynamicArray<T>::Capacity() const{
    return this->capacity;
}

template<typename T>
int DynamicArray<T>::getIndex(T& elem) const{
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

// Setters

template<typename T>
void DynamicArray<T>::setLength(int given_length) {
    this->nr_of_elements = given_length;
}

template<typename T>
void  DynamicArray<T>::setCapacity(int given_capacity) {
    this->capacity = given_capacity;
}

// Add, Delete

template<typename T>
void DynamicArray<T>::addElement(T &elem) {
    if (this->nr_of_elements == this->capacity) {
        this->resizeDynamicArray();
    }

    this->list[this->nr_of_elements] = elem;
    this->nr_of_elements += 1;
}

template<typename T>
void DynamicArray<T>::removeElement(T &elem) {
    int index = 0;
    while (this->list[index] != elem) {
        index += 1;
    }
    this->list[index] = this->list[nr_of_elements - 1];
    this->nr_of_elements -= 1;
}

