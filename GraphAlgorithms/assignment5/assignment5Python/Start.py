import collections
import pprint
import random
from itertools import chain
from random import randint
from copy import deepcopy


class DirectedGraph:
    def __init__(self):
        self._dictVertices = {}
        self._dictEdges = {}

        self.parent = []
        self.rank = []
        # mst stores edges of the minimum spanning tree
        self.mst = []
        self.mstCost = 0
        self.tries = 0

    def readGraph1(self, file_name):
        f = open(file_name, 'rt')  # read text

        list1 = [int(number) for number in f.readline().split(' ')]

        # print(str(list1[0]) + " " + str(list1[1]))
        nrvertices = int(list1[0])
        for i in range(0, nrvertices):
            self.addVertex(i)

        lines = f.readlines()
        f.close()
        for line in lines:
            line = line.split(' ')
            v1 = int(line[0])
            v2 = int(line[1])
            if (v1 > v2):
                aux = v1
                v1 = v2
                v2 = aux
            cost = int(line[2])
            self.addEdge(v1, v2, cost)

        self.sortDictionaryByCost()

    def readGraph2(self, file_name):
        f = open(file_name, 'rt')  # read text
        lines = f.readlines()
        f.close()
        for line in lines:
            line = line.split(' ')
            if len(line) == 1:
                if self.checkIfVertexExists(int(line[0])) is False:
                    self.addVertex(int(line[0]))
            elif len(line) == 3:
                v1 = int(line[0])
                v2 = int(line[1])
                if (v1 > v2):
                    aux = v1
                    v1 = v2
                    v2 = aux
                cost = int(line[2])
                if self.checkIfVertexExists(v1) is False:
                    self.addVertex(v1)
                if self.checkIfVertexExists(v2) is False:
                    self.addVertex(v2)
                self.addEdge(v1, v2, cost)
        self.sortDictionaryByCost()

    def saveGraph1(self, file_name):
        f = open(file_name, 'wt')  # write text
        f.write(str(self.getNrVertices()) + " " + str(self.getNrEdges()) + "\n")
        listv = list(chain.from_iterable(self._dictEdges))
        i = 0
        for x in range(self.getNrEdges()):
            v1 = listv[i]
            v2 = listv[i + 1]
            i = i + 2
            f.write(str(v1) + " " + str(v2) + "\n")

        f.close()

    def saveGraph2(self, file_name):
        f = open(file_name, 'wt')  # write text
        listv = list(chain.from_iterable(self._dictEdges))
        i = 0
        for x in range(self.getNrEdges()):
            v1 = listv[i]
            v2 = listv[i + 1]
            i = i + 2
            f.write(str(v1) + " " + str(v2) + "\n")
        for z in self._dictVertices.keys():
            if self._dictVertices[z] == []:
                f.write(str(z) + "\n")
        f.close()

    def checkIfVertexExists(self, v):
        if v in self._dictVertices.keys():
            return True
        else:
            return False

    def checkIfEdgeExists(self, v1, v2):
        if (v1, v2) in self._dictEdges or (v2, v1) in self._dictEdges:
            return True
        else:
            return False

    def getCost(self, v1, v2):
        if self.checkIfEdgeExists(v1, v2) is False:
            print("The edge doesn't exist!")
        else:
            if (v1, v2) in self._dictEdges:
                return self._dictEdges[(v1, v2)]
            else:
                return self._dictEdges[(v2, v1)]

    def getVertices(self):
        list = []
        for i in self._dictVertices.keys():
            list.append(i)
        return list

    def addVertex(self, v):
        if self.checkIfVertexExists(v):
            print("The vertex already exists!")
        else:
            self._dictVertices[v] = []

    def addEdge(self, v1, v2, cost):
        if self.checkIfVertexExists(v1) is False or self.checkIfVertexExists(v2) is False:
            print("The vertices are invalid!")
        elif self.checkIfEdgeExists(v1, v2):
            print("The edge does already exist!")
        else:
            self._dictEdges[(v1, v2)] = cost
            self._dictVertices[v2].append(v1)
            self._dictVertices[v1].append(v2)
        self.sortDictionaryByCost()

    def deleteEdge(self, v1, v2):
        if self.checkIfEdgeExists(v1, v2) is False:
            print("The edge does not exist!")
        else:
            for i in self._dictVertices[v2]:
                if i == v1:
                    self._dictVertices[v2].remove(i)
            for i in self._dictVertices[v1]:
                if i == v2:
                    self._dictVertices[v1].remove(i)
            if (v1, v2) in self._dictEdges:
                self._dictEdges.pop((v1, v2))
            elif (v2, v1) in self._dictEdges:
                self._dictEdges.pop((v2, v1))
        self.sortDictionaryByCost()

    def deleteVertex(self, v):
        if self.checkIfVertexExists(v) is False:
            print("The vertex does not exist!")
        else:
            for i in self._dictVertices[v]:
                if (i, v) in self._dictEdges:
                    self._dictEdges.pop((i, v))
                elif (v, i) in self._dictEdges:
                    self._dictEdges.pop((v, i))
                self._dictVertices[i].remove(v)

            del self._dictVertices[v]
        self.sortDictionaryByCost()

    def getNrVertices(self):
        return len(self._dictVertices.keys())

    def getNrEdges(self):
        return len(self._dictEdges)

    def printGraph(self):
        print(self._dictVertices)
        edg = self.sortDictionaryByCost()
        for i in edg:
            print(str(i) + " : " + str(edg[i]))

    def newGraph(self, vert, edges):
        ng = DirectedGraph()
        ng._dictVertices = deepcopy(vert)
        ng._dictEdges = deepcopy(edges)
        return ng

    def copy_graph(self):
        graph = DirectedGraph()
        graph._dictEdges = self._dictEdges
        graph._dictVertices = self._dictVertices
        return graph

    # def parse_vertices(self):
    #     a = self.getVertices()
    #     line = ""
    #     for i in a:
    #         line = line + str(i) + " "
    #     print(line)

    def FindParent(self, node):
        if self.parent[node] == node:
            return node
        return self.FindParent(self.parent[node])

    def sortDictionaryByCost(self):
        edges1 = sorted(self._dictEdges.items(), key=lambda kv: (kv[1], kv[0]))
        edges2 = {}
        for i in edges1:
            edges2[i[0]] = i[1]
        self._dictEdges = deepcopy(edges2)
        return self._dictEdges

    def findSetOfVertexes(self, v, s):
        n = self.getNrVertices()
        for i in range(n):
            if v in s[i]:
                return i  # we return the position/index of the set the vertex can be found in

    def kruskalAlgorithm(self):
        mst = []  # where we will save the minimum spanning tree
        n = self.getNrVertices()
        s = [0] * n
        for i in range(n):
            s[i] = [i]  # we make a set for each vertex and we initialise it with the vertex itself
        self.sortDictionaryByCost()  # we sort the dictionary of edges by the costs increasingly

        for (v1, v2) in self._dictEdges:
            # we need to check if our vertices are in the same set( basically the same connected component)
            # if they are not, we reunite their sets and append the edge to the MST
            sv1 = self.findSetOfVertexes(v1, s)
            sv2 = self.findSetOfVertexes(v2, s)
            if sv1 != sv2:
                mst.append(((v1, v2), self.getCost(v1, v2)))
                for vertex in s[sv1]:
                    s[sv2].append(vertex)  # we make the 1 set as the reunion of the 2 and clear the other
                s[sv1].clear()

        # if len(mst) != n - 1:
        #     print("\nOnly a partial tree:\n")
        # else:
        #     print("\nEdges of minimum spanning tree in graph :\n")
        cost = 0
        if (self.tries == 0):
            for k in mst:
                #     print(str(k[0]) + "  :  " + str(k[1]))
                self.mstCost += k[1]
        # if len(mst) != n - 1:
        #     print("\nCost of the partial minimum spanning tree : " + str(cost))
        # else:
        #     print("\nCost of minimum spanning tree : " + str(cost))
        root = 0
        for r in mst:
            root = r[0]
            break
        root = root[0]
        e = []
        for i in mst:
            t = i[0]
            c = i[1]
            e.append((t[0], t[1], c))
        # print(e)
        # print(root)
        return e, root

    def hamiltonianCycle(self):
        # reading from the file I save the edges with the smaller vertex first to prevent any possible error
        if self.tries == 0:
            edges, root = self.kruskalAlgorithm()  # the edges are given as a triple and the root is the first vertex from the MST
        else:
            edges, root = self.kruskalAlgorithm()
            random.shuffle(edges)
            # print(edges)
        prev = [-1] * self.getNrVertices()

        for e in edges:
            prev[e[1]] = e[0]  # previous of every vertex in the MST is set

        root = randint(0, self.getNrVertices() - 1)
        walk = [root]  # we will start the walk from the root and also it will end here

        while len(walk) < self.getNrVertices():
            v = randint(0, self.getNrVertices() - 1)
            if v not in walk:
                walk.append(v)

        walk.append(root)  # we add the root to finish the walk
        tcost = 0

        for i in range(self.getNrVertices()):
            tcost = tcost + self.getCost(walk[i], walk[i + 1])  # we go through the vertices to find the cost of the walk

        if tcost <= self.mstCost * 2:
            print("\nCost: " + str(tcost))
            print("Hamiltonian cycle: " + str(walk))
        else:
            print("\nnot the wanted cost, greater than 2*MST cost")
            self.tries += 1
            print("Cost: " + str(tcost))
            print("Hamiltonian cycle: " + str(walk))
            if (self.tries < 20):
                print("\nnot the wanted cost, greater than 2*MST cost")
                self.hamiltonianCycle()


