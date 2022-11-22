#include "Repo.h"
#include <stdlib.h>
#include <string.h>

// Constructor, Destructor

Repository* createRepository(int capacity){
    // allocate memory for the structure repository
    Repository* er = (Repository*)malloc(sizeof(Repository));

    if (er == NULL){
        return NULL;
    }

    // allocate space for the elements
    er->da = createDynamicArray(capacity);

    if (er->da == NULL){
        return NULL;
    }

    return er;
}

void destroyRepository(Repository* er){
    // if er points to NULL there is nothing that needs to be freed up
    if (er == NULL){
        return;
    }

    // free the memory occupied by the dynamic array
    destroyDynamicArray(er->da);
    er->da = NULL;

    // free the memory occupied by the repository
    free(er);
}

// Getters

int getRepoLength(Repository* er){
    return getDaLength(er->da);
}

int getRepoCapacity(Repository* er){
    return getDaCapacity(er->da);
}

TElem* getElementInRepo(Repository* er, int index){
    return getElementInDa(er->da, index);
}

// Make Repository Deep Copy

void makeRepoDeepCopy(Repository* repo_1, Repository* repo_2){
    makeDaDeepCopy(repo_1->da, repo_2->da);
}

// Copy Repository

Repository* copyRepository(Repository* er){
    Repository* new_er = createRepository(getDaCapacity(er->da));
    destroyDynamicArray(new_er->da);
    new_er->da = copyDynamicArray(er->da);

    return new_er;
}

// Add, Delete, Update

int addElementToRepository(Repository* er, char* type, char* address, double surface, double price){
    return addElementInDynamicArray(er->da, type, address, surface, price);
}

int deleteElementFromRepository(Repository* er, char* adr){
    return deleteElementFromDynamicArray(er->da, adr);
}

int updateElementInRepository(Repository* er, char* type, char* address, double surface, double price){
    return updateElementInDynamicArray(er->da, type, address, surface, price);
}

// Search

void searchElementInRepositoryByAddress(Repository* er, TElem** result_list, int* size_of_list, char* adr){
    char* result;  // what is the difference between char* s and char s[10] for example

    for (int i = 0; i < getRepoLength(er); i++){
        result = strstr(getAddress(getElementInRepo(er, i)), adr);
        if (result){
            result_list[*size_of_list] = copyEstate(getElementInRepo(er, i));
            *size_of_list += 1;
        }
    }
}

void searchElementInRepositoryByType(Repository* er, TElem** result_list, int* size_of_list, char* type){
    for (int i = 0; i < getRepoLength(er); i++) {
        if (strcmp(getType(getElementInRepo(er, i)), type) == 0) {
            result_list[*size_of_list] = copyEstate(getElementInRepo(er, i));
            *size_of_list += 1;
        }
    }


}