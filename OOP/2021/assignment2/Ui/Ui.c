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

    printf("The initial capacity of the list of Estate:\n");
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

    // free the memory occupied by the undoservice
    destroyUndoService(ui->undoService);
    ui->undoService = NULL;

    // free the memory occupied by the user interface
    free(ui);
    ui = NULL;
}

// Add, Delete, Update

void addFunctionalityUi(UserInterface* ui){
    char input_type[20];
    char input_address[50];
    char input_surface[20];
    char input_price[20];

    double validated_surface;
    double validated_price;

    char *ptr;
    double result;

    // validating the type
    printf("Type(house | apartment | penthouse): ");
    scanf("%s", input_type);

    if (strcmp(input_type, "house") != 0 && strcmp(input_type, "apartment") != 0 && strcmp(input_type, "penthouse") != 0 ){
        printf("Invalid type(available types: house | apartment | penthouse)\n");
        return;
    }

    printf("Address: ");
    scanf("%s", input_address);

    // validating the surface
    printf("Surface: ");
    scanf("%s", input_surface);

    result = strtod(input_surface, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid surface(must be floating point number)\n");
        return;
    }
    validated_surface = result;

    // validating the price
    printf("Price: ");
    scanf("%s", input_price);

    result = strtod(input_price, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid price(must be floating point number)\n");
        return;
    }
    validated_price = result;

    int b = addElementToService(ui->service, input_type, input_address, validated_surface, validated_price);

    if (b == 1){
        addOperationToHistory(ui->undoService, ui->service->repository);
    }
    else {
        printf("Estate already exists\n");
    }
}

void deleteFunctionalityUi(UserInterface* ui){
    char input_address[50];

    printf("Address: ");
    scanf("%s", input_address);

    int b = deleteElementFromService(ui->service, input_address);

    if (b == 1){
        addOperationToHistory(ui->undoService, ui->service->repository);
    }
    else {
        printf("Estate not found\n");
    }
}

void updateFunctionalityUi(UserInterface* ui){
    char new_type[20];
    char the_address[50];
    char new_surface[20];
    char new_price[20];

    double validated_new_surface;
    double validated_new_price;

    char *ptr;
    double result;

    printf("The address: ");
    scanf("%s", the_address);

    // validating the type
    printf("New Type(house | apartment | penthouse): ");
    scanf("%s", new_type);

    if (strcmp(new_type, "house") != 0 && strcmp(new_type, "apartment") != 0 && strcmp(new_type, "penthouse") != 0 ){
        printf("Invalid type(available types: house | apartment | penthouse)\n");
        return;
    }

    // validating the surface
    printf("New Surface: ");
    scanf("%s", new_surface);

    result = strtod(new_surface, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid surface(must be floating point number)\n");
        return;
    }
    validated_new_surface = result;

    // validating the price
    printf("New Price: ");
    scanf("%s", new_price);

    result = strtod(new_price, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid price(must be floating point number)\n");
        return;
    }
    validated_new_price = result;

    int b = updateElementInService(ui->service, new_type, the_address, validated_new_surface, validated_new_price);

    if (b == 1){
        addOperationToHistory(ui->undoService, ui->service->repository);
    }
    else {
        printf("Given address does not match any existing estate");
    }
}

// Search

void searchFunctionalityUi(UserInterface* ui){
    char input_address[50];
    char help;

    printf("The address:");
    scanf("%c", &help);
    fgets(input_address, sizeof(input_address), stdin);

    TElem** result_list = (TElem**)malloc(getServiceCapacity(ui->service) * sizeof(TElem*));
    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        result_list[i] = NULL;
    }

    if (input_address[0] == '\n') {
        int size_of_list = ui->service->repository->da->total_elements;

        copyListOfElements(ui->service->repository->da->list, result_list, size_of_list);
        sortElementsUi(result_list, ui->service->repository->da->total_elements);
        printListOfElements(result_list, ui->service->repository->da->total_elements);

    } else {
        input_address[strlen(input_address) - 1] = '\0';
        int size_of_list = 0;

        searchElementInServiceByAddressOrType(ui->service, result_list, &size_of_list, input_address);
        sortElementsUi(result_list, size_of_list);
        printListOfElements(result_list, size_of_list);
    }

    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        if (result_list[i] != NULL) {
            destroyEstate(result_list[i]);
        }
    }
    free(result_list);
    result_list = NULL;
}

// Sort

