# -*- coding: utf-8 -*-
import pickle
from copy import copy
from random import *
from utils import *
import numpy as np


class Drone:
    def __init__(self, x, y, battery=20):
        self._xCoordinate = x
        self._yCoordinate = y
        self._battery = battery

    def getX(self):
        return self._xCoordinate

    def getY(self):
        return self._yCoordinate

    def getBattery(self):
        return self._battery


class Map:
    def __init__(self, n=20, m=20):
        self._n = n
        self._m = m
        self._surface = np.zeros((self._n, self._m))

    def getRows(self):
        return self._n

    def getColumns(self):
        return self._m

    def getSurface(self):
        return self._surface

    def setN(self, inputN):
        self._n = inputN

    def setM(self, inputM):
        self._m = inputM

    def setSurface(self, inputSurface):
        self._surface = inputSurface

    def randomMap(self, fill=0.2):
        for i in range(self._n):
            for j in range(self._m):
                if random() <= fill:
                    self._surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self._n):
            for j in range(self._m):
                string = string + str(int(self._surface[i][j]))
            string = string + "\n"
        return string


class Gene:
    def __init__(self):
        # random initialise the gene according to the representation
        self._value = randint(0, 3)

    def getValue(self):
        return self._value


class Individual:
    def __init__(self, nrOfGenes=0):
        self._nrOfGenes = nrOfGenes
        self._genes = [Gene().getValue() for _ in range(self._nrOfGenes)]
        self._fitnessFunction = None
        self._path = None

    def getNumberOfGenes(self):
        return self._nrOfGenes

    def getGenes(self):
        return self._genes

    def setGenes(self, inputGenes):
        self._genes = inputGenes

    def getFitnessFunction(self):
        return self._fitnessFunction

    def getPath(self):
        return self._path

    def isMoveValid(self, x, y, inputMap):
        return 0 <= x <= inputMap.getRows() - 1 and 0 <= y <= inputMap.getColumns() - 1 and inputMap.getSurface()[x][y] == 0

    # Finding the path of a chromosome
    def findPath(self, inputDrone: Drone, inputMap: Map):
        startX = inputDrone.getX()
        startY = inputDrone.getY()
        battery = inputDrone.getBattery()
        coordinates = [startX, startY]
        self._path = [coordinates]

        # Parse all genes with and compute the path using directions
        for i in self._genes:
            nextX = self._path[-1][0] + directions[i][0]
            nextY = self._path[-1][1] + directions[i][1]
            if battery >= len(self._path):
                self._path.append([nextX, nextY])
                battery -= 1

    # Computing the fitness function of a individual
    def fitness(self, inputDrone: Drone, inputMap: Map):
        visitedPlaces = []
        self._fitnessFunction = 0
        self.findPath(inputDrone, inputMap)
        for i in range(len(self._path)):
            x = self._path[i][0]
            y = self._path[i][1]
            if (x, y) not in visitedPlaces:
                visitedPlaces.append((x, y))

                # save initial position of the drone
                initialX = x
                initialY = y
                for direction in directions:
                    # always start from the initial position
                    x = initialX
                    y = initialY
                    while self.isMoveValid(x + direction[0], y + direction[1], inputMap):
                        if (x + direction[0], y + direction[1]) not in visitedPlaces:
                            visitedPlaces.append((x + direction[0], y + direction[1]))
                            self._fitnessFunction += 10

                        x += direction[0]
                        y += direction[1]

                    self._fitnessFunction -= 5

    # Mutating a chromosome
    def mutate(self, nrOfMutatedGenes=1, mutateProbability=0.04):
        for _ in range(nrOfMutatedGenes):
            # Performing a mutation with respect to the representation
            index = randrange(self._nrOfGenes)
            # Using this mutation method to make sure that a gene is mutated if it is the case
            self._genes[index] = self._genes[index] if random() > mutateProbability else abs(self._genes[index] - 1)

    # Performing a crossover between 2 chromosomes
    def crossover(self, otherParent, crossoverProbability=0.8):
        offspring1, offspring2 = Individual(self._nrOfGenes), Individual(self._nrOfGenes)
        if random() < crossoverProbability:
            # Checking if the number of genes is the same for both chromosomes
            if self._nrOfGenes != otherParent.getNumberOfGenes():
                raise ValueError("Chromosomes must have the same number of genes")
            # Checking if the number of genes is greater than 2 (for the cut to be even worth doing)
            if self._nrOfGenes < 2:
                return self, otherParent
            # Creating 1 cut at a random place
            cut = randrange(self._nrOfGenes)
            # Performing the crossover between the self and the otherParent
            offspring1.setGenes(self._genes[cut:] + otherParent.getGenes()[:cut])
            offspring2.setGenes(self._genes[:cut] + otherParent.getGenes()[cut:])

        return offspring1, offspring2


class Population:
    def __init__(self, inputDrone: Drone, inputMap: Map, populationSize=0, individualSize=0):
        self._drone = inputDrone
        self._map = inputMap
        self._populationSize = populationSize
        self._Individuals = [Individual(individualSize) for _ in range(populationSize)]
        # Evaluating(computing the fitness function) all Individuals in the current population
        self.evaluate()

    def getPopulationSize(self):
        return self._populationSize

    def getIndividuals(self):
        return self._Individuals

    def getAverageFitness(self):
        return np.average([individual.getFitnessFunction() for individual in self._Individuals])

    def getBestPath(self):
        sortedIndividuals = self.getSortedIndividuals()
        bestIndividualPath = sortedIndividuals[0].getPath()
        return bestIndividualPath

    def getSortedIndividuals(self):
        return sorted(self._Individuals, key=lambda v: v.getFitnessFunction(), reverse=True)

    # Evaluating the population but not the one that hasn't been mutated
    def evaluate(self):
        for individual in self._Individuals:
            if individual.getFitnessFunction() is not None:
                continue
            individual.fitness(self._drone, self._map)

    # Performing a selection of k individuals from the population and returns that selection
    def selection(self, k=0):
        return choices(population=self._Individuals,
                       weights=[individual.getFitnessFunction() for individual in self._Individuals],
                       k=k)

    def extendPopulation(self):
        # Sort the individuals based on their fitness function
        self._Individuals = self.getSortedIndividuals()
        # Select the best 2 individuals to do a crossover between
        selection = self.selection(2)
        # Perform the crossover
        offSprings = selection[0].crossover(selection[1])

        # Mutate the offSprings
        offSprings[0].mutate()
        offSprings[1].mutate()
        # Replace the weakest individuals with the offSprings
        self._Individuals[-1] = offSprings[0]
        self._Individuals[-2] = offSprings[1]

        # Reevaluate the Individuals (the newly added once)
        self.evaluate()
