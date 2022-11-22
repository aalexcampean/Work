from random import randint
import pygame

from Controller import Controller
from DMap import DMap
from Drone import Drone
from Environment import Environment
from Constants import *

class UI() :
    def __init__(self):
        self._controller = Controller()

    def DMapImage(self, d_map: DMap, x, y):
        imagine = pygame.Surface((420, 420))
        brick = pygame.Surface((20, 20))
        empty = pygame.Surface((20, 20))
        empty.fill(BEIGE)
        brick.fill(ORANGE)
        imagine.fill(DARKOLIVE)

        for i in range(d_map.n):
            for j in range(d_map.m):
                if d_map.surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))
                elif d_map.surface[i][j] == 0:
                    imagine.blit(empty, (j * 20, i * 20))

        drona = pygame.image.load("drona.png")
        imagine.blit(drona, (y * 20, x * 20))
        return imagine

    def EnvironmentImage(self, e:Environment):
        imagine = pygame.Surface((420, 420))
        brick = pygame.Surface((20, 20))
        brick.fill(ORANGE)
        imagine.fill(BEIGE)
        for i in range(e.n):
            for j in range(e.m):
                if e.surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))

        return imagine

    def ui(self):
        # # we create the environment
        # e = Environment()
        # e.loadEnvironment("test2.map")
        # # print(str(e))
        #
        # # we create the map
        # m = DMap()

        # initialize the pygame module
        pygame.init()
        # load and set the logo
        logo = pygame.image.load("logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("drone exploration")

        # we position the drone somewhere in the area
        x = randint(0, 19)
        y = randint(0, 19)

        # we create drona
        d = Drone(x, y)

        # create a surface on screen that has the size of 800 x 480
        screen = pygame.display.set_mode((800, 400))
        screen.fill(BEIGE)
        screen.blit(self.EnvironmentImage(self._controller.environment), (0, 0))

        # define a variable to control the main loop
        running = True
        # main loop
        while running:
            # event handling, gets all event from the event queue
            for event in pygame.event.get():
                # only do something if the event is of type QUIT
                if event.type == pygame.QUIT:
                    # change the value to False, to exit the main loop
                    running = False
                # if event.type == KEYDOWN:
                #     # use this function instead of move
                #     d.move(m)

            self._controller.markDetectedWalls(d.x, d.y)
            try:
                d.moveDSF(self._controller.d_map)
                pygame.time.delay(200)

            except Exception as e:
                print(e)
                running = False

            screen.blit(self.DMapImage(self._controller.d_map, d.x, d.y), (400, 0))
            pygame.display.flip()

        pygame.quit()