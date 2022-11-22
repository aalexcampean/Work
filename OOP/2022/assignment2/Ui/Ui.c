//
// Created by Alex Campean on 16.03.2022.
//
#include "Ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constructor, Destructor

UserInterface* createUserInterface(){
    // allocate memory for the structure user interface
    UserInterface* ui = (UserInterface*)malloc(sizeof(UserInterface));

    if (ui == NULL){
        return NULL;
    }

    char string[10];
    int capacity;

    printf("The initial capacity of the list of Countries:\n");
    scanf("%s", string);

    capacity = atoi(string);

    if (capacity == 0){
        printf("Invalid input(must be an integer number)\n");
    }
    // allocate space for the elements
    ui->service = createService(capacity);
    if (ui->service == NULL){
        return NULL;
    }

    ui->undoService = createUndoService(capacity);
    if (ui->undoService == NULL){
        return NULL;
    }

    return ui;
}

void destroyUserInterface(UserInterface* ui){
    // if ui points to NULL there is nothing that needs to be freed up
    if (ui == NULL){
        return;
    }

    // free the memory occupied by the service
    destroyService(ui->service);
    ui->service = NULL;

    // free the memory occupied by the undoService
    destroyUndoService(ui->undoService);
    ui->undoService = NULL;

    // free the memory occupied by the user interface
    free(ui);
    ui = NULL;
}

// Add, Delete, Update

void addFunctionalityUi(UserInterface* ui){
    char input_name[20];
    char input_continent[50];
    char input_population[20];

    double validated_population;

    char *ptr;
    double result;

    printf("Country Name: ");
    scanf("%s", input_name);

    // validating the name
    if (strcmp(input_name, "") == 0){
        printf("Name field cannot be empty\n");
        return;
    }

    printf("Continent: ");
    scanf("%s", input_continent);

    // validating the continent
    if (strcmp(input_continent, "Europe") != 0 && strcmp(input_continent, "Africa") != 0 && strcmp(input_continent, "Asia") != 0 && strcmp(input_continent, "South America") != 0  && strcmp(input_continent, "North America") != 0 && strcmp(input_continent, "Australia") != 0){
        printf("Invalid continent(choose from: Europe | Africa | Asia | South America | North America | Australia)\n");
        return;
    }

    printf("Population: ");
    scanf("%s", input_population);

    // validating the population
    result = strtod(input_population, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid population(must be floating point number)\n");
        return;
    }
    validated_population = result;

    int b = addElementToService(ui->service, input_name, input_continent, validated_population);

    if (b == 1){
        addOperationToHistory(ui->undoService, ui->service->repository);
    }
    else {
        printf("Country already exists\n");
    }
}

void deleteFunctionalityUi(UserInterface* ui){
    char input_name[50];

    printf("Country Name: ");
    scanf("%s", input_name);

    // validating the name
    if (strcmp(input_name, "") == 0){
        printf("Name field cannot be empty\n");
        return;
    }

    int b = deleteElementFromService(ui->service, input_name);

    if (b == 1){
        addOperationToHistory(ui->undoService, ui->service->repository);
    }
    else {
        printf("Country not found\n");
    }
}

void updateFunctionalityUi(UserInterface* ui){
    char option[10];

    printf("1. Updating the population of a country\n");
    printf("2. Treating a case of migration from a country to another\n");
    printf("What do you want to do?\n");
    scanf("%s", option);

    // validating way of sorting
    if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0){
        printf("Invalid way of sorting\n");
        return;
    }

    if (strcmp(option, "1") == 0) {
        updateCountryPopulation(ui);
    } else {
        handleMigration(ui);
    }
}

void updateCountryPopulation(UserInterface* ui) {
    char input_name[20];
    char input_continent[50];
    char input_population[20];

    double validated_population;

    char *ptr;
    double result;

    printf("Country Name: ");
    scanf("%s", input_name);

    // validating the name
    if (strcmp(input_name, "") == 0){
        printf("Name field cannot be empty\n");
        return;
    }

    printf("Continent: ");
    scanf("%s", input_continent);

    // validating the continent
    if (strcmp(input_continent, "Europe") != 0 && strcmp(input_continent, "Africa") != 0 && strcmp(input_continent, "Asia") != 0 && strcmp(input_continent, "America") != 0 && strcmp(input_continent, "Australia") != 0){
        printf("Invalid continent(choose from: Europe | Africa | Asia | America | Australia)\n");
        return;
    }

    printf("Population: ");
    scanf("%s", input_population);

    // validating the population
    result = strtod(input_population, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid population(must be floating point number)\n");
        return;
    }
    validated_population = result;

    int b = updateElementInService(ui->service, input_name, input_continent, validated_population);

    if (b == 1){
        addOperationToHistory(ui->undoService, ui->service->repository);
    }
    else {
        printf("Country not found");
    }
}

