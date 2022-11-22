class Transition:
    def __init__(self, startState, value, endState):
        self.startState = startState
        self.value = value
        self.endState = endState

    def getStartSate(self):
        return self.startState

    def setStartSate(self, startState):
        self.startState = startState

    def getValue(self):
        return self.value

    def setValue(self, value):
        self.value = value

    def getEndState(self):
        return self.endState

    def setEndState(self, endState):
        self.endState = endState

    def __str__(self) -> str:
        return str(self.startState) + str(self.value) + str(self.endState)
