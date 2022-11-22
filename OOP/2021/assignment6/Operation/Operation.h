#pragma once
#include "../TextRepository/TextRepo.h"

class Operation {
public:
    Operation() {};
    ~Operation() {};

    virtual void perform() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class AddOperation : public Operation {
private:
    Movie m;
    TextRepo* repo;

public:
    AddOperation(Movie& movie, TextRepo* repo) : m(movie), repo(repo) {};
    ~AddOperation() {};

    void perform() override;
    void undo() override;
    void redo() override;
};

class DeleteOperation : public Operation {
private:
    Movie m;
    TextRepo* repo;

public:
    DeleteOperation(Movie& movie, TextRepo* repo) : m(movie), repo(repo) {};
    ~DeleteOperation() {};

    void perform() override;
    void undo() override;
    void redo() override;
};

class UpdateOperation : public Operation {
private:
    Movie prevM;
    Movie currentM;
    TextRepo* repo;

public:
    UpdateOperation(Movie& previousMovie, Movie& currentMovie, TextRepo* repo) : prevM(previousMovie), currentM(currentMovie), repo(repo) {};
    ~UpdateOperation() {};

    void perform() override;
    void undo() override;
    void redo() override;
};


