#include "../Repository/Repo.h"

// The Structure

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
/// <param name="us">UndoService*, the undo service that needs to be destroyed</param>
/// <returns></returns
void destroyUndoService(UndoService* us);

// Getters

/// <summary>Returns the "index" field of the undo service</summary>
/// <param name="us">UndoService*, the given undo service</param>
/// <returns>The int associated to the field "index" of the given undo service</returns
int getUsIndex(UndoService* us);

/// <summary>Returns the "length" field of the undo service</summary>
/// <param name="us">UndoService*, the given undo service</param>
/// <returns>The int associated to the length "index" of the given undo service</returns
int getUsLength(UndoService*us);

/// <summary>Returns the "capacity" field of the undo service</summary>
/// <param name="us">UndoService*, the given undo service</param>
/// <returns>The int associated to the field "capacity" of the given undo service</returns
int getUsCapacity(UndoService*us);

// Add to History

/// <summary>Adds an operation to the undo service history</summary>
/// <param name="us">UndoService*, the given undo service</param>
/// <param name="er">Repository*, the given repository</param>
/// <returns></returns
void addOperationToHistory(UndoService* us, Repository* er);

// Undo, Redo

/// <summary>Performs an undo operation</summary>
/// <param name="us">UndoService*, the given undo service</param>
/// <param name="er">Repository*, the given repository</param>
/// <returns>True if the there is an undo left and performs it and false otherwise and doesn't perform anything</returns
Repository* undoOperation(UndoService* us, Repository* er);

/// <summary>Performs an redo operation</summary>
/// <param name="us">UndoService*, the given undo service</param>
/// <param name="er">Repository*, the given repository</param>
/// <returns>True if the there is an redo left and performs it and false otherwise and doesn't perform anything</returns
Repository* redoOperation(UndoService* us, Repository* er);