from Transition import Transition


class FiniteAutomata:
    def __init__(self):
        self.alphabet = []
        self.states = []
        self.transitions = []
        self.initialState = []
        self.endStates = []

    def readFromFile(self):
        with open("fa.in", 'r') as file:
            lineNo = 0
            for line in file:
                if lineNo == 0:
                    self.states = line.split("\n")[0].split(" ")
                    lineNo += 1
                elif lineNo == 1:
                    self.alphabet = line.split("\n")[0].split(" ")
                    lineNo += 1
                elif lineNo == 2:
                    self.initialState = line.split("\n")[0]
                    lineNo += 1
                elif lineNo == 3:
                    self.endStates = line.split("\n")[0]
                    lineNo += 1
                else:
                    transitionsParts = line.split("\n")[0].split(" ")
                    self.transitions.append(Transition(transitionsParts[0], transitionsParts[1], transitionsParts[2]))

    def getNextState(self, currentState, value):
        for transition in self.transitions:
            if (currentState == transition.startState) & (transition.value == value):
                return transition.endState
        return None

    def isAccepted(self, variable):
        currentState = self.initialState
        for character in variable:
            currentState = self.getNextState(currentState, character)
        return currentState in self.endStates

    def alphabetToString(self):
        stringRepresentation = "Alphabet: "
        for elem in self.alphabet:
            stringRepresentation += str(elem) + " "
        return stringRepresentation

    def statesToString(self):
        stringRepresentation = "States: "
        for elem in self.states:
            stringRepresentation += str(elem) + " "
        return stringRepresentation

    def initialStateToString(self):
        return "Initial states: " + str(self.initialState)

    def finalStatesToString(self):
        stringRepresentation = "Final states: "
        for elem in self.endStates:
            stringRepresentation += str(elem) + " "
        return stringRepresentation

    def transitionToString(self):
        stringRepresentation = "Transition: "
        for elem in self.transitions:
            stringRepresentation += str(elem) + " \n"
        return stringRepresentation
