import numpy as np


class DMap():
    def __init__(self):
        self._n = 20
        self._m = 20
        self._surface = np.zeros((self._n, self._m))
        for i in range(self._n):
            for j in range(self._m):
                self._surface[i][j] = -1

    @property
    def n(self):
        return self._n

    @property
    def m(self):
        return self._m

    @property
    def surface(self):
        return self._surface
