#include "Tests.h"
#include <string.h>
#include <assert.h>

void testAll(){
//    testDomain();
//    testDynamicArray();
//    testRepository();
//    testService();
//    testUndoService();
}

void testDomain(){
    Estate* aux_estate = createEstate("house", "Carierei_de_piatra_10", 100, 140000);

    assert(strcmp(getType(aux_estate), "house") == 0);
    assert(strcmp(getAddress(aux_estate), "Carierei_de_piatra_10") == 0);
    assert(getSurface(aux_estate) == 100);
    assert(getPrice(aux_estate) == 140000);

    destroyEstate(aux_estate);
}

void testDynamicArray(){
    DynamicArray* aux_da = createDynamicArray(3);

    assert(getDaLength(aux_da) == 0);
    assert(getDaCapacity(aux_da) == 3);

    // Test Add

    addElementInDynamicArray(aux_da, "penthouse", "Rosetti_10", 150, 250000);
    assert(getDaLength(aux_da) == 1);

    addElementInDynamicArray(aux_da, "house", "Lazar_Gheorghe_19A", 80, 90000);
    assert(getDaLength(aux_da) == 2);

    addElementInDynamicArray(aux_da, "apartment", "Calea_Dorobantilor_20", 70, 100000);
    assert(getDaLength(aux_da) == 3);

    addElementInDynamicArray(aux_da, "apartment", "Primaverii_9", 70, 60000);
    // now a resize should have happened
    assert(getDaCapacity(aux_da)== 6);

    // Test Update

    updateElementInDynamicArray(aux_da, "penthouse", "Rosetti_10", 90, 200000);

    // check if the update has been done correctly
    assert(strcmp(getType(aux_da->list[0]), "penthouse") == 0);
    assert(getSurface(aux_da->list[0]) == 90);
    assert(getPrice(aux_da->list[0]) == 200000);
    assert(getDaLength(aux_da) == 4);

    // Test Delete

    deleteElementFromDynamicArray(aux_da, "Rosetti_10");

    // check if the delete has been done correctly
    assert(getDaLength(aux_da) == 3);
    assert(searchElementInDynamicArray(aux_da, "Rosetti_10") == 0);

    destroyDynamicArray(aux_da);
}
void testRepository(){
    Repository* aux_repo = createRepository(10);
    assert(getRepoLength(aux_repo) == 0);

    // Test Add

    addElementToRepository(aux_repo, "penthouse", "Rosetti_10", 150, 250000);
    assert(getRepoLength(aux_repo) == 1);

    addElementToRepository(aux_repo, "apartment", "Calea_Dorobantilor_20", 70, 100000);
    assert(getRepoLength(aux_repo) == 2);

    addElementToRepository(aux_repo, "house", "Lazar_Gheorghe_19A", 80, 90000);
    assert(getRepoLength(aux_repo) == 3);

    // this should not be added as it has an address that is already in the repository
    addElementToRepository(aux_repo, "apartment", "Calea_Dorobantilor_20", 70, 100000);
    assert(getRepoLength(aux_repo) == 3);

    addElementToRepository(aux_repo, "apartment", "Primaverii_9", 70, 60000);
    assert(getRepoLength(aux_repo) == 4);

    // Test Update

    updateElementInRepository(aux_repo, "penthouse", "No_Address", 90, 200000);

    // the update shouldn't be done as the given address does not exist
    assert(strcmp(getType(getElementInRepo(aux_repo, 0)), "penthouse") == 0);
    assert(getSurface(getElementInRepo(aux_repo, 0)) == 150);
    assert(getPrice(getElementInRepo(aux_repo, 0)) == 250000);
    assert(getRepoLength(aux_repo) == 4);

    // Test Delete

    deleteElementFromRepository(aux_repo, "Rosetti_10");

    // check if the delete has been done correctly
    assert(getRepoLength(aux_repo) == 3);
    assert(searchElementInDynamicArray(aux_repo->da, "Rosetti_10") == 0);

    deleteElementFromRepository(aux_repo, "No_Address");

    // the delete shouldn't be done as the given address doesn't exist
    assert(getRepoLength(aux_repo) == 3);

    // Test Search By Address

    Estate* aux_list[aux_repo->da->total_elements];
    int aux_size_of_list = 0;

    searchElementInRepositoryByAddress(aux_repo, aux_list, &aux_size_of_list, "i");
    assert(aux_size_of_list == 2);

    // Test Search By Type

    Estate* aux_list_2[aux_repo->da->total_elements];
    int aux_size_of_list_2 = 0;

    searchElementInRepositoryByType(aux_repo, aux_list_2, &aux_size_of_list_2, "house");
    assert(aux_size_of_list_2 == 1);

    destroyRepository(aux_repo);
}
void testService(){
    Service* aux_service = createService(10);
    assert(getServiceLength(aux_service) == 0);

    // Test Add

    addElementToService(aux_service, "penthouse", "Rosetti_10", 150, 250000);
    assert(getServiceLength(aux_service) == 1);

    addElementToService(aux_service, "apartment", "Calea_Dorobantilor_20", 70, 100000);
    assert(getServiceLength(aux_service) == 2);

    addElementToService(aux_service, "house", "Lazar_Gheorghe_19A", 80, 90000);
    assert(getServiceLength(aux_service) == 3);

    // this should not be added as it has an address that is already in the repository
    addElementToService(aux_service, "apartment", "Calea_Dorobantilor_20", 70, 100000);
    assert(getServiceLength(aux_service) == 3);

    addElementToService(aux_service, "apartment", "Primaverii_9", 70, 60000);
    assert(getServiceLength(aux_service) == 4);

    // Test Update

    updateElementInService(aux_service, "penthouse", "No_Address", 90, 200000);

    // the update shouldn't be done as the given address does not exist
    assert(strcmp(getType(getElementInService(aux_service, 0)), "penthouse") == 0);
    assert(getSurface(getElementInService(aux_service, 0)) == 150);
    assert(getPrice(getElementInService(aux_service, 0)) == 250000);
    assert(getServiceLength(aux_service) == 4);

    // Test Delete

    deleteElementFromService(aux_service, "Rosetti_10");

    // check if the delete has been done correctly
    assert(getServiceLength(aux_service) == 3);
    assert(searchElementInDynamicArray(aux_service->repository->da, "Rosetti_10") == 0);

    deleteElementFromService(aux_service, "No_Address");

    // the delete shouldn't be done as the given address doesn't exist
    assert(getServiceLength(aux_service) == 3);

    // Test Search By Address

    Estate* aux_list[getServiceLength(aux_service)];
    int aux_size_of_list = 0;

    searchElementInRepositoryByAddress(aux_service->repository, aux_list, &aux_size_of_list, "i");
    assert(aux_size_of_list == 2);

    // Test Search By Type

    Estate* aux_list_2[getServiceLength(aux_service)];
    int aux_size_of_list_2 = 0;

    searchElementInRepositoryByType(aux_service->repository, aux_list_2, &aux_size_of_list_2, "house");
    assert(aux_size_of_list_2 == 1);

    // Populating the list with 10 elements

    // the list already contains 3 addresses found in these 10 so the length should be 10
    populateListWithElements(aux_service);
    assert(getServiceLength(aux_service) == 10);

    // Test Sort By Price

    sortElementsByPrice(aux_service->repository->da->list, getServiceLength(aux_service), "1");
    // checking if the first element has the lowest price and the last one has the highest one
    assert(getPrice(getElementInService(aux_service, 0)) == 59000);
    assert(getPrice(getElementInService(aux_service, getServiceLength(aux_service) -1)) == 250000);

    // Test Sort By Surface

    // ascending order
    sortElementsBySurface(aux_service->repository->da->list, getServiceLength(aux_service), "1");
    // checking if the first element has the smallest surface and the last one has the greatest one
    assert(getSurface(getElementInService(aux_service, 0)) == 50);
    assert(getSurface(getElementInService(aux_service, getServiceLength(aux_service) -1)) == 150);

    // descending order
    sortElementsBySurface(aux_service->repository->da->list, getServiceLength(aux_service), "2");
    // checking if the first element has the greatest surface and the last one has the smallest one
    assert(getSurface(getElementInService(aux_service, 0)) == 150);
    assert(getSurface(getElementInService(aux_service, getServiceLength(aux_service) -1)) == 50);

    // Test Copy List

    Estate* aux_list_3[getServiceLength(aux_service)];
    int aux_size_of_list_3 = getServiceLength(aux_service);

    copyListOfElements(aux_service->repository->da->list, aux_list_3, aux_size_of_list_3);
    // check if all elements were copied correctly
    for (int i = 0; i < aux_size_of_list_3; i++){
        assert(strcmp(getType(aux_list_3[i]), getType(getElementInService(aux_service, i))) == 0);
        assert(strcmp(getAddress(aux_list_3[i]), getAddress(getElementInService(aux_service, i))) == 0);
        assert(getSurface(aux_list_3[i]) == getSurface(getElementInService(aux_service, i)));
        assert(getPrice(aux_list_3[i]) == getPrice(getElementInService(aux_service, i)));
    }

    // Test Filter Elements By Surface (over a given surface)
    filterElementsBySurface(aux_list_3, &aux_size_of_list_3, 80);

    // there should be 5 estates with the surface grater that 80
    assert(aux_size_of_list_3 == 5);

    Estate* aux_list_4[getServiceLength(aux_service)];
    int aux_size_of_list_4 = getServiceLength(aux_service);

    copyListOfElements(aux_service->repository->da->list, aux_list_4, aux_size_of_list_4);
    // Test Filter Elements By price (over a given surface)
    filterElementsByPrice(aux_list_4, &aux_size_of_list_4, 90000);

    // there should be 5 estates with the surface grater that 80
    assert(aux_size_of_list_4 == 1);

    destroyService(aux_service);
}
void testUndoService(){
    Service* aux_service = createService(10);
    UndoService* aux_undo_service = createUndoService(10);

    // Test first addition to history
    populateListWithElements(aux_service);
    addOperationToHistory(aux_undo_service, aux_service->repository);
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "penthouse") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Republicii_30") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 80);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 120000);


    // Test add functionality

    addElementToService(aux_service, "penthouse", "Macesilor_9", 100, 100000);
    addOperationToHistory(aux_undo_service, aux_service->repository);

    // check if the add was done correctly
    // current state
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "penthouse") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Macesilor_9") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 100);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 100000);


    undoOperation(aux_undo_service, aux_service->repository);
    // state after undo
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "penthouse") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Republicii_30") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 80);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 120000);

    redoOperation(aux_undo_service, aux_service->repository);
    // state after redo
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "penthouse") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Macesilor_9") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 100);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 100000);
    // Test delete functionality

    deleteElementFromService(aux_service, "Macesilor_9");
    addOperationToHistory(aux_undo_service, aux_service->repository);
    // current state
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "penthouse") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Republicii_30") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 80);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 120000);

    undoOperation(aux_undo_service, aux_service->repository);
    // state after undo
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "penthouse") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Macesilor_9") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 100);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 100000);

    redoOperation(aux_undo_service, aux_service->repository);
    // state after redo
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "penthouse") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Republicii_30") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 80);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 120000);

    // Test update functionality

    updateElementInService(aux_service, "house", "Republicii_30", 120, 300000);
    addOperationToHistory(aux_undo_service, aux_service->repository);
    // current state
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "house") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Republicii_30") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 120);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 300000);

    undoOperation(aux_undo_service, aux_service->repository);
    // state after undo
    assert(strcmp(getType(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]), "penthouse") == 0);
    assert(strcmp(getAddress(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]), "Republicii_30") == 0);
    assert(getSurface(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]) == 80);
    assert(getPrice(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]) == 120000);

    redoOperation(aux_undo_service, aux_service->repository);
    // state after redo
    assert(strcmp(getType(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "house") == 0);
    assert(strcmp(getAddress(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))), "Republicii_30") == 0);
    assert(getSurface(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 120);
    assert(getPrice(getElementInRepo(aux_undo_service->history[getUsIndex(aux_undo_service)], getRepoLength(aux_undo_service->history[getUsIndex(aux_undo_service)] - 1))) == 300000);

    undoOperation(aux_undo_service, aux_service->repository);
    // state after undo
    assert(strcmp(getType(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]), "penthouse") == 0);
    assert(strcmp(getAddress(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]), "Republicii_30") == 0);
    assert(getSurface(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]) == 80);
    assert(getPrice(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]) == 120000);

    deleteElementFromService(aux_service, "Republicii_30");
    addOperationToHistory(aux_undo_service, aux_service->repository);
    // current state
    assert(strcmp(getType(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]), "penthouse") == 0);
    assert(strcmp(getAddress(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]), "Calarasilor_4") == 0);
    assert(getSurface(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]) == 100);
    assert(getPrice(aux_undo_service->history[getUsIndex(aux_undo_service)]->da->list[getDaLength(aux_undo_service->history[getUsIndex(aux_undo_service)]->da) - 1]) == 150000);

    // added an operation after undo and therefore there should be no more redos
    assert(redoOperation(aux_undo_service, aux_service->repository) == 0);

    destroyService(aux_service);
    destroyUndoService(aux_undo_service);
}


