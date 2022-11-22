//
// Created by Alex Campean on 16.03.2022.
//

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

void destroyRepository(Repository* repository){
    // if repository points to NULL there is nothing that needs to be freed up
    if (repository == NULL){
        return;
    }

    // free the memory occupied by the dynamic array
    destroyDynamicArray(repository->da);
    repository->da = NULL;

    // free the memory occupied by the repository
    free(repository);
}

// Getters

int getRepoLength(Repository* repository){
    return getDaLength(repository->da);
}

int getRepoCapacity(Repository* repository){
    return getDaCapacity(repository->da);
}

Country* getElementInRepo(Repository* repository, int index){
    return getElementInDa(repository->da, index);
}

Country** getElementsInRepo(Repository* repository) {
    return getElements(repository->da);
}

// Make Repository Deep Copy

void makeRepoDeepCopy(Repository* repo1, Repository* repo2){
    makeDaDeepCopy(repo1->da, repo2->da);
}

// Copy Repository

Repository* copyRepository(Repository* repository){
    Repository* new_er = createRepository(getDaCapacity(repository->da));
    destroyDynamicArray(new_er->da);
    new_er->da = copyDynamicArray(repository->da);

    return new_er;
}

// Add, Delete, Update

int addElementToRepository(Repository* repository, Country* country){
    return addElement(repository->da, country);
}

int deleteElementFromRepository(Repository* repository, char* adr){
    return deleteElement(repository->da, adr);
}

int updateElementInRepository(Repository* repository, Country* country, int modify){
    return updateElement(repository->da, country, modify);
}

// Search

int searchCountryByNameInRepo(Repository* repository, char* name) {
    return searchElementInDynamicArray(repository->da, name);
}

void filterRepoByNameContainingString(Repository* repository, Country** result_list, int* size_of_list, char* name){
    char* result;

    for (int i = 0; i < getRepoLength(repository); i++){
        result = strstr(getName(getElementInRepo(repository, i)), name);
        if (result){
            result_list[*size_of_list] = getElementInRepo(repository, i);
//            result_list[*size_of_list] = copyCountry(getElementInRepo(repository, i));
            *size_of_list += 1;
        }
    }
}

void filterRepoByContinent(Repository* repository, Country** result_list, int* size_of_list, char* continent){
    char* result;

    for (int i = 0; i < getRepoLength(repository); i++){
        result = strstr(getContinent(getElementInRepo(repository, i)), continent);
        if (result){
            result_list[*size_of_list] = getElementInRepo(repository, i);
//            result_list[*size_of_list] = copyCountry(getElementInRepo(repository, i));
            *size_of_list += 1;
        }
    }
}


