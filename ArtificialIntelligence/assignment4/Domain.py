# -*- coding: utf-8 -*-
import math
import numpy as np
from queue import PriorityQueue

from random import *
from utils import *


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

    def setPosition(self, x, y):
        self._xCoordinate = x
        self._yCoordinate = y


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

    def setField(self, x, y, inputValue):
        self._surface[x][y] = inputValue

    def randomMap(self, fill=0.2):
        for i in range(self._n):
            for j in range(self._m):
                if random() <= fill:
                    self._surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self._n):
            for j in range(self._m):
                string = string + str(int(self._surface[i][j])) + "  "
            string = string + "\n"
        return string


class Sensor:
    def __init__(self, x, y, map: Map):
        self._x = x
        self._y = y
        self._map = map

        self._maxEnergy = 0
        self._explorationPerEnergy = [0 for _ in range(6)]

    def getX(self):
        return self._x

    def getY(self):
        return self._y

    def getCoordinates(self):
        return self._x, self._y

    def getMaxEnergy(self):
        return self._maxEnergy

    def setMaxEnergy(self, energyLevel):
        self._maxEnergy = energyLevel

    def getExploredPositions(self):
        return self._explorationPerEnergy

    def getExploredPosition(self, key):
        return self._explorationPerEnergy[key]

    def setExploredPosition(self, key, value):
        self._explorationPerEnergy[key] = value

    def isInMap(self, x, y):
        return 0 <= x <= (self._map.getRows() - 1) and 0 <= y <= (self._map.getColumns() - 1)

    def isValidPosition(self, x, y):
        return self.isInMap(x, y) and self._map.getSurface()[x][y] != 1

    def detectMaximumExploration(self):
        # computing the number of explored places for each energy level
        blockedDirections = [False for _ in range(4)]

        # exploring for all energy levels
        for energyLevel in range(1, 6):
            # when starting, the number of explored places is the same as the one fot the previous energy level
            self._explorationPerEnergy[energyLevel] = self._explorationPerEnergy[energyLevel - 1]

            directionCount = 0
            # exploring in all directions
            for direction in directions:
                if not blockedDirections[directionCount]:
                    nextX = self._x + direction[0] * energyLevel
                    nextY = self._y + direction[1] * energyLevel
                    if self.isValidPosition(nextX, nextY):
                        self._explorationPerEnergy[energyLevel] += 1
                    else:
                        blockedDirections[directionCount] = True

                directionCount += 1

    def detectMaximumEnergyLevel(self):
        # computing the amount of energy the sensor should be charge with
        # by default, we suppose the maximum energy required is 5
        self._maxEnergy = 5
        for energyLevel in range(5):
            # when the number of explored positions is the same for 2 continious energy levels
            # => the sensor's explorations stops there
            if self._explorationPerEnergy[energyLevel] == self._explorationPerEnergy[energyLevel + 1]:
                self._maxEnergy = energyLevel
                return


class Sensors:
    def __init__(self, map: Map):
        self._map = map
        self._listOfSensors = []
        self._distances = [[0 for _ in range(nrOfSensors)] for _ in range(nrOfSensors)]

        self.randomlyPlaceSensors()
        self.findDistanceBetweenSensors()
        self.findPossibleExploration()

    def getMap(self):
        return self._map

    def getSensors(self):
        return self._listOfSensors

    def getSensor(self, index):
        return self._listOfSensors[index]

    def getDistances(self):
        return self._distances

    def isInMap(self, x, y):
        return 0 <= x <= (self._map.getRows() - 1) and 0 <= y <= (self._map.getColumns() - 1)

    def isValidPosition(self, x, y):
        return self.isInMap(x, y) and self._map.getSurface()[x][y] != 1

    def heuristic(self, x, y, endX, endY):
        return abs(x - endX) + abs(y - endY)

    def aStar(self, startX, startY, endX, endY):
        # represents the g function from the formula
        distances = {(startX, startY): 0}
        visited = [(startX, startY)]

        toVisit = PriorityQueue()
        toVisit.put((0, [startX, startY]))

        while not toVisit.empty():
            pos = toVisit.get()[1]
            if (pos[0], pos[1]) == (endX, endY):
                return distances[(endX, endY)]

            for direction in directions:
                newX = pos[0] + direction[0]
                newY = pos[1] + direction[1]
                if self.isValidPosition(newX, newY) and (newX, newY) not in visited:
                    visited.append((newX, newY))

                    distances[(newX, newY)] = distances[(pos[0], pos[1])] + 1
                    pathCost = self.heuristic(newX, newY, endX, endY) + distances[(newX, newY)]
                    toVisit.put((pathCost, [newX, newY]))
        return math.inf

    def findDistanceBetweenSensors(self):
        # Using A* to find the shortest distance between sensors
        for sensor1 in range(len(self._listOfSensors)):
            for sensor2 in range(len(self._listOfSensors)):
                firstSensorX = self._listOfSensors[sensor1].getX()
                firstSensorY = self._listOfSensors[sensor1].getY()
                secondSensorX = self._listOfSensors[sensor2].getX()
                secondSensorY = self._listOfSensors[sensor2].getY()

                distanceBetween = self.aStar(firstSensorX, firstSensorY, secondSensorX, secondSensorY)
                # the distance between 2 sensors is the same starting from one or the other
                self._distances[sensor1][sensor2] = self._distances[sensor2][sensor1] = distanceBetween

    def findPossibleExploration(self):
        # getting the maximum energy level each sensor should be charged with
        for sensor in self._listOfSensors:
            sensor.detectMaximumExploration()
            sensor.detectMaximumEnergyLevel()

    def randomlyPlaceSensors(self):
        for i in range(nrOfSensors):
            xPosition = randrange(20)
            yPosition = randrange(20)

            while self._map.getSurface()[xPosition][yPosition] != 0:
                xPosition = randrange(20)
                yPosition = randrange(20)

            self._map.setField(xPosition, yPosition, 2)
            self._listOfSensors.append(Sensor(xPosition, yPosition, self._map))


