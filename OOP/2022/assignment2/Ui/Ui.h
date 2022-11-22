//
// Created by Alex Campean on 16.03.2022.
//
#pragma once
#include "../Controller/Service.h"
#include "../Controller/UndoService.h"

typedef struct{
    Service* service;
    UndoService* undoService;
} UserInterface;

// Constructor, Destructor

/// <summary>Creates an user interface layer</summary>
/// <param name=""></param>
/// <returns>A pointer to the created user interface</returns
UserInterface* createUserInterface();

/// <summary>Destroys an user interface layer and its contents</summary>
/// <param name="ui">UserInterface*, the user interface that needs to be destroyed</param>
/// <returns></returns
void destroyUserInterface(UserInterface* ui);

// Add, Delete, Update

/// <summary>Prepares the addition of an element to the service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the operation if able or prints a message otherwise</returns
void addFunctionalityUi(UserInterface* ui);

/// <summary>Prepares the deletion of an element from the service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the operation if able or prints a message otherwise</returns
void deleteFunctionalityUi(UserInterface* ui);

/// <summary>Prepares the update of an element in the service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the operation if able or prints a message otherwise</returns
void updateFunctionalityUi(UserInterface* ui);

void updateCountryPopulation(UserInterface* ui);
void handleMigration(UserInterface* ui);


// Sort

void sortByPopulationUi(TElem** given_list, int size_of_list);

// Filter

void filterByNameContainingStringUi(UserInterface* ui);

void filterByContinentUi(UserInterface* ui);

void filterByPopulationSize(TElem** result_list, int* size_of_list);

// Undo, Redo

/// <summary>Prepares the undo / redo for the undo service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the undo / redo if able or prints a message otherwise</returns
void undoFunctionalityUi(UserInterface* ui);

// Print

void printAllElements(UserInterface* ui);

void printListOfElements(TElem** given_list, int size_of_list);

void printMenu();

// Start

/// <summary>Starts the ui</summary>
/// <param name="ui">UserInterface*, the user interface that needs to be used</param>
/// <returns></returns
void startUi(UserInterface* ui);
