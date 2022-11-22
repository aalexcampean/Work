//
// Created by Alex Campean on 16.03.2022.
//
#pragma once
#include "../Repository/Repo.h"

typedef struct{
    Repository** history;
    int index;
    int total_repositories;
    int capacity;
} UndoService;

// Constructor, Destructor

/// <summary>Creates an undo service layer</summary>
/// <param name="capacity">int, the capacity of repositories inside the history</param>
/// <returns>A pointer to the created undo service</returns
UndoService* createUndoService(int capacity);

/// <summary>Destroys an undo service layer and its contents</summary>
/// <param name="undoService">UndoService*, the undo service that needs to be destroyed</param>
/// <returns></returns
void destroyUndoService(UndoService* undoService);

// Getters

/// <summary>Returns the "index" field of the undo service</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <returns>The int associated to the field "index" of the given undo service</returns
int getUndoServiceIndex(UndoService* undoService);

/// <summary>Returns the "length" field of the undo service</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <returns>The int associated to the length "index" of the given undo service</returns
int getUndoServiceLength(UndoService*undoService);

/// <summary>Returns the "capacity" field of the undo service</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <returns>The int associated to the field "capacity" of the given undo service</returns
int getUndoServiceCapacity(UndoService*undoService);

/// <summary>Returns the "history" field of the undo service</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <returns>The list of repositories associated to the field "history" of the given undo service</returns
Repository** getHistory(UndoService* undoService);

/// <summary>Returns the repository situated at the given position</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <param name="position">int*, the given position</param>
/// <returns>The repository found at the given position</returns
Repository* getRepositoryAtPosition(UndoService* undoService, int position);

// Add to History

/// <summary>Adds an operation to the undo service history</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <param name="repository">Repository*, the given repository</param>
/// <returns></returns
void addOperationToHistory(UndoService* undoService, Repository* repository);

// Undo, Redo

/// <summary>Performs an undo operation</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <param name="repository">Repository*, the given repository</param>
/// <returns>True if the there is an undo left and performs it and false otherwise and doesn't perform anything</returns
Repository* undoOperation(UndoService* undoService, Repository* repository);

/// <summary>Performs an redo operation</summary>
/// <param name="undoService">UndoService*, the given undo service</param>
/// <param name="repository">Repository*, the given repository</param>
/// <returns>True if the there is an redo left and performs it and false otherwise and doesn't perform anything</returns
Repository* redoOperation(UndoService* undoService, Repository* repository);