void handleMigration(UserInterface* ui) {
    char input_name1[20];
    char input_continent1[50];
    char help;

    char input_name2[20];
    char input_continent2[50];

    char input_population[20];

    double validated_population;

    char *ptr;
    double result;

    printf("Home Country Name: ");
    scanf("%s", input_name1);

    // validating the name
    if (strcmp(input_name1, "") == 0){
        printf("Name field cannot be empty\n");
        return;
    }

    printf("Home Country Continent: ");
    scanf("%s", input_continent1);

    // validating the continent
    if (strcmp(input_continent1, "Europe") != 0 && strcmp(input_continent1, "Africa") != 0 && strcmp(input_continent1, "Asia") != 0 && strcmp(input_continent1, "America") != 0 && strcmp(input_continent1, "Australia") != 0){
        printf("Invalid continent(choose from: Europe | Africa | Asia | America | Australia)\n");
        return;
    }

    printf("Leaving Population: ");
    scanf("%s", input_population);

    // validating the population
    result = strtod(input_population, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid population(must be floating point number)\n");
        return;
    }
    validated_population = result;

    printf("Destination Country Name: ");
    scanf("%s", input_name2);

    // validating the name
    if (strcmp(input_name2, "") == 0){
        printf("Name field cannot be empty\n");
        return;
    }

    printf("Destination Country Continent: ");
    scanf("%s", input_continent2);

    // validating the continent
    if (strcmp(input_continent2, "Europe") != 0 && strcmp(input_continent2, "Africa") != 0 && strcmp(input_continent2, "Asia") != 0 && strcmp(input_continent2, "America") != 0 && strcmp(input_continent2, "Australia") != 0){
        printf("Invalid continent(choose from: Europe | Africa | Asia | America | Australia)\n");
        return;
    }

    int b = updateElementsInService(ui->service, input_name1, input_continent1, validated_population, input_name2, input_continent2);

    if (b == 1){
        addOperationToHistory(ui->undoService, ui->service->repository);
    }
    else {
        printf("Countries not found");
    }
}

// Filter

void filterByNameContainingStringUi(UserInterface* ui){
    char input_name[50];
    char help;

    printf("Name:");
    scanf("%c", &help);
    fgets(input_name, sizeof(input_name), stdin);

    TElem** result_list = (TElem**)malloc(getServiceCapacity(ui->service) * sizeof(TElem*));
    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        result_list[i] = NULL;
    }

    if (input_name[0] == '\n') {
        printListOfElements(getElementsInRepo(getRepository(ui->service)), getServiceLength(ui->service));

    } else {
        input_name[strlen(input_name) - 1] = '\0';
        int size_of_list = 0;

        filterServiceByNameContainingString(ui->service, result_list, &size_of_list, input_name);
        printListOfElements(result_list, size_of_list);
    }

    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        if (result_list[i] != NULL) {
            result_list[i] = NULL;
        }
    }
    free(result_list);
    result_list = NULL;
}

void filterByContinentUi(UserInterface* ui){
    char input_continent[50];
    char help;

    printf("Continent:");
    scanf("%c", &help);
    fgets(input_continent, sizeof(input_continent), stdin);

    int size_of_list = 0;
    TElem** result_list = (TElem**)malloc(getServiceCapacity(ui->service) * sizeof(TElem*));
    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        result_list[i] = NULL;
    }

    if (input_continent[0] == '\n') {
        // getting all the countries
        shallowCopyListOfElements(getElementsInRepo(getRepository(ui->service)), result_list, getServiceLength(ui->service));
        size_of_list = getServiceLength(ui->service);

    } else {
        input_continent[strlen(input_continent) - 1] = '\0';
        // getting the countries from a continent
        filterServiceByContinent(ui->service, result_list, &size_of_list, input_continent);
    }

    filterByPopulationSize(result_list, &size_of_list);
    sortByPopulationUi(result_list, size_of_list);
    printListOfElements(result_list, size_of_list);

    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        if (result_list[i] != NULL) {
            result_list[i] = NULL;
        }
    }
    free(result_list);
    result_list = NULL;
}

