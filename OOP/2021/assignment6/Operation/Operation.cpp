#include "Operation.h"

void AddOperation::perform() {
    this->redo();
}

void AddOperation::undo() {
    this->repo->deleteElement(this->m.getTitle());
}

void AddOperation::redo() {
    this->repo->addElement(m);
}

void DeleteOperation::perform() {
    this->redo();
}

void DeleteOperation::undo() {
    this->repo->addElement(m);
}

void DeleteOperation::redo() {
    this->repo->deleteElement(this->m.getTitle());
}

void UpdateOperation::perform() {
    this->redo();
}

void UpdateOperation::undo() {
    this->repo->updateElement(this->prevM);
}

void UpdateOperation::redo() {
    this->repo->updateElement(this->currentM);
}
