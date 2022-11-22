# -*- coding: utf-8 -*-

from pygame.locals import *
import pygame

from Controller import *


class GUI:
    def __init__(self, controller):
        self.initPyGame()
        self.screen = pygame.display.set_mode((400, 400))
        self.screen.fill(OFFWHITE)
        self.controller = controller

    def initPyGame(self):
        # init the pygame
        pygame.init()
        logo = pygame.image.load("logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("ACO")

    def closePyGame(self):
        # closes the pygame
        running = True
        # loop for events
        while running:
            # event handling, gets all event from the event queue
            for event in pygame.event.get():
                # only do something if the event is of type QUIT
                if event.type == pygame.QUIT:
                    # change the value to False, in order to exit the main loop
                    running = False
        pygame.quit()

    def imageMap(self, colour=ORANGE, background=OFFWHITE, colour2=GREEN):
        imagine = pygame.Surface((mapLength * 20, mapLength * 20))
        # marking walls
        brick = pygame.Surface((20, 20))
        brick.fill(colour)
        # marking sensors
        sensor = pygame.Surface((20, 20))
        sensor.fill(colour2)
        # marking the background
        imagine.fill(background)
        # marking the best path
        coloredPath = pygame.Surface((20, 20))
        coloredPath.fill(SAND)

        mapSurface = self.controller.getMapSurface()
        for i in range(mapLength):
            for j in range(mapLength):
                if mapSurface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))
                if mapSurface[i][j] == 2:
                    imagine.blit(sensor, (j * 20, i * 20))

        # TODO: color the map explored by the sensors, taking into account the remaining energy level in each one
        return imagine

    def displayMap(self):
        droneImage = pygame.image.load("drona.png")
        pathImage = self.imageMap()
        pathImage.blit(droneImage, (self.controller.getDroneYCoord() * 20, self.controller.getDroneXCoord() * 20))
        self.screen.blit(pathImage, (0, 0))
        pygame.display.update()
        while True:
            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    return
            pygame.time.wait(1)

    def startGUI(self):
        self.controller.runACO()
        self.displayMap()
