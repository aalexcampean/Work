from random import randint

import pygame
from pygame.constants import K_LEFT, K_RIGHT, KEYDOWN
import time

from taks1.Model.Constants import *
from taks1.Model.Drone import Drone
from taks1.Model.Map import Map
from taks1.Service.Service import *


class Ui:
    def __init__(self):
        # creating the map
        self.map = Map()
        self.map.loadMap("test1.map")

        # creating and randomly positioning the drone
        x = randint(0, 19)
        y = randint(0, 19)
        self.drone = Drone(x, y)

        # initializing the service
        self.service = Service(self.map, self.drone, x, y, 4, 0)

        self.screen = None

    def createGame(self):
        # initialize the pygame module
        pygame.init()
        # load and set the logo
        logo = pygame.image.load("logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Path in simple environment")

        # create a surface on screen that has the size of 400 x 480
        self.screen = pygame.display.set_mode((400, 400))
        self.screen.fill(OFFWHITE)

    def image(self, colour=ORANGE, background=OFFWHITE):
        imagine = pygame.Surface((400, 400))
        brick = pygame.Surface((20, 20))
        brick.fill(ORANGE)
        imagine.fill(OFFWHITE)
        for i in range(self.map.rows):
            for j in range(self.map.columns):
                if self.map.surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))

        return imagine

    def displayWithPath(self, image, path1, path2, path3, color1, color2, color3):
        mark = pygame.Surface((20, 20))
        mark.fill(color1)

        for move1 in path1:
            image.blit(mark, (move1[1] * 20, move1[0] * 20))

        mark.fill(color2)
        for move2 in path2:
            image.blit(mark, (move2[1] * 20, move2[0] * 20))

        mark.fill(color3)
        for move3 in path3:
            image.blit(mark, (move3[1] * 20, move3[0] * 20))

        return image

    def mapWithDrone(self, mapImage):
        drona = pygame.image.load("drona.png")
        mapImage.blit(drona, (self.drone.y * 20, self.drone.x * 20))

        return mapImage

    def main(self):
        # creating the game
        self.createGame()

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

                if event.type == KEYDOWN:
                    greedy_start_time = time.time()
                    greedy_path = self.service.searchGreedy()
                    print(f"Greedy finished in: {time.time() - greedy_start_time}")

                    astar_start_time = time.time()
                    astar_path = self.service.searchAStar()
                    print(f"A Star finished in: {time.time() - astar_start_time}")

                    # # colors the greedy path
                    # self.screen.blit(self.displayWithPath(self.image(), greedy_path, DARKOLIVE), (0, 0))
                    # pygame.time.delay(200)
                    # pygame.display.flip()
                    #
                    # # color the astar path
                    # self.screen.blit(self.displayWithPath(self.image(), astar_path, SAND), (0, 0))
                    # pygame.time.delay(200)
                    # pygame.display.flip()

                    # color the common path
                    self.screen.blit(self.displayWithPath(self.image(), greedy_path, astar_path, self.service.intersection(greedy_path, astar_path), DARKOLIVE, SAND, GREEN), (0, 0))
                    pygame.display.flip()

                else:
                    self.screen.blit(self.mapWithDrone(self.image()), (0, 0))
                    pygame.display.flip()

        # path = self.service.dummysearch()

        pygame.display.flip()
        pygame.quit()
