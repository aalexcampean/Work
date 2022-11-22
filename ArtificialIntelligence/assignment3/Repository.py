# -*- coding: utf-8 -*-

import pickle
from Domain import *


class Repository:
    def __init__(self):
        self._populations = []
        self._map = Map()
        self._drone = Drone(randrange(20), randrange(20), 10)

    def getPopulations(self):
        return self._populations

    def getLastPopulation(self):
        return self._populations[-1]

    def getBestPathInLastPopulation(self):
        # Returning the path of the individual with the best fitness from the last population
        return self._populations[-1].getBestPath()

    def getMap(self):
        return self._map

    def getMapRows(self):
        return self._map.getRows()

    def getMapColumns(self):
        return self._map.getColumns()

    def createPopulation(self, args):
        # args = [populationSize, individualSize] -- you can add more args
        self._populations.append(Population(self._drone, self._map, args[0], args[1]))

    def createRandomMap(self):
        self._map.randomMap()

    def saveMap(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def loadMap(self, numfile):
        with open(numfile, "rb") as f:
            dummy = pickle.load(f)
            self._map.setN(dummy.getMap().getRows())
            self._map.setN(dummy.getMap().getColumns())
            self._map.setSurface(dummy.getMap().getSurface())
            f.close()
            