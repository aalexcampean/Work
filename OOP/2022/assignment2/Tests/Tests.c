//
// Created by Alex Campean on 16.03.2022.
//

#include <assert.h>
#include <string.h>
#include "Tests.h"
#include "../Controller/Service.h"
#include "../Controller/UndoService.h"

void testAll() {
    testDomain();
    testDynamicArray();
    testRepository();
    testService();
    testUndoService();
}

void testDomain() {
    Country* aux_country = createCountry("Romania", "Europe", 19.29);

    assert(strcmp(getName(aux_country), "Romania") == 0);
    assert(strcmp(getContinent(aux_country), "Europe") == 0);
    assert(getPopulation(aux_country) == 19.29);

    Country* aux_country_copy = copyCountry(aux_country);
    assert(strcmp(getName(aux_country_copy), "Romania") == 0);
    assert(strcmp(getContinent(aux_country_copy), "Europe") == 0);
    assert(getPopulation(aux_country_copy) == 19.29);

    destroyCountry(aux_country);
    destroyCountry(aux_country_copy);
}

void testDynamicArray(){
    DynamicArray* aux_da = createDynamicArray(3);

    assert(getDaLength(aux_da) == 0);
    assert(getDaCapacity(aux_da) == 3);

    // Test Add

    Country* romania = createCountry("Romania", "Europe", 19.29);
    addElement(aux_da, romania);
    assert(getDaLength(aux_da) == 1);

    Country* hungary = createCountry("Hungary", "Europe", 9.75);
    addElement(aux_da, hungary);
    assert(getDaLength(aux_da) == 2);

    Country* france = createCountry("France", "Europe", 67.39);
    addElement(aux_da, france);
    assert(getDaLength(aux_da) == 3);

    Country* indonesia = createCountry("Indonesia", "Asia", 273.5);
    addElement(aux_da, indonesia);

    // now a resize should have happened
    assert(getDaCapacity(aux_da)== 6);

    // Test Update

    Country* romania_updated = createCountry("Romania", "Europe", 19.31);
    updateElement(aux_da, romania_updated, 0);
    destroyCountry(romania_updated);


    // check if the update has been done correctly
    assert(getPopulation(aux_da->list[0]) == 19.31);
    assert(getDaLength(aux_da) == 4);

    // Test Delete

    deleteElement(aux_da, "France");

    // check if the deletion has been done correctly
    assert(getDaLength(aux_da) == 3);
    assert(searchElementInDynamicArray(aux_da, "France") == -1);

    destroyDynamicArray(aux_da);
}

void testRepository(){
    Repository* aux_repo = createRepository(10);
    assert(getRepoLength(aux_repo) == 0);

    // Test Add

    Country* romania = createCountry("Romania", "Europe", 19.29);
    addElementToRepository(aux_repo, romania);
    assert(getRepoLength(aux_repo) == 1);

    Country* bolivia = createCountry("Bolivia", "America", 11.67);
    addElementToRepository(aux_repo, bolivia);
    assert(getRepoLength(aux_repo) == 2);

    Country* nigeria = createCountry("Nigeria", "Africa", 206.1);
    addElementToRepository(aux_repo, nigeria);
    assert(getRepoLength(aux_repo) == 3);

    // this should not be added as it has a name that is already in the repository
    Country* bolivia2 = createCountry("Bolivia", "America", 11.67);
    addElementToRepository(aux_repo, bolivia2);
    assert(getRepoLength(aux_repo) == 3);
    destroyCountry(bolivia2);

    Country* indonesia = createCountry("Indonesia", "Asia", 273.5);
    addElementToRepository(aux_repo, indonesia);
    assert(getRepoLength(aux_repo) == 4);

    // Test Update

    Country* morocco = createCountry("Morocco", "Africa", 36.91);
    updateElementInRepository(aux_repo, morocco, 0);
    destroyCountry(morocco);

    // the update shouldn't be done as the given address does not exist
    assert(getPopulation(getElementInRepo(aux_repo, 0)) == 19.29);
    assert(getPopulation(getElementInRepo(aux_repo, 1)) == 11.67);
    assert(getPopulation(getElementInRepo(aux_repo, 2)) == 206.1);
    assert(getPopulation(getElementInRepo(aux_repo, 3)) == 273.5);
    assert(getRepoLength(aux_repo) == 4);

    // Test Delete

    deleteElementFromRepository(aux_repo, "Romania");

    // check if the delete has been done correctly
    assert(getRepoLength(aux_repo) == 3);
    assert(searchCountryByNameInRepo(aux_repo, "Romania") == -1);

    deleteElementFromRepository(aux_repo, "Malta");

    // the delete shouldn't be done as the given address doesn't exist
    assert(getRepoLength(aux_repo) == 3);

    // Test Search By Name

    Country* aux_list[getRepoLength(aux_repo)];
    int aux_size_of_list = 0;

    filterRepoByNameContainingString(aux_repo, aux_list, &aux_size_of_list, "ia");
    assert(aux_size_of_list == 3);

    // Test Search By Continent

    Country* aux_list2[getRepoLength(aux_repo)];
    int aux_size_of_list2 = 0;

    filterRepoByContinent(aux_repo, aux_list2, &aux_size_of_list2, "Asia");
    assert(aux_size_of_list2 == 1);


    destroyRepository(aux_repo);
}

