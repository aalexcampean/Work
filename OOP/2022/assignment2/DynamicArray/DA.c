#include "DA.h"
#include <stdlib.h>
#include <string.h>

// Constructor, Destructor

DynamicArray* createDynamicArray(int capacity){
    // allocate memory for the structure dynamic array
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));

    if (da == NULL) {
        return NULL;
    }

    da->capacity = capacity;
    da->total_elements = 0;

    da->list = (TElem**)malloc(capacity * sizeof(TElem*));
    if (da->list == NULL) {
        return NULL;
    }

    for (int i = 0; i < capacity; i++){
        da->list[i] = NULL;
    }

    return da;
}

void destroyDynamicArray(DynamicArray* da){
    // if da points to NULL there is nothing that needs to be freed up
    if (da->list == NULL){
        return;
    }

    // free the memory occupied by the list
    for (int i = 0; i < getDaCapacity(da); i++){
        destroyCountry(getElementInDa(da, i));
    }

    free(da->list);
    da->list = NULL;

    // free the memory occupied by the dynamic array itself
    free(da);
}

// Resize

void resizeDynamicArray(DynamicArray* da){
    da->capacity *= 2;

    // allocating memory fo the new array
    TElem** new_list = (TElem**)malloc(getDaCapacity(da) * sizeof(TElem*));
    for (int i = 0; i < getDaCapacity(da); i++){
        new_list[i] = NULL;
    }

    // copping each element to its new location
    for (int i = 0; i < getDaLength(da); i++){
        new_list[i] = copyCountry(da->list[i]);
    }

    // destroying the previous elements
    for (int i = 0; i < getDaLength(da); i++){
        destroyCountry(da->list[i]);
        da->list[i] = NULL;
    }

    free(da->list);
    da->list = new_list;
}

// Getters

int getDaLength(DynamicArray* da){
    return da->total_elements;
}

int getDaCapacity(DynamicArray* da){
    return da->capacity;
}

TElem* getElementInDa(DynamicArray* da, int index){
    return da->list[index];
}

TElem** getElements(DynamicArray* da) {
    return da->list;
}

// Make Dynamic Array Deep Copy

void makeDaDeepCopy(DynamicArray* da1, DynamicArray* da2){
    for (int i = 0; i < getDaLength(da2); i++){
        makeCountryDeepCopy(da1->list[i], da2->list[i]);
    }
}

// Copy Dynamic Array

DynamicArray* copyDynamicArray(DynamicArray* da){
    DynamicArray* new_da = createDynamicArray(getDaCapacity(da));

    for (int i = 0; i < getDaLength(da); i++){
        new_da->list[i] = copyCountry(da->list[i]);
    }
    new_da->total_elements = getDaLength(da);
    new_da->capacity = getDaCapacity(da);

    return new_da;
}

// Add, Delete, Update

int addElement(DynamicArray* da, TElem* elem){
    int index = searchElementInDynamicArray(da, getName(elem));
    if (index != -1){
        return 0;
    }

//    //creating the element
//    TElem* e = createCountry(type, address, surface, price);

    if (getDaLength(da) == getDaCapacity(da)){
        resizeDynamicArray(da);
    }

    da->list[getDaLength(da)] = elem;
    da->total_elements += 1;
    return 1;
}

int deleteElement(DynamicArray* da, UniqueField field) {
    int index = searchElementInDynamicArray(da, field);
    if (index == -1){
        return 0;
    }

    if (strcmp(field, getName(getElementInDa(da, getDaLength(da) - 1))) != 0) {
        makeCountryDeepCopy(da->list[index], getElementInDa(da, getDaLength(da) - 1));
        destroyCountry(da->list[getDaLength(da) - 1]);
        da->list[getDaLength(da) - 1] = NULL;

    }
    da->total_elements -= 1;
    return 1;
}

int updateElement(DynamicArray* da, TElem* elem, int modify) {
    int index = searchElementInDynamicArray(da, getName(elem));
    if (index == -1){
        return 0;
    }

    if (modify == 0) {
        setPopulation(getElementInDa(da, index), getPopulation(elem));
    } else {
        double oldPopulation = getPopulation(getElementInDa(da, index));
        setPopulation(getElementInDa(da, index), oldPopulation + getPopulation(elem));
    }
    return 1;
}

// Search

int searchElementInDynamicArray(DynamicArray* da, UniqueField field){
    for (int i = 0; i < getDaLength(da); i++) {
        if(strcmp(getName(getElementInDa(da, i)), field) == 0) {
            return i;
        }
    }
    return -1;
}
