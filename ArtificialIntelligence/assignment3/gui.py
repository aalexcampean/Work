# -*- coding: utf-8 -*-

from pygame.locals import *
import pygame, time
from utils import *
from Domain import *


def initPyGame(dimension):
    # init the pygame
    pygame.init()
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("drone exploration with AE")

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode(dimension)
    screen.fill(OFFWHITE)
    return screen


def closePyGame():
    # closes the pygame
    running = True
    # loop for events
    while running:
        # event handling, gets all event from the event queue
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False
    pygame.quit()


def movingDrone(currentMap: Map, path, speed=1, markSeen=True):
    # animation of a drone on a path

    screen = initPyGame((currentMap.getRows() * 20, currentMap.getColumns() * 20))

    drona = pygame.image.load("drona.png")

    for i in range(len(path)):
        screen.blit(image(currentMap), (0, 0))

        if markSeen:
            brick = pygame.Surface((20, 20))
            brick.fill(GREEN)
            for j in range(i + 1):
                for var in directions:
                    x = path[j][0]
                    y = path[j][1]
                    while ((0 <= x + var[0] < currentMap.getRows() and
                            0 <= y + var[1] < currentMap.getColumns()) and
                           currentMap.getSurface()[x + var[0]][y + var[1]] != 1):
                        x = x + var[0]
                        y = y + var[1]
                        screen.blit(brick, (y * 20, x * 20))

        screen.blit(drona, (path[i][1] * 20, path[i][0] * 20))
        pygame.display.flip()
        time.sleep(0.5 * speed)
    closePyGame()


def image(currentMap, colour=ORANGE, background=OFFWHITE):
    # creates the image of a map

    imagine = pygame.Surface((currentMap.getRows() * 20, currentMap.getColumns() * 20))
    brick = pygame.Surface((20, 20))
    brick.fill(colour)
    imagine.fill(background)
    for i in range(currentMap.getRows()):
        for j in range(currentMap.getColumns()):
            if currentMap.getSurface()[i][j] == 1:
                imagine.blit(brick, (j * 20, i * 20))

    return imagine
