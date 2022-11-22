from Repository import *


class Controller:
    def __init__(self, repo: Repository):
        # args - list of parameters needed in order to create the controller
        self._repository = repo
        self._currentIteration = 0

    def getRepository(self):
        return self._repository

    def getMap(self):
        return self._repository.getMap()

    def getMapRows(self):
        return self._repository.getMapRows()

    def getMapColumns(self):
        return self._repository.getMapColumns()

    def createRandomMap(self):
        self._repository.createRandomMap()

    def loadMapService(self, inputFile):
        self._repository.loadMap(inputFile)

    def saveMapService(self, inputFile):
        self._repository.saveMap(inputFile)

    def iteration(self):
        # args - list of parameters needed to run one iteration
        # A iteration:
        lastPopulation = self._repository.getLastPopulation()
        # Selecting the parents
        lastPopulation.selection(lastPopulation.getPopulationSize())
        # Creating offsprings by crossover of the parents and apply mutations for them
        # The mutated offsprings are taking the place of the weakest existing individuals
        lastPopulation.extendPopulation()
        # Incrementing the iteration count
        self._currentIteration += 1

    def run(self, nrOfIterations):
        # args - list of parameters needed in order to run the algorithm
        self._currentIteration = 0
        fitnessFunctions = []

        # Until stop condition
        while self._currentIteration < nrOfIterations:
            # Performing an iteration
            self.iteration()
            # Every 2 iterations compute another result for statistics
            if self._currentIteration % 2 == 0:
                # Saving the information needed for statistics
                fitnessFunctions.append(self._repository.getLastPopulation().getAverageFitness())

        # Returning the results and the info for statistics
        return fitnessFunctions

    def solver(self, nrOfIterations, populationSize, individualSize):
        # args - list of parameters needed in order to run the solver
        # Creating the population
        self._repository.createPopulation([populationSize, individualSize])
        # Running the algorithm
        fitnessFunctions = self.run(nrOfIterations)
        # Returning the results and the statistics
        return self._repository.getBestPathInLastPopulation(), fitnessFunctions
