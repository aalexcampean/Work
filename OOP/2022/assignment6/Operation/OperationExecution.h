#pragma once
#include "Operation.h"
#include <stack>

class OperationExecution {
private:
    std::stack<Operation*> operations;
    std::stack<Operation*> undoOperations;

public:
    OperationExecution() = default;;
    ~OperationExecution() = default;;
    void saveOperation(Operation* op);
    void undo();
    void redo();
};



