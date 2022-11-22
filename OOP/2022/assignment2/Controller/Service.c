//
// Created by Alex Campean on 16.03.2022.
//

#include "Service.h"
#include <stdlib.h>
#include <string.h>

// Constructor, Destructor

Service* createService(int capacity){
    // allocate memory for the structure service
    Service* es = (Service*)malloc(sizeof(Service));

    if (es == NULL){
        return NULL;
    }

    // allocate space for the element
    es->repository = createRepository(capacity);

    if (es->repository == NULL){
        return NULL;
    }

    return es;
}

void destroyService(Service* service){
    // if service points to NULL there is nothing that needs to be freed up
    if (service == NULL){
        return;
    }

    // free the memory occupied by the repository
    destroyRepository(service->repository);
    service->repository = NULL;

    // free the memory occupied by the service
    free(service);
}

// Getters

int getServiceLength(Service* service) {
    return getRepoLength(service->repository);
}

int getServiceCapacity(Service* service) {
    return getRepoCapacity(service->repository);
}

Country* getElementInService(Service* service, int index) {
    return getElementInRepo(service->repository, index);
}

Country** getElementsInService(Service* service) {
    return getElementsInRepo(service->repository);
}

Repository* getRepository(Service* service) {
    return service->repository;
}

// Add, Delete, Update

int addElementToService(Service* service, char* name, char* continent, double population) {
    Country* newCountry = createCountry(name, continent, population);
    int return_value = addElementToRepository(service->repository, newCountry);
    // if the element has a name that is already in the repo, destroy the previously created instance
    if (return_value == 0) {
        destroyCountry(newCountry);
    }
    return return_value;
}

int deleteElementFromService(Service* service, char* name){
    return deleteElementFromRepository(service->repository, name);
}

int updateElementInService(Service* es, char* name, char* continent, double population){
    Country* newCountry = createCountry(name, continent, population);

    int returnValue = updateElementInRepository(es->repository, newCountry, 0);
    destroyCountry(newCountry);

    return returnValue;
}

int updateElementsInService(Service* es, char* name1, char* continent1, double population, char* name2, char* continent2) {
    // the country which the people are leaving from
    Country* newCountry1 = createCountry(name1, continent1, -population);
    // the country which the people are leaving to
    Country* newCountry2 = createCountry(name2, continent2, population);

    int returnValue1 = updateElementInRepository(es->repository, newCountry1, 1);
    int returnValue2 = updateElementInRepository(es->repository, newCountry2, 1);

    destroyCountry(newCountry1);
    destroyCountry(newCountry2);

    if (returnValue1 == 1 && returnValue2 == 1) {
        return 1;
    }
    return 0;
}

// Create the first 10 Elements

void populateServiceWithEntries(Service* service){
    addElementToService(service, "Brazil", "America", 212.6);
    addElementToService(service, "Chile", "America", 19.12);

    addElementToService(service, "US", "America", 329.5);
    addElementToService(service, "Canada", "America", 38.01);

    addElementToService(service, "Egypt", "Africa", 102.3);
    addElementToService(service, "Mozambique", "Africa", 31.26);

    addElementToService(service, "Portugal", "Europe", 10.31);
    addElementToService(service, "Switzerland", "Europe", 8.637);

    addElementToService(service, "Nepal", "Asia", 29.14);
    addElementToService(service, "Japan", "Asia", 125.8);
}

// Sort

void sortElementsByPopulation(Country** given_list, int size_of_list, char* option){
    Country* aux = NULL;

    for (int i = 0; i < size_of_list - 1; i++) {
        for (int j = i + 1; j < size_of_list; j++) {
            // sort increasingly
            if (strcmp(option, "1") == 0){
                if (getPopulation(given_list[i]) > getPopulation(given_list[j])) {
                    aux = given_list[i];
                    given_list[i] = given_list[j];
                    given_list[j] = aux;
                }
            }
            // sort in decreasing order
            else {
                if (getPopulation(given_list[i]) < getPopulation(given_list[j])) {
                    aux = given_list[i];
                    given_list[i] = given_list[j];
                    given_list[j] = aux;
                }
            }
        }
    }
}

// Copy

void shallowCopyListOfElements(Country** given_list, Country** new_list, int size_of_list){
    for (int i = 0; i < size_of_list; i++){
        new_list[i] = given_list[i];
    }
}

// Filter

void filterServiceByNameContainingString(Service* service, Country** given_list, int* size_of_list, char* name){
    filterRepoByNameContainingString(service->repository, given_list, size_of_list, name);
}

void filterServiceByContinent(Service* service, Country** given_list, int* size_of_list, char* continent){
    filterRepoByContinent(service->repository, given_list, size_of_list, continent);
}

void filterElementsByPopulation(Country** given_list, int* size_of_list, double population) {
    int i = 0;
    if (*size_of_list == 1){
        if (getPopulation(given_list[i]) <= population){
            given_list[i] = NULL;
            *size_of_list -= 1;
//            destroyCountry(given_list[i]);
//            *size_of_list -= 1;
        }
    }
    else {
        while (i < *size_of_list - 1) {
            if (getPopulation(given_list[i]) <= population) {
                given_list[i] = given_list[*size_of_list - 1];
                given_list[*size_of_list - 1] = NULL;
                *size_of_list -= 1;

//                destroyCountry(given_list[i]);
//                given_list[i] = copyCountry(given_list[*size_of_list - 1]);
//                destroyCountry(given_list[*size_of_list - 1]);
//                given_list[*size_of_list - 1] = NULL;
//                *size_of_list -= 1;

            } else {
                i += 1;
            }
        }
        if (getPopulation(given_list[i]) <= population) {
            given_list[i] = NULL;
            *size_of_list -= 1;

//            destroyCountry(given_list[i]);
//            given_list[i] = NULL;
//            *size_of_list -= 1;
        }
    }
}
