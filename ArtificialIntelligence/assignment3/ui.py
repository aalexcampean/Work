# -*- coding: utf-8 -*-


# imports
import matplotlib.pyplot as plot

from gui import *
from Controller import *
from Repository import *
from Domain import *


# create a menu
#   1. map options:
#         a. create random map
#         b. load a map
#         c. save a map
#         d visualise map
#   2. EA options:
#         a. parameters setup
#         b. run the solver
#         c. visualise the statistics
#         d. view the drone moving on a path
#              function gui.movingDrone(currentMap, path, speed, markseen)
#              ATTENTION! the function doesn't check if the path passes through walls

class UI:
    def __init__(self):
        self.__nrOfGenerations = 20
        self._individualSize = 100
        self._populationSize = 50
        self.__nrOfIterations = 100
        self.repo = Repository()
        self._controller = Controller(self.repo)
        self._drone = Drone(randrange(20), randrange(20))
        self._bestPath = []
        self._fitnessFunctions = []

    def printMenu(self):
        print("1. Map options")
        print("2. EA options")
        print("0. Exit")

    def printMapMenu(self):
        print("1. Create random map")
        print("2. Load a map")
        print("3. Save a map")
        print("4. Visualize map")
        print("0. Exit")

    def printEAMenu(self):
        print("1. Parameters setup")
        print("2. Run the solver")
        print("3. Visualise the statistics")
        print("4. View the drone moving on a path")
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
        screen = initPyGame((self._controller.getMapRows() * 20, self._controller.getMapColumns() * 20))
        for i in range(20):
            screen.blit(image(self._controller.getMap()), (0, 0))
        pygame.display.flip()
        closePyGame()

    def plotGraph(self, solutionAverages):
        plot.plot(solutionAverages)
        plot.savefig("plotAvgFitness.png")
        plot.show()

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

            elif optionMap == "0":
                done = True

            else:
                print("Unknown option")

    def handleEAMenu(self):
        done = False
        while not done:
            self.printEAMenu()
            optionEA = input("Please choose an option:\n")

            if optionEA == "1":
                self._populationSize = input("Population size: ")
                self._individualSize = input("Number of individuals: ")
                self.__nrOfGenerations = input("Number of generations: ")
                self.__nrOfIterations = input("Number of iterations: ")

            elif optionEA == "2":
                # Marking the staring time
                startTime = time.time()
                self._bestPath, self._fitnessFunctions = self._controller.solver(self.__nrOfIterations,
                                                                                 self._populationSize,
                                                                                 self._individualSize)
                # Marking the ending time
                endTime = time.time()

                # Printing the time performance
                print(f"Execution Time: {endTime - startTime} seconds")
                # Plotting the graph
                self.plotGraph(self._fitnessFunctions)

            elif optionEA == "3":
                fitness = []
                for i in range(30):
                    randSeed = randint(0, 100)
                    seed(randSeed)
                    self._bestPath, self._fitnessFunctions = self._controller.solver(self.__nrOfIterations,
                                                                                     self._populationSize,
                                                                                     self._individualSize)
                    fitness.append(np.average(self._fitnessFunctions))
                    print(f'Run: {i + 1}, with Seed: {str(randSeed)}, and Fitness: {fitness[-1]}')

                print(f"\nThe average is: {np.average(fitness)}")
                print(f"The standard deviation is: {np.std(fitness)}\n")

            elif optionEA == "4":
                movingDrone(self._controller.getMap(), self._bestPath, 0.2)

            elif optionEA == "0":
                done = True

            else:
                print("Unknown option")

    def startUI(self):
        done = False

        while not done:
            self.printMenu()
            option1 = input("Please choose an option:\n")
            if option1 == "1":
                self.handleMapMenu()
            elif option1 == "2":
                self.handleEAMenu()
            else:
                print("Exiting")
                done = True


if __name__ == "__main__":
    ui = UI()
    ui.startUI()