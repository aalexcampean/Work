class UndoServiceException(Exception):

    def __init__(self, msg):
        self._msg = msg


class UndoService:
    def __init__(self):
        # History of program operations
        self._history = []
        self._index = -1

    def record(self, operation):
        # When recording a new operation, discard all previous undos
        self._history = self._history[0:self._index + 1]

        self._history.append(operation)
        self._index += 1

    def undo(self):
        if self._index == -1:
            # Nothing to undo
            raise UndoServiceException('!!! Nothing left to undo !!!')

        self._history[self._index].undo()
        self._index -= 1

    def redo(self):
        if self._index == len(self._history) - 1:
            # Nothing to redo
            raise UndoServiceException('!!! Nothing left to redo !!!')

        self._index += 1
        self._history[self._index].redo()


class CascadedOperation:
    """
    Represents a cascaded operation (where 1 user operation corresponds to more than 1 program operations)
    """

    def __init__(self, *operations):
        self._operations = operations

    def undo(self):
        for oper in self._operations:
            oper.undo()

    def redo(self):
        for oper in self._operations:
            oper.redo()


class Operation:
    """
    How to undo/redo a program operation
    """

    def __init__(self, fun_call_undo, fun_call_redo):
        self._fun_call_undo = fun_call_undo
        self._fun_call_redo = fun_call_redo

    def undo(self):
        self._fun_call_undo()

    def redo(self):
        self._fun_call_redo()


class FunctionCall:
    """
    A function call with parameters
    """

    def __init__(self, function_ref, *function_params):
        self._function_ref = function_ref
        self._function_params = function_params

    def call(self):
        return self._function_ref(*self._function_params)

    def __call__(self):
        return self.call()


'''
Command design pattern
    - Tell the program what to do 
        e.g. undo -> create_client
             redo -> delete_client
    - Call a method sometime later (definitely not right now)
        1. exec('client_service.create_client(...)')
        2. function references
'''