void sortElementsUi(TElem** given_list, int size_of_list){
    int ok = 0;
    char option[10];
    char option_2[10];

    while (ok == 0) {

        printf("1. Sort by price\n");
        printf("2. Sort by surface\n");
        printf("What do you want to do?\n");
        scanf("%s", option);

        printf("1. Ascending\n");
        printf("2. Descending\n");
        printf("What do you want to do?\n");
        scanf("%s", option_2);

        // validating way of sorting
        if (strcmp(option_2, "1") !=0 && strcmp(option_2, "2") == !0){
            printf("Invalid way of sorting\n");
            return;
        }

        if (strcmp(option, "1") == 0) {
            sortElementsByPrice(given_list, size_of_list, option_2);
            ok = 1;

        }
        else if (strcmp(option, "2") == 0) {
            sortElementsBySurface(given_list, size_of_list, option_2);
            ok = 1;

        }
        else {
            printf("No such command!\n");
        }
    }
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

// Filter

void filterByTypeUi(UserInterface* ui){
    char input_type[20];

    char input_surface[20];
    double validated_surface;

    char *ptr;
    double result;

    printf("The type(house | apartment | penthouse):");
    scanf("%s", input_type);

    if (strcmp(input_type, "house") != 0 && strcmp(input_type, "apartment") != 0 && strcmp(input_type, "penthouse") != 0 ){
        printf("Invalid type(available types: house | apartment | penthouse)\n");
        return;
    }

    printf("The surface:");
    scanf("%s", input_surface);

    result = strtod(input_surface, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid surface(must be floating point number)\n");
        return;
    }
    validated_surface = result;

    char option[10];

    printf("1. Sort in ascending order\n");
    printf("2. Sort in descending order\n");

    // validating the option
    scanf("%s", option);
    if (strcmp(option, "1") != 0 && strcmp(option, "2") != 0){
        printf("Invalid way of sorting\n");
        return;
    }

    TElem** result_list = (TElem**)malloc(getServiceCapacity(ui->service) * sizeof(TElem*));
    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        result_list[i] = NULL;
    }
    int size_of_list = 0;

    searchElementInServiceByAddressOrType(ui->service, result_list, &size_of_list, input_type);

    filterElementsBySurface(result_list, &size_of_list, validated_surface);
    sortElementsBySurface(result_list, size_of_list, option);
    printListOfElements(result_list, size_of_list);

    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        if (result_list[i] != NULL) {
            destroyEstate(result_list[i]);
        }
    }
    free(result_list);
    result_list = NULL;
}

void filterByPrice(UserInterface* ui){
    char input_price[20];
    double validated_new_price;

    char *ptr;
    double result;

    printf("Estate price: ");
    scanf("%s", input_price);

    result = strtod(input_price, &ptr);
    if (result == 0 && strcmp(ptr, "") != 0){
        printf("Invalid price(must be floating point number)\n");
        return;
    }
    validated_new_price = result;

    int size_of_list = getServiceLength(ui->service);
    TElem** result_list = (TElem**)malloc(size_of_list * sizeof(TElem*));
    for (int i = 0; i < size_of_list; i++){
        result_list[i] = createEstate("", "", 0, 0);
    }

    copyListOfElements(ui->service->repository->da->list, result_list, size_of_list);
    filterElementsByPrice(result_list, &size_of_list, validated_new_price);
    printListOfElements(result_list, size_of_list);

    for (int i = 0; i < getServiceCapacity(ui->service); i++){
        if (result_list[i] != NULL) {
            destroyEstate(result_list[i]);
        }
    }
    free(result_list);
    result_list = NULL;
}

// Print

void printElementsUi(UserInterface* ui){
    int ok = 0;
    char option[10];

    while (ok == 0) {
        printf("1. Print all elements\n");
        printf("2. Print elements of a given type\n");
        printf("3. Print elements with a given price\n");

        printf("What do you want to do?\n");
        scanf("%s", option);

        if (strcmp(option, "1") == 0){
            printAllElements(ui);
            ok = 1;

        }
        else if (strcmp(option, "2") == 0){
            filterByTypeUi(ui);
            ok = 1;

        }
        else if (strcmp(option, "3") == 0){
            filterByPrice(ui);
            ok = 1;

        }
        else {
            printf("No such command!\n");
        }
    }
}

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
    printf("\n1. Add Estate\n");
    printf("2. Delete Estate\n");
    printf("3. Update Estate\n");
    printf("4. Show Estates\n");
    printf("5. Search Estate\n");
    printf("6. Undo / Redo\n");
    printf("0. Exit\n");
}

// Start

void startUi(UserInterface* ui){
    int ok = 0;
    char option[10];
    populateListWithElements(ui->service);
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
            printElementsUi(ui);

        }
        else if (strcmp(option, "5") == 0) {
            searchFunctionalityUi(ui);

        }
        else if (strcmp(option, "6") == 0){
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

