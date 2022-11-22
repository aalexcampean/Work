import pickle
from random import random
import numpy as np


class Environment():
    def __init__(self):
        self._n = 20
        self._m = 20
        self._surface = np.zeros((self._n, self._m))

    @property
    def n(self):
        return self._n

    @property
    def m(self):
        return self._m

    @property
    def surface(self):
        return self._surface

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

    def saveEnvironment(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def loadEnvironment(self, numfile):
        with open(numfile, "rb") as f:
            dummy = pickle.load(f)
            self._n = dummy.__n
            self._m = dummy.__m
            self._surface = dummy.__surface
            f.close()