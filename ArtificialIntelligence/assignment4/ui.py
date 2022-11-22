# -*- coding: utf-8 -*-


# imports
import matplotlib.pyplot as plot

from gui import *
from Controller import *
from Repository import *
from Domain import *


class UI:
    def __init__(self):
        self.repo = Repository()
        self._controller = Controller(self.repo)
        self._drone = Drone(randrange(20), randrange(20))

    def printMenu(self):
        print("1. Map options")
        print("2. Find the order in which the sensors will be visited")
        print("0. Exit")

    def printMapMenu(self):
        print("1. Create random map")
        print("2. Load a map")
        print("3. Save a map")
        print("4. Visualize map")
        print("5. Generate random sensors")
        print("0. Exit")

    def createRandomMap(self):
        self._controller.createRandomMap()
        fileName = input("The name of the file for the random map to be saved in:\n")
        self._controller.saveMapService(fileName)

    def loadMap(self):
        fileName = input("The name of the file to be loaded from:\n")
        self._controller.loadMapService(fileName)

    def saveMap(self):
        fileName = input("The name of the file for the map to be saved in:\n")
        self._controller.saveMapService(fileName)

    def visualizeMap(self):
        # screen = initPyGame((self._controller.getMapRows() * 20, self._controller.getMapColumns() * 20))
        # for i in range(20):
        #     screen.blit(image(self._controller.getMap()), (0, 0))
        # pygame.display.flip()
        # closePyGame()
        screen = initPyGame((self._controller.getMapRows() * 20, self._controller.getMapColumns() * 20))
        screen.blit(imageMap(self._controller), (0, 0))
        pygame.display.flip()
        closePyGame()


    def generateRandomSensors(self):
        pass
        # TODO: Implement this

    def handleMapMenu(self):
        done = False
        while not done:
            self.printMapMenu()
            optionMap = input("Please choose an option:\n")

            if optionMap == "1":
                self.createRandomMap()
                pass

            elif optionMap == "2":
                self.loadMap()

            elif optionMap == "3":
                self.saveMap()

            elif optionMap == "4":
                self.visualizeMap()

            elif optionMap == "5":
                pass

            elif optionMap == "0":
                done = True

            else:
                print("Unknown option")

    def findSensorVisitingOrder(self):
        pass
        # TODO: Add implementation

    def startUI(self):
        done = False

        while not done:
            self.printMenu()
            option1 = input("Please choose an option:\n")
            if option1 == "1":
                self.handleMapMenu()
            elif option1 == "2":
                self.findSensorVisitingOrder()
            else:
                print("Exiting")
                done = True


if __name__ == "__main__":
    ui = UI()
    ui.startUI()