void testService(){
    Service* aux_service = createService(10);
    assert(getServiceLength(aux_service) == 0);

    // Test Add

    addElementToService(aux_service, "Romania", "Europe", 19.29);
    assert(getServiceLength(aux_service) == 1);

    addElementToService(aux_service, "Bolivia", "America", 11.67);
    assert(getServiceLength(aux_service) == 2);

    addElementToService(aux_service, "Brazil", "America", 212.6);
    assert(getServiceLength(aux_service) == 3);

    // this should not be added as it has an address that is already in the repository
    addElementToService(aux_service, "Bolivia", "America", 12);
    assert(getServiceLength(aux_service) == 3);

    addElementToService(aux_service, "Japan", "Asia", 125.8);
    assert(getServiceLength(aux_service) == 4);

    // Test Update

    updateElementInService(aux_service, "Switzerland", "Europe", 8.637);

    // the update shouldn't be done as the given address does not exist
    assert(getPopulation(getElementInService(aux_service, 0)) == 19.29);
    assert(getPopulation(getElementInService(aux_service, 1)) == 11.67);
    assert(getPopulation(getElementInService(aux_service, 2)) == 212.6);
    assert(getPopulation(getElementInService(aux_service, 3)) == 125.8);
    assert(getServiceLength(aux_service) == 4);

    // the update should be successful
    updateElementInService(aux_service, "Romania", "Europe", 20);
    assert(getPopulation(getElementInService(aux_service, 0)) == 20);

    // Test Delete

    deleteElementFromService(aux_service, "Romania");

    // check if the delete has been done correctly
    assert(getServiceLength(aux_service) == 3);
    assert(searchCountryByNameInRepo(aux_service->repository, "Romania") == -1);

    deleteElementFromService(aux_service, "LoremIpsum");

    // the delete shouldn't be done as the given address doesn't exist
    assert(getServiceLength(aux_service) == 3);

    // Test Filter By Name containing string

    Country* aux_list[getServiceLength(aux_service)];
    int aux_size_of_list = 0;

    filterServiceByNameContainingString(aux_service, aux_list, &aux_size_of_list, "a");
    assert(aux_size_of_list == 3);

    // Test Filter By continent

    Country * aux_list2[getServiceLength(aux_service)];
    int aux_size_of_list_2 = 0;

    filterServiceByContinent(aux_service, aux_list2, &aux_size_of_list_2, "America");
    assert(aux_size_of_list_2 == 2);

    // Populating the list with 10 elements

    // the list already contains 2 countries found in these 10 so the length should be 11
    populateServiceWithEntries(aux_service);
    assert(getServiceLength(aux_service) == 11);

    // Test Sort By Population

    // ascending order
    sortElementsByPopulation(getElementsInService(aux_service), getServiceLength(aux_service), "1");
    // checking if the first element has the smallest surface and the last one has the greatest one
    assert(getPopulation(getElementInService(aux_service, 0)) == 8.637);
    assert(getPopulation(getElementInService(aux_service, getServiceLength(aux_service) -1)) == 329.5);

    // descending order
    sortElementsByPopulation(getElementsInService(aux_service), getServiceLength(aux_service), "2");
    // checking if the first element has the greatest surface and the last one has the smallest one
    assert(getPopulation(getElementInService(aux_service, 0)) == 329.5);
    assert(getPopulation(getElementInService(aux_service, getServiceLength(aux_service) -1)) == 8.637);

    // Test Copy List

    Country* aux_list3[getServiceLength(aux_service)];
    int aux_size_of_list3 = getServiceLength(aux_service);

    shallowCopyListOfElements(getElementsInService(aux_service), aux_list3, aux_size_of_list3);
    // check if all elements were copied correctly
    for (int i = 0; i < aux_size_of_list3; i++){
        assert(strcmp(getName(aux_list3[i]), getName(getElementInService(aux_service, i))) == 0);
        assert(strcmp(getContinent(aux_list3[i]), getContinent(getElementInService(aux_service, i))) == 0);
        assert(getPopulation(aux_list3[i]) == getPopulation(getElementInService(aux_service, i)));
    }

    // Test Filter Elements By Population (over a given surface)
    filterElementsByPopulation(aux_list3, &aux_size_of_list3, 19.12);

    // there should be 7 countries with the population grater that 19.12
    assert(aux_size_of_list3 == 7);

    destroyService(aux_service);
}

