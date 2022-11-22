#pragma once

#include "../Repository/TextFile/TextFileRepository.h"

class Operation {
public:
    Operation() = default;;

    ~Operation() = default;;

    virtual void perform() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;
};

class AddOperation : public Operation {
private:
    Dog dog;
    TextFileRepository *repository;

public:
    AddOperation(Dog &dog, TextFileRepository *repo) : dog(dog), repository(repo) {};

    ~AddOperation() = default;;

    void perform() override;

    void undo() override;

    void redo() override;
};

class DeleteOperation : public Operation {
private:
    Dog dog;
    TextFileRepository *repository;

public:
    DeleteOperation(Dog &dog, TextFileRepository *repo) : dog(dog), repository(repo) {};

    ~DeleteOperation() = default;;

    void perform() override;

    void undo() override;

    void redo() override;
};

class UpdateOperation : public Operation {
private:
    Dog previousDog;
    Dog currentDog;
    TextFileRepository *repository;

public:
    UpdateOperation(Dog &prevDog, Dog &currDog, TextFileRepository *repo) : previousDog(prevDog), currentDog(currDog),
                                                                            repository(repo) {};

    ~UpdateOperation() = default;;

    void perform() override;

    void undo() override;

    void redo() override;
};


