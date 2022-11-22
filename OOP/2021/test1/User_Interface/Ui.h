#include "../Service/Service.h"


class Ui {
private:
    Service service;

public:
    Ui();
    Ui(Ui &ui);
    ~Ui();

    // Start

    /// <summary>Starts the ui</summary>
    /// <param name=""></param>
    /// <returns></returns
    void start();

    // Print Menu

    /// <summary>Prints the menu of the application</summary>
    /// <param name=""></param>
    /// <returns></returns
    void printStartMenu();

    // Print Database

    /// <summary>Prints all the elements from the adminService->repository->dynamic array</summary>
    /// <param name=""></param>
    /// <returns></returns
    void printGenesInDatabase();

    // Add, Delete, Update

    /// <summary>Prepares the addition of an element to the adminService layer</summary>
    /// <param name=""></param>
    /// <returns>Performs the operation if able or prints a message otherwise</returns
    void addFunctionalityUi();
};

