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
    for (int i = 0; i < getUsCapacity(us); i++){
        us->history[i] = NULL;
    }

    if (us->history == NULL){
        return NULL;
    }

    return us;
}

void destroyUndoService(UndoService* us){
    // if us points to NULL there is nothing that needs to be freed up
    if (us == NULL){
        return;
    }

    // if us->history points to NULL there is nothing that needs to be freed up
    if (us->history == NULL){
        return;
    }

    for (int i = 0; i < getUsCapacity(us); i++){
        // if us points to NULL there is nothing that needs to be freed up
        if (us->history[i] != NULL){
            destroyRepository(us->history[i]);
            us->history[i] = NULL;
        }
    }

    free(us->history);
    us->history = NULL;

    free(us);
    us = NULL;
}

// Resize

void resizeUndoService(UndoService* us) {
    us->capacity *= 2;

    Repository **new_history = (Repository **) malloc(us->capacity * sizeof(Repository *));

    for (int i = 0; i < getUsCapacity(us); i++) {
        new_history[i]->da->list = NULL;
        new_history[i]->da->total_elements = 0;
        new_history[i]->da->capacity = 0;
    }

    for (int i = 0; i < getUsLength(us); i++) {
        new_history[i] = copyRepository(us->history[i]);
        destroyRepository(us->history[i]);

        free(us->history);
        us->history = new_history;
    }
}
// Getters

int getUsIndex(UndoService* us){
    return us->index;
}

int getUsLength(UndoService*us){
    return us->total_repositories;
}

int getUsCapacity(UndoService*us){
    return us->capacity;
}

// Add to History

void addOperationToHistory(UndoService* us, Repository* er){
    if (getUsLength(us) == getUsCapacity(us)){
        resizeUndoService(us);
    }

    while (getUsIndex(us) + 1 < getUsLength(us)){
        destroyRepository(us->history[getUsLength(us)]);
        us->history[getUsLength(us)] = NULL;
        us->total_repositories -= 1;
    }

    us->history[getUsLength(us)] = copyRepository(er);
    us->index += 1;
    us->total_repositories += 1;
}

// Undo, Redo

Repository* undoOperation(UndoService* us, Repository* er){
    if (getUsIndex(us) <= 0){
        return NULL;
    }

    us->index -= 1;

    Repository* new_er = copyRepository(us->history[getUsIndex(us)]);
    destroyRepository(er);

    return new_er;
}

Repository* redoOperation(UndoService* us, Repository* er){
    if (getUsIndex(us) == getUsLength(us) - 1){
        return 0;
    }

    us->index += 1;

    Repository* new_er = copyRepository(us->history[getUsIndex(us)]);
    destroyRepository(er);
//    er = new_er;

//    makeRepoDeepCopy(er, us->history[getUsIndex(us)]);
//    er->da->total_elements = getDaLength(us->history[getUsIndex(us)]->da);

    return NULL;
}

