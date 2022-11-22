import copy
from random import randint

from Graph import DirectedGraph

class userInterface:

    def __init__(self):
        self._main_graph = DirectedGraph()
        self._copy_graph = DirectedGraph()

    def readGraph1(self, filename, my_graph: DirectedGraph):

        f = open(filename, 'rt')
        info = f.readline().split(' ')

        nr_vertices = int(info[0])
        nr_edges = int(info[1])

        for i in range(nr_vertices):
            my_graph.addVertex(i)

        for i in range(nr_edges):
            current_info = f.readline().split(' ')
            source_vertex = int(current_info[0])
            target_vertex = int(current_info[1])
            cost = int(current_info[2])
            my_graph.addEdge(source_vertex, target_vertex, cost)

        f.close()

    def readGraph2(self, filename, my_graph: DirectedGraph):

        f = open(filename, 'rt')
        lines = f.readlines()

        for line in lines:
            current_info = line.split(' ')
            source_vertex = int(current_info[0])

            if len(current_info) > 1:
                source_vertex = int(current_info[0])
                target_vertex = int(current_info[1])
                cost = int(current_info[2])

                my_graph.addVertex(source_vertex)
                my_graph.addVertex(target_vertex)
                my_graph.addEdge(source_vertex, target_vertex, cost)
            else:
                my_graph.addVertex(source_vertex)
        f.close()

    def saveGraph(self, filename, my_graph: DirectedGraph):

        f = open(filename, 'wt')

        for i in my_graph.getDictOut.keys():
            if my_graph.getDictOut[i] == [] and my_graph.getDictIn[i] == []:
                f.write(str(i) + '\n')
            else:
                for j in my_graph.getDictOut[i]:
                    f.write(str(i) + ' ' + str(j) + ' ' + str(my_graph.getCost(i, j)) + '\n')

        f.close()

    def createRandomGraph(self):
        new_graph = DirectedGraph()
        nr_vertices = int(input("Enter the number of vertices: "))
        nr_edges = int(input("Enter the number of edges: "))

        if nr_edges > nr_vertices * nr_vertices:
            raise ValueError(f'Impossible to create such a graph')

        for i in range(nr_vertices):
            new_graph.addVertex(i)

        i = 0
        while i <= nr_edges:
            source_vertex = randint(0, nr_vertices - 1)
            target_vertex = randint(0, nr_vertices - 1)
            cost = randint(-20, 20)
            if new_graph.addEdge(source_vertex, target_vertex, cost):
                i += 1

        return new_graph

    def printMenu(self):
        print('\n-----------------------------------------------------------------------------------------')
        print('|    1. Read from a file' + '12. Find if an edge exists'.rjust(60) + '|'.rjust(5))
        print('|    2. Save graph in a file' + '13. Add a vertex'.rjust(46) + '|'.rjust(15))
        print('|    3. Get number of vertices' + '14. Delete a vertex'.rjust(47) + '|'.rjust(12))
        print('|    4. Get number of edges' + '15. Add an edge'.rjust(46) + '|'.rjust(16))
        print('|    5. Get all vertices' + '16. Delete an edge'.rjust(52) + '|'.rjust(13))
        print('|    6. Get all edges' + '17. Update edge info'.rjust(57) + '|'.rjust(11))
        print('|    7. Get in and out degree of a vertex' + '18. Print graph'.rjust(32) + '|'.rjust(16))
        print('|    8. Get the inbound neighbours of a vertex' + '19. Copy graph'.rjust(26) + '|'.rjust(17))
        print('|    9. Get the outbound neighbours of a vertex' + '20. Create random graph'.rjust(34) + '|'.rjust(8))
        print('|    10. Get the cost of an edge' + '21. Find shortest path'.rjust(48) + '|'.rjust(9))
        print('|    11. Find if a vertex exists' + '0. Exit'.rjust(34) + '|'.rjust(23))
        print('-----------------------------------------------------------------------------------------\n')

    def startUi(self):
        self.printMenu()
        done = False

        while not done:
            try:
                option = int(input("\nEnter the number of the command: \n"))

                if option == 1:
                    desired_file = input("Enter the name of the file: ")
                    read_format = int(input("The reading format is (1. including number of vertices | 2. excluding the number of vertices): "))
                    if read_format == 1:
                        self.readGraph1(desired_file, self._main_graph)
                    elif read_format == 2:
                        self.readGraph2(desired_file, self._main_graph)
                    else:
                        print('No such format')

                elif option == 2:
                    desired_file = input("Enter the name of the file: ")
                    self.saveGraph(desired_file, self._main_graph)

                elif option == 3:
                    print('-----------------------------------------------------------------------------------------')
                    print(f'|    Number of vertices: {self._main_graph.getNrOfVertices}')
                    print('-----------------------------------------------------------------------------------------')

                elif option == 4:
                    print('-----------------------------------------------------------------------------------------')
                    print(f'|    Number of edges: {self._main_graph.getNrOfEdges}')
                    print('-----------------------------------------------------------------------------------------')

                elif option == 5:
                    print('-----------------------------------------------------------------------------------------')
                    print(f'|    The vertices: {self._main_graph.getAllVertices}')
                    print('-----------------------------------------------------------------------------------------')

                elif option == 6:
                    print('-----------------------------------------------------------------------------------------')
                    print(f'|    The edges: {self._main_graph.getAllEdges}')
                    print('-----------------------------------------------------------------------------------------')

                elif option == 7:
                    desired_vertex = int(input('Enter the desired vertex: '))
                    neighbours = self._main_graph.getInDegreeAndOutDegree(desired_vertex)
                    print('-----------------------------------------------------------------------------------------')
                    print(f'|    The in degree of the vertex {desired_vertex} is {neighbours[0]}')
                    print(f'|    The out degree of the vertex {desired_vertex} is {neighbours[1]}')
                    print('-----------------------------------------------------------------------------------------')

                elif option == 8:
                    desired_vertex = int(input('Enter the desired vertex: '))
                    print('-----------------------------------------------------------------------------------------')
                    print(f'|    The inbound neighbours of the vertex {desired_vertex} are: {self._main_graph.getInboundNeighbours(desired_vertex)}')
                    print('-----------------------------------------------------------------------------------------')

                elif option == 9:
                    desired_vertex = int(input('Enter the desired vertex: '))
                    print('-----------------------------------------------------------------------------------------')
                    print(f'|    The outbound neighbours of the vertex {desired_vertex} are: {self._main_graph.getOutboundNeighbours(desired_vertex)}')
                    print('-----------------------------------------------------------------------------------------')

                elif option == 10:
                    edge = input('Enter the edge in this format - (sourceEdge targetEdge): ').strip('(').strip(')').split(' ')
                    if len(edge) != 2:
                        print('Invalid number of parameters')
                    else:
                        source_vertex = int(edge[0])
                        target_vertex = int(edge[1])
                        print('-----------------------------------------------------------------------------------------')
                        print(f'|    The cost of the edge ({source_vertex} {target_vertex}) is {self._main_graph.getCost(source_vertex, target_vertex)}')
                        print('-----------------------------------------------------------------------------------------')

                elif option == 11:
                    desired_vertex = int(input('Enter the desired vertex: '))
                    if self._main_graph.findIfVertexExists(desired_vertex):
                        print('-----------------------------------------------------------------------------------------')
                        print(f'|    Vertex {desired_vertex} exists')
                        print('-----------------------------------------------------------------------------------------')
                    else:
                        print('-----------------------------------------------------------------------------------------')
                        print(f'|    Vertex {desired_vertex} does not exist')
                        print('-----------------------------------------------------------------------------------------')

                elif option == 12:
                    edge = input('Enter the edge in this format - (sourceEdge targetEdge): ').strip('(').strip(')').split(' ')
                    if len(edge) != 2:
                        print('Invalid number of parameters')
                    else:
                        source_vertex = int(edge[0])
                        target_vertex = int(edge[1])
                        if self._main_graph.findIfEdgeExists(source_vertex, target_vertex):
                            print('-----------------------------------------------------------------------------------------')
                            print(f'|    Edge ({source_vertex} {target_vertex}) exists')
                            print('-----------------------------------------------------------------------------------------')
                        else:
                            print('-----------------------------------------------------------------------------------------')
                            print(f'|    Edge ({source_vertex} {target_vertex}) does not exist')
                            print('-----------------------------------------------------------------------------------------')

                elif option == 13:
                    desired_vertex = int(input('Enter the desired vertex: '))
                    if self._main_graph.addVertex(desired_vertex):
                        print('-----------------------------------------------------------------------------------------')
                        print(f'|    Vertex {desired_vertex} was added successfully')
                        print('-----------------------------------------------------------------------------------------')
                    else:
                        print('-----------------------------------------------------------------------------------------')
                        print(f'|    Vertex {desired_vertex} already exists')
                        print('-----------------------------------------------------------------------------------------')

                elif option == 14:
                    desired_vertex = int(input('Enter the desired vertex: '))
                    if self._main_graph.deleteVertex(desired_vertex):
                        print('-----------------------------------------------------------------------------------------')
                        print(f'|    Vertex {desired_vertex} was deleted successfully')
                        print('-----------------------------------------------------------------------------------------')
                    else:
                        print('-----------------------------------------------------------------------------------------')
                        print(f'|    Vertex {desired_vertex} does not exist')
                        print('-----------------------------------------------------------------------------------------')

                elif option == 15:
                    edge = input('Enter the edge in this format - (sourceEdge targetEdge cost): ').strip('(').strip(')').split(' ')
                    if len(edge) != 3:
                        print('Invalid number of parameters')
                    else:
                        source_vertex = int(edge[0])
                        target_vertex = int(edge[1])
                        cost = int(edge[2])
                        if self._main_graph.addEdge(source_vertex, target_vertex, cost):
                            print('-----------------------------------------------------------------------------------------')
                            print(f'|    Edge ({source_vertex} {target_vertex}) was added successfully')
                            print('-----------------------------------------------------------------------------------------')
                        else:
                            print('-----------------------------------------------------------------------------------------')
                            print(f'|    Edge ({source_vertex} {target_vertex}) already exists')
                            print('-----------------------------------------------------------------------------------------')

                elif option == 16:
                    edge = input('Enter the edge in this format - (sourceEdge targetEdge): ').strip('(').strip(')').split(' ')
                    if len(edge) != 2:
                        print('Invalid number of parameters')
                    else:
                        source_vertex = int(edge[0])
                        target_vertex = int(edge[1])
                        if self._main_graph.deleteEdge(source_vertex, target_vertex):
                            print('-----------------------------------------------------------------------------------------')
                            print(f'|    Edge ({source_vertex} {target_vertex}) was deleted successfully')
                            print('-----------------------------------------------------------------------------------------')
                        else:
                            print('-----------------------------------------------------------------------------------------')
                            print(f'|    Edge ({source_vertex} {target_vertex}) does not exist')
                            print('-----------------------------------------------------------------------------------------')

                elif option == 17:
                    edge = input('Enter the edge in this format - (sourceEdge targetEdge newCost): ').strip('(').strip(')').split(' ')
                    if len(edge) != 3:
                        print('Invalid number of parameters')
                    else:
                        source_vertex = int(edge[0])
                        target_vertex = int(edge[1])
                        new_cost = int(edge[2])
                        return_value = self._main_graph.updateEdgeInformation(source_vertex, target_vertex, new_cost)
                        print('-----------------------------------------------------------------------------------------')
                        print(f"|    Edge's ({source_vertex} {target_vertex}) old cost of {return_value[0]} was updated to {return_value[1]}")
                        print('-----------------------------------------------------------------------------------------')

                elif option == 18:
                    desired_graph = int(input('Print (1. main graph | 2. copy graph): '))
                    if desired_graph == 1:
                        print(self._main_graph.graphToString())
                    else:
                        print(self._copy_graph.graphToString())

                elif option == 19:
                    # desired_file = input("Enter the name of the file: ")
                    self._copy_graph = self._main_graph.copyGraph()
                    # self.saveGraph(desired_file, self._copy_graph)

                elif option == 20:
                    desired_file = input("Enter the name of the file: ")
                    self._copy_graph = self.createRandomGraph()
                    self.saveGraph(desired_file, self._copy_graph)

                elif option == 21:
                    edge = input('Enter the edge in this format - (sourceEdge targetEdge): ').strip('(').strip(
                        ')').split(' ')
                    if len(edge) != 2:
                        print('Invalid number of parameters')
                    else:
                        source_vertex = int(edge[0])
                        target_vertex = int(edge[1])
                        path = self._main_graph.findLowestLengthPath(source_vertex, target_vertex)
                        if not path[0]:
                            print('-----------------------------------------------------------------------------------------')
                            print(f"|    There is no path between ({source_vertex} {target_vertex})")
                            print('-----------------------------------------------------------------------------------------')
                        else:
                            print('-----------------------------------------------------------------------------------------')
                            print(f"|    The shortest path between ({source_vertex} {target_vertex}) is: {path[0]} of lenght {path[1]}")
                            print('-----------------------------------------------------------------------------------------')

                elif option == 0:
                    done = True
                    print('Exiting...')

                else:
                    print('No such command')

            except ValueError as ve:
                print('-----------------------------------------------------------------------------------------')
                print(f'|    {ve}')
                print('-----------------------------------------------------------------------------------------')








