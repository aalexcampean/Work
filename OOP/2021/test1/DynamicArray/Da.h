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

    // Operators Overload
    DynamicArray& operator=(const DynamicArray &da);
    T& operator[](int index);

    // Getters

    size_t getLength() const;
    size_t getCapacity() const;
    int getIndex(const std::string &unique_field1, const std::string &unique_field2) const;
    T& getElementByUniqueField(const std::string &unique_field);

    // Add, Delete, Update

    /// <summary>Adds an element in the dynamic array</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was added and False otherwise</returns
    void addElement(T &elem);

    /// <summary>Deletes an element from the dynamic array</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <returns>True if the element was deleted and False otherwise</returns
    void deleteElement(int index);

    /// <summary>Updates an element in the dynamic array</summary>
    /// <param name="title">string, the title of the movie</param>
    /// <param name="genre">int, the genre of the movie</param>
    /// <param name="year_of_release">int, the year which the movie was released in</param>
    /// <param name="nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="trailer">string, the link to the trailer of the movie</param>
    /// <returns>True if the element was updated and False otherwise</returns
    void updateElement(T &elem, int index);

private:

    // Resize

    void resizeDynamicArray(double factor = 2);
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
        throw std::string("Index out of range");
    }
    return this->list[index];
}

// Getter

template<typename T>
size_t DynamicArray<T>::getLength() const{
    return this->nr_of_elements;
}

template<typename T>
size_t DynamicArray<T>::getCapacity() const{
    return this->capacity;
}

template<typename T>
int DynamicArray<T>::getIndex(const std::string &unique_field1, const std::string &unique_field2) const{
    int index = 0;
    while (index < this->nr_of_elements){
        if (this->list[index].checkIfEqual(unique_field1, unique_field2)) {
            return index;
        }
        else {
            index += 1;
        }
    }

    return -1;
}

template<typename T>
T& DynamicArray<T>::getElementByUniqueField(const std::string &unique_field) {
    return this->list[this->getIndex(unique_field)];
}


// Add, Delete, Update

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
void DynamicArray<T>::updateElement(T &elem, int index) {
    this->list[index] = elem;
}

