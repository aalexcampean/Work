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

void destroyService(Service* es){
    // if es points to NULL there is nothing that needs to be freed up
    if (es == NULL){
        return;
    }

    // free the memory occupied by the repository
    destroyRepository(es->repository);
    es->repository = NULL;

    // free the memory occupied by the service
    free(es);
}

// Getters

int getServiceLength(Service* es){
    return getRepoLength(es->repository);
}

int getServiceCapacity(Service* es){
    return getRepoCapacity(es->repository);
}

TElem* getElementInService(Service* es, int index){
    return getElementInRepo(es->repository, index);
}

// Add, Delete, Update

int addElementToService(Service* es, char* type, char* address, double surface, double price){
    return addElementToRepository(es->repository, type, address, surface, price);
}

int deleteElementFromService(Service* es, char* adr){
    return deleteElementFromRepository(es->repository, adr);
}

int updateElementInService(Service* es, char* type, char* address, double surface, double price){
    return updateElementInRepository(es->repository, type, address, surface, price);
}

// Create the first 10 Elements

void populateListWithElements(Service* es){
    addElementToService(es, "house", "Lazar_Gheorghe_19A", 80, 90000);
    addElementToService(es, "house", "Eugen_Ionesco_6", 80, 85000);
    addElementToService(es,"house", "Aurel_Vlaicu_70", 70, 59000);
    addElementToService(es,"apartment", "B-dul_21_Decembrie_5", 50, 80000);
    addElementToService(es,"apartment", "Calea_Dorobantilor_20", 70, 100000);
    addElementToService(es,"apartment", "Primaverii_9", 70, 60000);
    addElementToService(es,"apartment", "Calea_Manastur_108", 70, 65000);
    addElementToService(es,"penthouse", "Rosetti_10", 150, 250000);
    addElementToService(es,"penthouse", "Calarasilor_4", 100, 150000);
    addElementToService(es,"penthouse", "Republicii_30", 80, 120000);
}

// Search

void searchElementInServiceByAddressOrType(Service* es, TElem** result_list, int* size_of_list, char* adr_type){
    if (strcmp(adr_type, "house") != 0 && strcmp(adr_type, "apartment") != 0 && strcmp(adr_type, "penthouse") != 0){
        searchElementInRepositoryByAddress(es->repository, result_list, size_of_list, adr_type);
    }
    else {
        searchElementInRepositoryByType(es->repository, result_list, size_of_list, adr_type);
    }
}

// Sort

void sortElementsByPrice(TElem** given_list, int size_of_list, char* option){
    TElem* aux = createEstate("apartment", "NoName", 100, 100);

    for (int i = 0; i < size_of_list - 1; i++) {
        for (int j = i + 1; j < size_of_list; j++) {
            if (strcmp(option, "1") == 0){
                if (getPrice(given_list[i]) > getPrice(given_list[j])) {
                    makeEstateDeepCopy(aux, given_list[i]);
                    makeEstateDeepCopy(given_list[i], given_list[j]);
                    makeEstateDeepCopy(given_list[j], aux);
                }
            }
            else {
                if (getPrice(given_list[i]) < getPrice(given_list[j])) {
                    makeEstateDeepCopy(aux, given_list[i]);
                    makeEstateDeepCopy(given_list[i], given_list[j]);
                    makeEstateDeepCopy(given_list[j], aux);
                }
            }
        }
    }
    destroyEstate(aux);
}

void sortElementsBySurface(TElem** given_list, int size_of_list, char* option){
    TElem* aux = createEstate("apartment", "NoName", 100, 100);

    for (int i = 0; i < size_of_list - 1; i++) {
        for (int j = i + 1; j < size_of_list; j++) {
            if (strcmp(option, "1") == 0){
                if (getSurface(given_list[i]) > getSurface(given_list[j])) {
                    makeEstateDeepCopy(aux, given_list[i]);
                    makeEstateDeepCopy(given_list[i], given_list[j]);
                    makeEstateDeepCopy(given_list[j], aux);
                }
            }
            else {
                if (getSurface(given_list[i]) < getSurface(given_list[j])) {
                    makeEstateDeepCopy(aux, given_list[i]);
                    makeEstateDeepCopy(given_list[i], given_list[j]);
                    makeEstateDeepCopy(given_list[j], aux);
                }
            }
        }
    }
    destroyEstate(aux);
    aux = NULL;
}

// Copy

void copyListOfElements(TElem** given_list, TElem** new_list, int size_of_list){
    for (int i = 0; i < size_of_list; i++){
        new_list[i] = copyEstate(given_list[i]);
    }
}

// Filter

void filterElementsBySurface(TElem** given_list, int* size_of_list, double given_surface){
    int i = 0;
    if (*size_of_list == 1){
        if (getSurface(given_list[i]) < given_surface){
            destroyEstate(given_list[i]);
            *size_of_list -= 1;
        }
    }
    else {
        while (i < *size_of_list - 1) {
            if (getSurface(given_list[i]) < given_surface) {
                destroyEstate(given_list[i]);
                given_list[i] = copyEstate(given_list[*size_of_list - 1]);
                destroyEstate(given_list[*size_of_list - 1]);
                given_list[*size_of_list - 1] = NULL;
//                makeEstateDeepCopy(given_list[i], given_list[*size_of_list - 1]);
                *size_of_list -= 1;

            } else {
                i += 1;
            }
        }
        if (getSurface(given_list[i]) < given_surface) {
            destroyEstate(given_list[i]);
            given_list[i] = NULL;
            *size_of_list -= 1;

        }
    }
}

void filterElementsByPrice(TElem** given_list, int* size_of_list, double given_price){
    int i = 0;
    if (*size_of_list != 1){
        while (i < *size_of_list - 1) {
            if (getPrice(given_list[i]) != given_price) {
                makeEstateDeepCopy(given_list[i], given_list[*size_of_list - 1]);
                *size_of_list -= 1;

            } else {
                i += 1;
            }
        }
    }
    if (getPrice(given_list[i]) != given_price){
        *size_of_list -= 1;
    }
}
