#include "Operation.h"

void AddOperation::perform() {
    this->redo();
}

void AddOperation::undo() {
    this->repository->deleteElementRepo(this->dog.getImage());
}

void AddOperation::redo() {
    this->repository->addElementRepo(dog);
}

void DeleteOperation::perform() {
    this->redo();
}

void DeleteOperation::undo() {
    this->repository->addElementRepo(dog);
}

void DeleteOperation::redo() {
    this->repository->deleteElementRepo(this->dog.getImage());
}

void UpdateOperation::perform() {
    this->redo();
}

void UpdateOperation::undo() {
    this->repository->updateElementAdminRepo(this->previousDog);
}

void UpdateOperation::redo() {
    this->repository->updateElementAdminRepo(this->currentDog);
}
