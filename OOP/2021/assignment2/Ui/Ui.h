#pragma once
#include "../Controller/Service.h"
#include "../Controller/UndoService.h"
#define _CRT_SECURE_NO_WARNINGS

// The Structure

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

// Search

/// <summary>Prepares the search of an element(by its address) in the service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the search if able or prints a message otherwise</returns
void searchFunctionalityUi(UserInterface* ui);

// Sort

/// <summary>Prepares the sort of a list in the service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the search if able or prints a message otherwise</returns
void sortElementsUi(TElem** given_list, int size_of_list);

// Undo, Redo

/// <summary>Prepares the undo / redo for the undo service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the undo / redo if able or prints a message otherwise</returns
void undoFunctionalityUi(UserInterface* ui);

// Filter

/// <summary>Prepares the filter by type of the repo for the service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the filter if able or prints a message otherwise</returns
void filterByTypeUi(UserInterface* ui);

/// <summary>Prepares the filter by price of the repo for the service layer</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the filter if able or prints a message otherwise</returns
void filterByPrice(UserInterface* ui);

// Print

/// <summary>Prepares the prints from the ui</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns>Performs the operation according to the user's input</returns
void printElementsUi(UserInterface* ui);

/// <summary>Prints all the elements from the service->repository->dynamic array</summary>
/// <param name="ui">UserInterface*, the given user interface</param>
/// <returns></returns
void printAllElements(UserInterface* ui);

/// <summary>Prints all the elements from a given list</summary>
/// <param name="given_list">TElem*, the given list of elements</param>
/// <param name="size_of_list">Int, the size of the given list of elements</param>
/// <returns></returns
void printListOfElements(TElem** given_list, int size_of_list);

/// <summary>Prints all the menu of the application</summary>
/// <param name=""></param>
/// <returns></returns
void printMenu();

// Start

/// <summary>Starts the ui</summary>
/// <param name="ui">UserInterface*, the user interface that needs to be used</param>
/// <returns></returns
void startUi(UserInterface* ui);
