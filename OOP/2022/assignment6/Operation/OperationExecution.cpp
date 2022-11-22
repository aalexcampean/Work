#include "OperationExecution.h"

void OperationExecution::saveOperation(Operation *op) {
    this->undoOperations = std::stack<Operation*>();
    op->perform();
    this->operations.push(op);
}

void OperationExecution::undo() {
    if (this->operations.size() > 0) {
        this->operations.top()->undo();
        this->undoOperations.push(this->operations.top());
        this->operations.pop();
    }
}

void OperationExecution::redo() {
    if (this->undoOperations.size() > 0) {
        this->undoOperations.top()->redo();
        this->operations.push(this->undoOperations.top());
        this->undoOperations.pop();
    }
}