void filterByPopulationSize(TElem** result_list, int* size_of_list){
    char input_population[50];

    double validated_population;

    char *ptr;
    double result;

    printf("Population: ");
    scanf("%s", input_population);

    // validating the population
    result = strtod(input_population, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid population(must be floating point number)\n");
        return;
    }
    validated_population = result;

    filterElementsByPopulation(result_list, size_of_list, validated_population);
}

// Sort

void sortByPopulationUi(TElem** given_list, int size_of_list){
    char option[10];

    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("What do you want to do?\n");
    scanf("%s", option);

    // validating way of sorting
    if (strcmp(option, "1") !=0 && strcmp(option, "2") != 0){
        printf("Invalid way of sorting\n");
        return;
    }

    sortElementsByPopulation(given_list, size_of_list, option);
}

// Undo, Redo

void undoFunctionalityUi(UserInterface* ui){
    char option[10];

    printf("1. Undo\n");
    printf("2. Redo\n");

    printf("What do you want to do?\n");
    scanf("%s", option);

    if (strcmp(option, "1") == 0) {
        Repository* new_pointer;
        new_pointer = undoOperation(ui->undoService, ui->service->repository);
        if (new_pointer == NULL){
            printf("Nothing to undo");
            return;
        }
        ui->service->repository = new_pointer;
    }
    else if (strcmp(option, "2") == 0) {
        Repository* new_pointer;
        new_pointer = redoOperation(ui->undoService, ui->service->repository);
        if (new_pointer == NULL){
            printf("Nothing to redo");
            return;
        }
        ui->service->repository = new_pointer;
    }
    else {
        printf("No such command!\n");

    }
}

// Print

void printListOfElements(TElem** given_list, int size_of_list){
    char my_string[200];

    if (size_of_list == 0){
        printf("Empty list\n");
    }
    else {
        for (int i = 0; i < size_of_list; i++) {
            toString(given_list[i], my_string);
            printf("%s\n", my_string);
        }
    }
}

void printAllElements(UserInterface* ui){
    char my_string[200];
    for (int i = 0; i < getServiceLength(ui->service); i++){
        toString(getElementInService(ui->service, i), my_string);
        printf("%s\n", my_string);
    }
}

void printMenu(){
    printf("\n1. Add Country\n");
    printf("2. Delete Country\n");
    printf("3. Update Country\n");
    printf("4. Show Countries\n");
    printf("5. Search Countries - whose names contain the substring\n");
    printf("6. Filter Countries By Continent - sorted by population greater than a value\n");
    printf("7. Undo / Redo\n");
    printf("0. Exit\n");
}

// Start

void startUi(UserInterface* ui){
    int ok = 0;
    char option[10];
    populateServiceWithEntries(ui->service);
    addOperationToHistory(ui->undoService, ui->service->repository);

    while (ok == 0) {
        printMenu();
        printf("What do you want to do?\n");
        scanf("%s", option);

        if (strcmp(option, "1") == 0){
            addFunctionalityUi(ui);
        }
        else if (strcmp(option, "2") == 0) {
            deleteFunctionalityUi(ui);
        }
        else if (strcmp(option, "3") == 0) {
            updateFunctionalityUi(ui);
        }
        else if (strcmp(option, "4") == 0) {
            printAllElements(ui);
        }
        else if (strcmp(option, "5") == 0) {
            filterByNameContainingStringUi(ui);
        }
        else if (strcmp(option, "6") == 0) {
            filterByContinentUi(ui);
        }
        else if (strcmp(option, "7") == 0){
            undoFunctionalityUi(ui);
        }
        else if (strcmp(option, "0") == 0){
            printf("Bye bye!");
            ok = 1;
            destroyUserInterface(ui);
        }
        else {
            printf("No such command!\n");
        }
    }
}