class Ant:
    def __init__(self):
        self._path = [randrange(nrOfSensors)]
        self._fitness = 0
        self._batteryLevel = batterLife

    def getPath(self):
        return self._path

    def getFitness(self):
        return self._fitness

    def getBatteryLife(self):
        return self._batteryLevel

    def isSensorVisited(self, sensor):
        return sensor not in self._path

    def isBatteryLevelOptimal(self, sourceSensor, targetSensor, distancesMap):
        return self._batteryLevel >= distancesMap[sourceSensor][targetSensor]

    def isDistanceValid(self, sourceSensor, targetSensor, distancesMap):
        return sourceSensor != targetSensor and distancesMap[sourceSensor][targetSensor] != math.inf

    def getPossibleSensors(self, distancesMap):
        # retrieving the accessible sensors
        moves = []
        currentSensor = self._path[-1]
        # saving the next possible and valid move
        for nextSensor in range(nrOfSensors):
            if nextSensor != currentSensor \
                    and distancesMap[currentSensor][nextSensor] != math.inf \
                    and self.isSensorVisited(nextSensor) \
                    and self.isBatteryLevelOptimal(currentSensor, nextSensor, distancesMap):
                moves.append(nextSensor)
        return moves

    def probabilityOfChoosingNextSensor(self, possibleMoves, distancesMap, pheromonesMap, alpha, beta):
        currentSensor = self._path[-1]
        probabilitiesNextSensor = [0 for _ in range(nrOfSensors)]
        # computing the probabilities of choosing the next possible moves
        for nextSensor in possibleMoves:
            # the cost of the path to the next sensor
            distanceToNextSensor = distancesMap[currentSensor][nextSensor]
            # the amount of pheromones left on the path
            amountOfPheromones = pheromonesMap[currentSensor][nextSensor]

            # the probability = the pheromone level on that trail + 1 / the cost of the trail
            # doing this, we encourage taking into consideration the quality of an edge
            probability = amountOfPheromones ** alpha * (1 / distanceToNextSensor) ** beta
            probabilitiesNextSensor[nextSensor] = probability

        # computing the sum of all edges
        probabilitiesSum = sum(probabilitiesNextSensor)

        # dividing the values by the sum
        # => this way the better moves have a better probability of being chosen
        for sensor in possibleMoves:
            probabilitiesNextSensor[sensor] /= probabilitiesSum

        return probabilitiesNextSensor

    # assuming alpha and beta are 1 for simplicity
    def chooseNextMove(self, distancesMap, pheromonesMap, probability=0.5, alpha=1, beta=1):
        # getting all the possible next moves
        moves = self.getPossibleSensors(distancesMap)
        # checking if there are any possible moves
        if not moves:
            return False

        nextMovesProbabilities = self.probabilityOfChoosingNextSensor(moves, distancesMap, pheromonesMap, alpha, beta)
        nextMove = self.rouletteWheel(nextMovesProbabilities)

        self._batteryLevel -= distancesMap[self._path[-1]][nextMove]
        self._path.append(nextMove)
        return True

    def rouletteWheel(self, probabilitiesNextSensor):
        cumulativeSum = [0 for _ in range(nrOfSensors)]
        for i in range(len(probabilitiesNextSensor)):
            listToRight = probabilitiesNextSensor[i:]
            cumulativeSum[i] = sum(listToRight)

        randomProbability = random()
        for i in range(len(probabilitiesNextSensor) - 1):
            if cumulativeSum[i] >= randomProbability > cumulativeSum[i + 1]:
                return i
        return len(probabilitiesNextSensor) - 1

    def computeFitness(self, distances):
        # considering the fitness to be the distance between 2 sensors
        self._fitness = 0
        for i in range(1, len(self._path)):
            self._fitness += distances[self._path[i - 1]][self._path[i]]


if __name__ == "__main__":
    newMap = Map()
    newMap.randomMap()
    sensors = Sensors(newMap)
    sensors.findDistanceBetweenSensors()
    sensors.findPossibleExploration()

    print(newMap)
