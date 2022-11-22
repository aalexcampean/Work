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

    da->list = (TElem**)malloc(getDaCapacity(da) * sizeof(TElem*));
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
        destroyEstate(getElementInDa(da, i));
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
        new_list[i] = copyEstate(da->list[i]);
    }

    // destroying the previous elements
    for (int i = 0; i < getDaLength(da); i++){
        destroyEstate(da->list[i]);
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

// Make Dynamic Array Deep Copy

void makeDaDeepCopy(DynamicArray* da_1, DynamicArray* da_2){
    for (int i = 0; i < getDaLength(da_2); i++){
        makeEstateDeepCopy(da_1->list[i], da_2->list[i]);
    }
}

// Copy Dynamic Array

DynamicArray* copyDynamicArray(DynamicArray* da){
    DynamicArray* new_da = createDynamicArray(getDaCapacity(da));

    for (int i = 0; i < getDaLength(da); i++){
        new_da->list[i] = copyEstate(da->list[i]);
    }
    new_da->total_elements = getDaLength(da);
    new_da->capacity = getDaCapacity(da);

    return new_da;
}

// Add, Delete, Update

int addElementInDynamicArray(DynamicArray* da, char* type, char* address, double surface, double price){
    if (searchElementInDynamicArray(da, address) == 1){
        return 0;
    }

    //creating the element
    TElem* e = createEstate(type, address, surface, price);

    if (getDaLength(da) == getDaCapacity(da)){
        resizeDynamicArray(da);
    }

    da->list[getDaLength(da)] = e;
    da->total_elements += 1;
    return 1;
}

int deleteElementFromDynamicArray(DynamicArray* da, char* adr){
    if (searchElementInDynamicArray(da, adr) == 0){
        return 0;
    }

    if (strcmp(adr, getAddress(getElementInDa(da, getDaLength(da) - 1))) != 0) {

        for (int i = 0; i < getDaLength(da); i++) {
            if (strcmp(getAddress(getElementInDa(da, i)), adr) == 0) {
                makeEstateDeepCopy(da->list[i], getElementInDa(da, getDaLength(da) - 1));
                destroyEstate(da->list[getDaLength(da) - 1]);
                break;
            }
        }
    }
    da->total_elements -= 1;
    return 1;
}

int updateElementInDynamicArray(DynamicArray* da, char* type, char* address, double surface, double price){
    if (searchElementInDynamicArray(da, address) == 0){
        return 0;
    }

    for (int i = 0; i < getDaLength(da); i++){
        if (strcmp(getAddress(getElementInDa(da, i)), address) == 0){
            setNonUniqueAttributes(getElementInDa(da, i), type, surface, price);
        }
    }
    return 1;
}

// Search

int searchElementInDynamicArray(DynamicArray* da, char* adr){
    for (int i = 0; i < getDaLength(da); i++) {
        if(strcmp(getAddress(getElementInDa(da, i)), adr) == 0) {
            return 1;
        }
    }
    return 0;
}
