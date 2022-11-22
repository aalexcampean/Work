import pygame
from pygame.locals import *

from Constants import *


class Drone():
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.visited = []
        self.stack = [(x, y)]
        self.inverse_stack = []

    def move(self, detectedMap):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[K_UP] and detectedMap.surface[self.x - 1][self.y] == 0:
                self.x = self.x - 1
        if self.x < 19:
            if pressed_keys[K_DOWN] and detectedMap.surface[self.x + 1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[K_LEFT] and detectedMap.surface[self.x][self.y - 1] == 0:
                self.y = self.y - 1
        if self.y < 19:
            if pressed_keys[K_RIGHT] and detectedMap.surface[self.x][self.y + 1] == 0:
                self.y = self.y + 1

    def isMoveValid(self, detectedMap, x, y):
        if 0 <= x <= 19 and 0 <= y <= 19 and detectedMap.surface[x][y] == 0 and (x, y) not in self.visited:
            return True
        else:
            return False

    def moveDSF(self, detectedMap):
        # TO DO!
        # rewrite this function in such a way that you perform an automatic
        # mapping with DFS

        if len(self.stack) > 0:
            self.visited.append((self.x, self.y))

            for direction in v:
                next_x = self.x + direction[0]
                next_y = self.y + direction[1]
                if self.isMoveValid(detectedMap, next_x, next_y):
                    self.stack.append((next_x, next_y))
            self.x, self.y = self.stack.pop()

        else:
            raise Exception("The drone finished exploring the map!")