def menu():
    print('\n-----------------------------------------------------------------------------------------')
    print("|   1. Read from a file.")
    print("|   2. Check the existence of a vertex.")
    print("|   3. Check the existence of an edge.")
    print("|   4. Add a vertex.")
    print("|   5. Add an edge.")
    print("|   6. Delete a vertex.")
    print("|   7. Delete an edge.")
    print("|   8. Save the graph in a file.")
    print("|   9. Print everything")
    print("|   10. Get the number of vertices.")
    print("|   11. Get the number of edges.")
    print("|   12. Print all vertices.")
    print("|   13. MST using Kruskal's.")
    print("|   14. Hamiltonian Cycle of max 2*MST cost.")
    print("|   0. Exit")
    print('-----------------------------------------------------------------------------------------\n')

def start(cmd, dg):
    if cmd == 0:
        return True
    elif cmd == 1:
        file = input("Enter the name of the file: ")
        format = int(input("The format is(1 - numbers specified, 2 - numbers not specified) : "))
        if format == 1:
            dg.readGraph1(file)
        elif format == 2:
            dg.readGraph2(file)
        # dg.read_graph("r1.txt")
    elif cmd == 2:
        v = int(input("Enter a vertex: "))
        if dg.checkIfVertexExists(v) is True:
            print("The vertex exists!")
        else:
            print("The vertex doesn't exist!")
    elif cmd == 3:
        v = input("Enter 2 vertices: ")
        v1 = int(v.split(" ")[0])
        v2 = int(v.split(" ")[1])
        if dg.checkIfEdgeExists(v1, v2):
            print("The edge exists!")
        else:
            print("The edge doesn't exist!")
    elif cmd == 4:
        v = int(input("Enter a vertex: "))
        dg.addVertex(v)
    elif cmd == 5:
        v = input("Enter 2 vertices and a cost: ")
        v1 = int(v.split(" ")[0])
        v2 = int(v.split(" ")[1])
        cost = int(v.split(" ")[2])
        dg.addEdge(v1, v2, cost)
    elif cmd == 6:
        v = int(input("Enter a vertex: "))
        dg.deleteVertex(v)
    elif cmd == 7:
        v = input("Enter 2 vertices: ")
        v1 = int(v.split(" ")[0])
        v2 = int(v.split(" ")[1])
        dg.deleteEdge(v1, v2)
    elif cmd == 8:
        file = input("Enter the name of the file: ")
        format = int(input("The format is(1 - numbers specified, 2 - numbers not specified) : "))
        if format == 1:
            dg.saveGraph1(file)
        elif format == 2:
            dg.saveGraph2(file)
    elif cmd == 9:
        dg.printGraph()
    elif cmd == 10:
        print("The number of vertices: " + str(dg.getNrVertices()))
    elif cmd == 11:
        print("The number of edges: " + str(dg.getNrEdges()))
    elif cmd == 12:
        print(dg.getVertices())
    elif cmd == 13:
        dg.KruskalMST()
        # dg.kruskal()
    elif cmd == 14:
        dg.tries=0
        dg.mstCost=0
        dg.hamiltonianCycle()


if __name__ == '__main__':
    dg = DirectedGraph()
    done = False
    while not done:
        menu()
        cmd = int(input("\nEnter the number of the command: "))
        done = start(cmd, dg)
