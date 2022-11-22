from Constants import *
from DMap import DMap
from Environment import Environment


class Controller():
    def __init__(self):
        self._e = Environment()
        self._e.loadEnvironment("test2.map")

        self._d_map = DMap()

    @property
    def environment(self):
        return self._e

    @property
    def d_map(self):
        return self._d_map

    def readUDMSensors(self,  x, y):
        readings = [0, 0, 0, 0]
        # UP
        xf = x - 1
        while (xf >= 0) and (self._e.surface[xf][y] == 0):
            xf = xf - 1
            readings[UP] = readings[UP] + 1
        # DOWN
        xf = x + 1
        while (xf < self._e.n) and (self._e.surface[xf][y] == 0):
            xf = xf + 1
            readings[DOWN] = readings[DOWN] + 1
        # LEFT
        yf = y + 1
        while (yf < self._e.m) and (self._e.surface[x][yf] == 0):
            yf = yf + 1
            readings[LEFT] = readings[LEFT] + 1
        # RIGHT
        yf = y - 1
        while (yf >= 0) and (self._e.surface[x][yf] == 0):
            yf = yf - 1
            readings[RIGHT] = readings[RIGHT] + 1

        return readings

    def markDetectedWalls(self, x, y):
        self._d_map.surface[x][y] = 0

        walls = self.readUDMSensors(x, y)
        i = x - 1
        if walls[UP] > 0:
            while (i >= 0) and (i >= x - walls[UP]):
                self._d_map.surface[i][y] = 0
                i = i - 1
        if i >= 0:
            self._d_map.surface[i][y] = 1

        i = x + 1
        if walls[DOWN] > 0:
            while (i < self._d_map.n) and (i <= x + walls[DOWN]):
                self._d_map.surface[i][y] = 0
                i = i + 1
        if i < self._d_map.n:
            self._d_map.surface[i][y] = 1

        j = y + 1
        if walls[LEFT] > 0:
            while (j < self._d_map.m) and (j <= y + walls[LEFT]):
                self._d_map.surface[x][j] = 0
                j = j + 1
        if j < self._d_map.m:
            self._d_map.surface[x][j] = 1

        j = y - 1
        if walls[RIGHT] > 0:
            while (j >= 0) and (j >= y - walls[RIGHT]):
                self._d_map.surface[x][j] = 0
                j = j - 1
        if j >= 0:
            self._d_map.surface[x][j] = 1

        return None