from queue import PriorityQueue
from taks1.Model.Constants import *
from taks1.Model.Map import Map


class Service:
    def __init__(self, mapM: Map, droneD, initialX, initialY, finalX, finalY):
        self._map = mapM
        self._drone = droneD

        self.initialX = initialX
        self.initialY = initialY
        self.finalX = finalX
        self.finalY = finalY

    @property
    def drone(self):
        return self._drone

    @property
    def map(self):
        return self._map

    @property
    def map_row(self):
        return self._map.rows

    @property
    def map_columns(self):
        return self._map.columns

    def isInMap(self, x, y):
        if 0 <= x <= (self._map.rows - 1) and 0 <= y <= (self._map.columns - 1):
            return True
        return False

    def heuristic(self, x, y):
        return abs(x - self.finalX) + abs(y - self.finalY)

    def reconstructPath(self, previous, destX, destY):
        path = []
        current = (destX, destY)

        while current != (self.initialX, self.initialY):
            path.append(current)
            current = previous[current]

        path.append(current)
        return reversed(path)

    def searchAStar(self):
        # TO DO
        # implement the search function and put it in controller
        # returns a list of moves as a list of pairs [x,y]

        visited = [[self.initialX, self.initialY]]
        previous = {}

        # represents the g function from the formula
        distances = {(self.initialX, self.initialY): 0}

        to_visit = PriorityQueue()
        to_visit.put((0, [self.initialX, self.initialY]))

        while not to_visit.empty():
            # the position in the map -> pos[0] = x // pos[1] = y
            pos = to_visit.get()[1]
            if pos == (self.finalX, self.finalY):
                return

            for direction in DIRECTIONS:
                new_x = pos[0] + direction[0]
                new_y = pos[1] + direction[1]

                if self.isInMap(new_x, new_y) and self._map.surface[new_x][new_y] == 0:
                    if [new_x, new_y] not in visited:
                        previous[(new_x, new_y)] = (pos[0], pos[1])
                        visited.append([new_x, new_y])

                        distances[(new_x, new_y)] = distances[(pos[0], pos[1])] + 1
                        path_cost = self.heuristic(new_x, new_y) + distances[(new_x, new_y)]
                        to_visit.put((path_cost, [new_x, new_y]))

        if previous[(self.finalX, self.finalY)] == (self.finalX, self.finalY):
            return []

        reconstructed_path = self.reconstructPath(previous, self.finalX, self.finalY)
        return list(reconstructed_path)

    def searchGreedy(self):
        # TO DO
        # implement the search function and put it in controller
        # returns a list of moves as a list of pairs [x,y]

        visited = [[self.initialX, self.initialY]]
        previous = {}

        # represents the g function from the formula
        distances = {(self.initialX, self.initialY): 0}

        to_visit = PriorityQueue()
        to_visit.put((0, [self.initialX, self.initialY]))

        while not to_visit.empty():
            # the position in the map -> pos[0] = x // pos[1] = y
            pos = to_visit.get()[1]
            if pos == (self.finalX, self.finalY):
                return

            for direction in DIRECTIONS:
                new_x = pos[0] + direction[0]
                new_y = pos[1] + direction[1]

                if self.isInMap(new_x, new_y) and self._map.surface[new_x][new_y] == 0:
                    if [new_x, new_y] not in visited:
                        previous[(new_x, new_y)] = (pos[0], pos[1])
                        visited.append([new_x, new_y])

                        distances[(new_x, new_y)] = distances[(pos[0], pos[1])] + 1
                        path_cost = self.heuristic(new_x, new_y)
                        to_visit.put((path_cost, [new_x, new_y]))

        if previous[(self.finalX, self.finalY)] == (self.finalX, self.finalY):
            return []

        reconstructed_path = self.reconstructPath(previous, self.finalX, self.finalY)
        return list(reconstructed_path)

    def dummysearch(self):
        # example of some path in test1.map from [5,7] to [7,11]
        return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]

    def intersection(self, lst1, lst2):
        return list(set(lst1) & set(lst2))