void testUndoService(){
    Service* aux_service = createService(10);
    UndoService* aux_undo_service = createUndoService(10);

    // Test first addition to history
    populateServiceWithEntries(aux_service);
    addOperationToHistory(aux_undo_service, getRepository(aux_service));
    Repository* current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Japan") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Asia") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 125.8);

    // Test add functionality

    addElementToService(aux_service, "Spain", "Europe", 47.35);
    addOperationToHistory(aux_undo_service, getRepository(aux_service));

    // check if the add was done correctly
    // current state
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Spain") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Europe") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 47.35);

    aux_service->repository = undoOperation(aux_undo_service, getRepository(aux_service));
    // state after undo
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Japan") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Asia") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 125.8);

    aux_service->repository = redoOperation(aux_undo_service, getRepository(aux_service));
    // state after redo
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Spain") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Europe") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 47.35);

    // Test delete functionality

    deleteElementFromService(aux_service, "Spain");
    addOperationToHistory(aux_undo_service, getRepository(aux_service));
    // current state
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Japan") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Asia") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 125.8);

    aux_service->repository = undoOperation(aux_undo_service, getRepository(aux_service));
    // state after undo
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Spain") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Europe") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 47.35);

    aux_service->repository = redoOperation(aux_undo_service, getRepository(aux_service));
    // state after redo
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Japan") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Asia") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 125.8);

    // Test update functionality

    updateElementInService(aux_service, "Japan", "Asia", 124);
    addOperationToHistory(aux_undo_service, getRepository(aux_service));
    // current state
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 124);

    aux_service->repository = undoOperation(aux_undo_service, getRepository(aux_service));
    // state after undo
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 125.8);

    aux_service->repository = redoOperation(aux_undo_service, getRepository(aux_service));
    // state after redo
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 124);

    aux_service->repository = undoOperation(aux_undo_service, getRepository(aux_service));
    // state after undo
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 125.8);

    deleteElementFromService(aux_service, "Japan");
    addOperationToHistory(aux_undo_service, getRepository(aux_service));
    // current state
    current_repo = getRepositoryAtPosition(aux_undo_service, getUndoServiceIndex(aux_undo_service));
    assert(strcmp(getName(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Nepal") == 0);
    assert(strcmp(getContinent(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)), "Asia") == 0);
    assert(getPopulation(getElementInRepo(current_repo, getRepoLength(current_repo) - 1)) == 29.14);

    // added an operation after undo and therefore there should be no more redos
    Repository* return_value = redoOperation(aux_undo_service, getRepository(aux_service));
    assert(return_value == NULL);

    destroyService(aux_service);
    destroyUndoService(aux_undo_service);
}