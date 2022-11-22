from Domain import *


class Controller:
    def __init__(self):
        self._map = Map()
        self.createRandomMap()
        self._sensors = Sensors(self._map)

        self._drone = Drone(0, 0)
        self.placeDrone()

        self._pheromoneMap = [[1.0 for _ in range(nrOfSensors)] for _ in range(nrOfSensors)]
        self._distanceMap = self._sensors.getDistances()

        self._bestPath = []

    def getMap(self):
        return self._map

    def getMapRows(self):
        return self._map.getRows()

    def getMapColumns(self):
        return self._map.getColumns()

    def getMapSurface(self):
        return self._map.getSurface()

    def getDroneXCoord(self):
        return self._drone.getX()

    def getDroneYCoord(self):
        return self._drone.getY()

    def getSensors(self):
        return self._sensors

    def getSensor(self, index):
        return self._sensors.getSensor(index)

    def getBestPath(self):
        return self._bestPath

    def moveAnts(self, ants, alpha, beta, q0):
        antColony = ants
        for ant in ants:
            for step in range(nrOfSensors - 1):
                found = ant.chooseNextMove(self._distanceMap, self._pheromoneMap, q0, alpha, beta)
                # keeping only the ants that can complete the path
                # computing the fitness for the ones that do
                if not found:
                    antColony.remove(ant)
                else:
                    ant.computeFitness(self._distanceMap)
        return antColony

    @staticmethod
    def getBestAnt(ants):
        bestAnt = ants[0]
        bestFitness = 0
        for ant in ants:
            if bestFitness < ant.getFitness():
                bestFitness = ant.getFitness()
                bestAnt = ant
        return bestAnt

    def simulateEpoch(self, nrAnts=nrOfSensors * 5, alpha=1, beta=1, probability=0.5, evaporation=0.05):
        # creating the antColony
        antColony = [Ant() for _ in range(nrAnts)]
        # moving the ants
        antColony = self.moveAnts(antColony, alpha, beta, probability)

        # creating the pheromone map
        for i in range(nrOfSensors):
            for j in range(nrOfSensors):
                # ants living pheromones on their path
                self._pheromoneMap[i][j] = (1 - evaporation) * self._pheromoneMap[i][j]

        # stopping in case all ants failed to complete their path
        if not antColony:
            return None

        # leaving more pheromones on the best path
        # this is done by dividing 1 to the total length of the path chosen by the ant (shorter paths -> better results)
        newPheromoneTrail = [1.0 / ant.getFitness() for ant in antColony]
        for i in range(len(antColony)):
            antPath = antColony[i].getPath()
            for j in range(len(antPath) - 1):
                currentSensor = antPath[j]
                nextSensor = antPath[j + 1]
                self._pheromoneMap[currentSensor][nextSensor] += newPheromoneTrail[i]

        return self.getBestAnt(antColony)

    def findBestSolution(self, bestSolution):
        # simulating an epoch
        currentSolution = self.simulateEpoch()
        # if all ants failed, we stop
        if currentSolution is None:
            return bestSolution

        # checking to see if the current solution is the best one
        if bestSolution is None \
                or len(currentSolution.getPath()) > len(bestSolution.getPath()) \
                or (len(currentSolution.getPath()) == len(bestSolution.getPath()) and currentSolution.getFitness() < bestSolution.getFitness()):
            return currentSolution
        return bestSolution

    def chargeSensors(self, remainingBattery, accessibleSensors):
        # getting the accessible sensors
        sensorList = []
        for i in range(len(self._sensors.getSensors())):
            if i in accessibleSensors:
                sensorList.append(self._sensors.getSensors()[i])

        # setting the energy levels to 0 (not charged)
        sensorEnergyLevels = [0 for _ in sensorList]

        # checking if the battery ran out
        if remainingBattery <= 0:
            return sensorEnergyLevels

        # sorting the sensors based on their accessibility and potential
        sensorList.sort(key=lambda sensor: (sensor.getExploredPositions()[-1] / sensor.getMaxEnergy()))

        # reconstructing the path and charging the sensors
        for i in range(len(sensorList)):
            if remainingBattery <= 0:
                break

            # retrieving the maximum level of energy it can receive to explore to its fullest potential
            currentSensorMaxEnergy = sensorList[i].getMaxEnergy()

            # checking if we have enough battery for it
            # if we do, we charge the sensor with the required amount
            # otherwise we charge the remaining amount of the drone
            if remainingBattery > currentSensorMaxEnergy:
                remainingBattery -= currentSensorMaxEnergy
                sensorEnergyLevels[i] = currentSensorMaxEnergy
            else:
                sensorEnergyLevels[i] = remainingBattery
                remainingBattery = 0

        # returning the energy levels charged in each sensor
        return sensorEnergyLevels

    def runACO(self, epochCount=1000):
        bestSolution = None

        for epoch in range(epochCount):
            bestSolution = self.findBestSolution(bestSolution)

        self._bestPath = bestSolution.getPath()
        energyLevels = self.chargeSensors(batterLife - bestSolution.getFitness(), bestSolution.getPath())

        print("Best path (sensors in order): ")
        for indices in bestSolution.getPath():
            print(self._sensors.getSensors()[indices].getCoordinates(), end=" ")
        print("\nEnergy left in each sensor: ", energyLevels)

    def placeDrone(self):
        # placing the drone on a valid position
        x, y = randrange(mapLength), randrange(mapLength)
        while self._map.getSurface()[x][y] == 1:
            x, y = randrange(mapLength), randrange(mapLength)
        self._drone.setPosition(x, y)

    def createRandomMap(self):
        self._map.randomMap()
