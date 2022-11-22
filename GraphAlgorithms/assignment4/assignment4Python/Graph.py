import copy
import math
from queue import Queue


class EdgeId:

    def __init__(self, source, target):
        self._source = source
        self._target = target


class DirectedGraph:

    def __init__(self):
        self._din = {}
        self._dout = {}
        self._dcost = {}

    @property
    def getDictIn(self):
        return self._din

    @property
    def getDictOut(self):
        return self._dout

    @property
    def getDictCost(self):
        return self._dcost

    @property
    def getNrOfVertices(self):
        return len(self._din)

    @property
    def getNrOfEdges(self):
        return len(self._dcost)

    @property
    def getAllVertices(self):
        result = []
        for i in self._dout.keys():
            result.append(i)
        return result

    @property
    def getAllEdges(self):
        result = []
        for i in self._dcost.keys():
            result.append(i)
        return result

    def getInDegreeAndOutDegree(self, vertex):
        if self.findIfVertexExists(vertex) is False:
            raise ValueError(f'Vertex {vertex} does not exist')
        in_degree = len(self._din[vertex])
        out_degree = len(self._dout[vertex])

        return in_degree, out_degree

    def getInboundNeighbours(self, vertex):
        if self.findIfVertexExists(vertex) is False:
            raise ValueError(f'Vertex {vertex} does not exist')

        return self._din.get(vertex)

    def getOutboundNeighbours(self, vertex):
        if self.findIfVertexExists(vertex) is False:
            raise ValueError(f'Vertex {vertex} does not exist')

        return self._dout.get(vertex)

    def getCost(self, source_vertex, target_vertex):
        if not self.findIfEdgeExists(source_vertex, target_vertex):
            raise ValueError(f'Edge ({source_vertex} {target_vertex}) does not exist')

        return self._dcost[(source_vertex, target_vertex)]

    def findIfVertexExists(self, vertex):
        if vertex in self._din.keys():
            return True
        return False

    def findIfEdgeExists(self, source_vertex, target_vertex):
        if not self.findIfVertexExists(source_vertex) or not self.findIfVertexExists(target_vertex):
            return False
        if target_vertex in self._dout[source_vertex]:
            return True
        return False

    def addVertex(self, new_vertex):
        if self.findIfVertexExists(new_vertex):
            return False

        self._din[new_vertex] = []
        self._dout[new_vertex] = []

        return True

    def deleteVertex(self, given_vertex):
        if not self.findIfVertexExists(given_vertex):
            return False

        for vertex in self._dout.get(given_vertex):
            self._din[vertex].remove(given_vertex)
            # removing the key in the out dict corresponding to the given vertex
            del self._dcost[given_vertex, vertex]

        del self._dout[given_vertex]

        for vertex in self._din.get(given_vertex):
            self._dout[vertex].remove(given_vertex)
            # removing the key in the in dict corresponding to the given vertex
            del self._dcost[vertex, given_vertex]

        del self._din[given_vertex]

        return True

    def addEdge(self, source_vertex, target_vertex, info):
        if not self.findIfVertexExists(source_vertex) or not self.findIfVertexExists(target_vertex):
            return False
        if self.findIfEdgeExists(source_vertex, target_vertex):
            return False

        # add each vertex to its corresponding dictionary
        self._dout[source_vertex].append(target_vertex)
        self._din[target_vertex].append(source_vertex)

        # add the new edge to the cost dictionary and assign it the given value
        self._dcost[(source_vertex, target_vertex)] = info

        return True

    def deleteEdge(self, source_vertex, target_vertex):
        if not self.findIfVertexExists(source_vertex) or not self.findIfVertexExists(target_vertex):
            return False
        if not self.findIfEdgeExists(source_vertex, target_vertex):
            return False

        # delete the target vertex from the source vertex key
        self._dout[source_vertex].remove(target_vertex)

        # delete the source vertex from the target vertex key
        self._din[target_vertex].remove(source_vertex)

        # delete the edge from the cost dictionary
        del self._dcost[source_vertex, target_vertex]

        return True

    def updateEdgeInformation(self, source_vertex, target_vertex, new_info):
        if self.findIfEdgeExists(source_vertex, target_vertex) is False:
            raise ValueError(f'Edge ({source_vertex} {target_vertex}) already exists')

        old_info = self._dcost[(source_vertex, target_vertex)]
        self._dcost[(source_vertex, target_vertex)] = new_info
        return old_info, new_info

        # print(f'The cost of the edge ({source_vertex},{target_vertex}) was changed from {old_info} to {new_info}')

    def findLowestLengthPath(self, source_vertex, target_vertex):
        if not self.findIfVertexExists(source_vertex):
            raise ValueError(f'Vertex {source_vertex} does not exist')
        if not self.findIfVertexExists(target_vertex):
            raise ValueError(f'Vertex {target_vertex} does not exist')

        list_of_previous_nodes = self.backwardBreadthFirstSearch(target_vertex, source_vertex)
        return self.reconstructPath(source_vertex, target_vertex, list_of_previous_nodes)

    def backwardBreadthFirstSearch(self, start_vertex, end_vertex):
        queue_of_nodes = Queue(maxsize=self.getNrOfVertices)
        queue_of_nodes.put(start_vertex)

        visited = {}
        for i in self.getDictIn:
            visited[i] = False
        visited[start_vertex] = True

        previous_nodes = {}
        for i in self.getDictIn:
            previous_nodes[i] = None

        while not queue_of_nodes.empty():
            node = queue_of_nodes.get()
            node_neighbours = self.getInboundNeighbours(node)

            for in_node in node_neighbours:
                if not visited[in_node]:
                    queue_of_nodes.put(in_node)
                    visited[in_node] = True
                    previous_nodes[in_node] = node
                    if in_node == end_vertex:
                        return previous_nodes

        return previous_nodes

    def reconstructPath(self, start_vertex, end_vertex, list_of_previous_nodes):
        final_path = []
        length = 0
        node = start_vertex
        while node is not None:
            final_path.append(node)
            length += 1
            node = list_of_previous_nodes[node]

        if final_path[-1] == end_vertex:
            return final_path, length - 1
        return [], length - 1

    def findMinimumCostWalk(self, source_vertex, target_vertex):
        if not self.findIfVertexExists(source_vertex):
            raise ValueError(f'Vertex {source_vertex} does not exist')
        if not self.findIfVertexExists(target_vertex):
            raise ValueError(f'Vertex {target_vertex} does not exist')

        return_value = self.minimumCostWalkUsingDynamicProgramming(source_vertex, target_vertex)
        return self.reconstructWalk(target_vertex, return_value[0], return_value[1])

    def minimumCostWalkUsingDynamicProgramming(self, source_vertex, target_vertex, ):
        # initializing the cost matrix
        cost_matrix = [[-1 for x in range(self.getNrOfVertices)] for y in range(self.getNrOfVertices)]

        before = {}
        for x in range(self.getNrOfVertices):
            before[x] = -1

        for x in self.getAllVertices:
            if x == source_vertex:
                cost_matrix[0][x] = 0
            else:
                cost_matrix[0][x] = math.inf

        # going through the matrix and setting the cost for any walk worth taking into consideration
        for k in range(1, self.getNrOfVertices):
            for x in self.getAllVertices:
                minimum_path = math.inf
                minimum_node = -1

                for in_neighbour in self.getInboundNeighbours(x):
                    current_minimum = min(minimum_path, cost_matrix[k-1][in_neighbour] + self.getCost(in_neighbour, x))
                    if minimum_path > current_minimum:
                        minimum_node = in_neighbour
                    minimum_path = current_minimum

                if cost_matrix[k-1][x] > minimum_path:
                    before[x] = minimum_node
                cost_matrix[k][x] = min(cost_matrix[k-1][x], minimum_path)

        if cost_matrix[self.getNrOfVertices - 1][target_vertex] == math.inf:
            raise ValueError(f'There is no walk between vertex {source_vertex} and vertex {target_vertex}')

        return cost_matrix, before

    def reconstructWalk(self, end_vertex, cost_matrix, before_vertices):
        walk = []
        current_vertex = end_vertex
        walk.append(current_vertex)

        while before_vertices[current_vertex] != -1:
            walk.append(before_vertices[current_vertex])
            current_vertex = before_vertices[current_vertex]

            if len(walk) > self.getNrOfVertices * self.getNrOfVertices:
                raise ValueError('Negative cycle!')

        walk.reverse()
        return cost_matrix[len(walk) - 1][end_vertex], walk

    def findHighestCostPath(self, source_vertex, target_vertex):
        if not self.findIfVertexExists(source_vertex):
            raise ValueError(f'Vertex {source_vertex} does not exist')
        if not self.findIfVertexExists(target_vertex):
            raise ValueError(f'Vertex {target_vertex} does not exist')

        sorted_v = self.topologicalSort()

        if sorted_v is None:
            raise ValueError('The graph is not a DAG')

        costs_list = [-math.inf for i in range(self.getNrOfVertices)]
        costs_list[source_vertex] = 0

        previous_list = [None for i in range(self.getNrOfVertices)]

        for vertex in sorted_v:
            # if the vertex is the end one we break, meaning we found our walk
            if vertex == target_vertex:
                break

            for out_vertex in self.getOutboundNeighbours(vertex):
                if costs_list[out_vertex] < costs_list[vertex] + self.getCost(vertex, out_vertex):
                    costs_list[out_vertex] = costs_list[vertex] + self.getCost(vertex, out_vertex)
                    previous_list[out_vertex] = vertex

        if costs_list[target_vertex] == -math.inf:
            raise ValueError(f'There is no walk between vertex {source_vertex} and vertex {target_vertex}')

        # reconstructing the final path
        path = []

        vertex = target_vertex
        while costs_list[vertex] != -math.inf:
            path.append(vertex)
            vertex = previous_list[vertex]
            if vertex == source_vertex:
                break
        path.append(source_vertex)

        path.reverse()

        return costs_list[target_vertex], path

    def topologicalSort(self):
        sorted_v = []
        fully_processed_v = set()
        in_process_v = set()

        for vertex in self.getAllVertices:
            if vertex not in fully_processed_v:
                ok = self.tSDepthFirstSearch(vertex, sorted_v, fully_processed_v, in_process_v)
                if not ok:
                    sorted_v = None
                    break

        return sorted_v

    def tSDepthFirstSearch(self, vertex, sorted_v, fully_processed_v, in_process_v):
        in_process_v.add(vertex)
        for in_vertex in self._din[vertex]:
            if in_vertex in in_process_v:
                return False
            elif in_vertex not in fully_processed_v:
                ok = self.tSDepthFirstSearch(in_vertex, sorted_v, fully_processed_v, in_process_v)
                if not ok:
                    return False

        in_process_v.remove(vertex)
        sorted_v.append(vertex)
        fully_processed_v.add(vertex)

        return True

    def copyGraph(self):
        return copy.deepcopy(self)

    def graphToString(self):
        graph_string = ''
        graph_string += '-----------------------------------------------------------------------------------------\n'
        for i in self._dout:
            if self._dout[i] == [] and self._din[i] == []:
                graph_string += f'|    {i} is an isolated vertex\n'
            else:
                for j in self._dout[i]:
                    graph_string += f'|    ({i} {j}) with the cost: {self.getCost(i, j)}\n'

        graph_string += '-----------------------------------------------------------------------------------------'
        return graph_string
