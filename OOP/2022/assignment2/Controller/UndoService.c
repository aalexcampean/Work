//
// Created by Alex Campean on 16.03.2022.
//
#include "UndoService.h"
#include <stdlib.h>
#include <string.h>

// Constructor, Destructor

UndoService* createUndoService(int capacity){
    // allocate memory for the structure undo service
    UndoService* us = (UndoService*)malloc(sizeof(UndoService));

    if (us == NULL){
        return NULL;
    }

    us->capacity = 10;
    us->total_repositories = 0;
    us->index = -1;

    // allocating space for the 2d array like history
    us->history = (Repository**)malloc(us->capacity * sizeof(Repository*));
    for (int i = 0; i < getUndoServiceCapacity(us); i++){
        us->history[i] = NULL;
    }

    if (us->history == NULL){
        return NULL;
    }

    return us;
}

void destroyUndoService(UndoService* undoService){
    // if undoService points to NULL there is nothing that needs to be freed up
    if (undoService == NULL){
        return;
    }

    // if undoService->history points to NULL there is nothing that needs to be freed up
    if (undoService->history == NULL){
        return;
    }

    for (int i = 0; i < getUndoServiceCapacity(undoService); i++){
        // if undoService points to NULL there is nothing that needs to be freed up
        Repository* aux = undoService->history[i];
        if (undoService->history[i] != NULL){
            destroyRepository(undoService->history[i]);
            undoService->history[i] = NULL;
        }
    }

    free(undoService->history);
    undoService->history = NULL;

    free(undoService);
    undoService = NULL;
}

// Resize

void resizeUndoService(UndoService* undoService) {
    undoService->capacity *= 2;

    Repository **new_history = (Repository **) malloc(undoService->capacity * sizeof(Repository *));

    for (int i = 0; i < getUndoServiceCapacity(undoService); i++) {
        new_history[i]->da->list = NULL;
        new_history[i]->da->total_elements = 0;
        new_history[i]->da->capacity = 0;
    }

    for (int i = 0; i < getUndoServiceLength(undoService); i++) {
        new_history[i] = copyRepository(undoService->history[i]);
        destroyRepository(undoService->history[i]);

        free(undoService->history);
        undoService->history = new_history;
    }
}
// Getters

int getUndoServiceIndex(UndoService* undoService){
    return undoService->index;
}

int getUndoServiceLength(UndoService* undoService){
    return undoService->total_repositories;
}

int getUndoServiceCapacity(UndoService* undoService){
    return undoService->capacity;
}

Repository** getHistory(UndoService* undoService) {
    return undoService->history;
}

Repository* getRepositoryAtPosition(UndoService* undoService, int position) {
    return undoService->history[position];
}

// Add to History

void addOperationToHistory(UndoService* undoService, Repository* repository){
    if (getUndoServiceLength(undoService) == getUndoServiceCapacity(undoService)){
        resizeUndoService(undoService);
    }

    while (getUndoServiceIndex(undoService) + 1 < getUndoServiceLength(undoService)){
        destroyRepository(undoService->history[getUndoServiceLength(undoService) - 1]);
        undoService->history[getUndoServiceLength(undoService)] = NULL;
        undoService->total_repositories -= 1;
    }

    undoService->history[getUndoServiceLength(undoService)] = copyRepository(repository);
    undoService->index += 1;
    undoService->total_repositories += 1;
}

// Undo, Redo

Repository* undoOperation(UndoService* undoService, Repository* repository){
    if (getUndoServiceIndex(undoService) <= 0){
        return NULL;
    }

    undoService->index -= 1;

    Repository* new_er = copyRepository(undoService->history[getUndoServiceIndex(undoService)]);
    destroyRepository(repository);

    return new_er;
}

Repository* redoOperation(UndoService* undoService, Repository* repository){
    if (getUndoServiceIndex(undoService) == getUndoServiceLength(undoService) - 1){
        return NULL;
    }

    undoService->index += 1;

    Repository* new_er = copyRepository(undoService->history[getUndoServiceIndex(undoService)]);
    destroyRepository(repository);
//    repository = new_er;

//    makeRepoDeepCopy(repository, undoService->history[getUndoServiceIndex(undoService)]);
//    repository->da->total_elements = getDaLength(undoService->history[getUndoServiceIndex(undoService)]->da);

    return new_er;
}

