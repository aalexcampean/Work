#pragma once
#include <map>
#include <vector>
#include <string>

typedef std::pair<int, int> key;
typedef std::pair<int, int> tuple;

class DirectedGraph {
private:
    std::map<int, std::vector<int>> din;
    std::map<int, std::vector<int>> dout;
    std::map<key, int> dcost;

public:
    DirectedGraph();
    DirectedGraph(DirectedGraph& given_graph);
    ~DirectedGraph();

    // Getters

    std::map<int, std::vector<int>> getDictIn();
    std::map<int, std::vector<int>> getDictOut();
    std::map<key, int> getDictCost();
    int getNrOfVertices();
    int getNrOfEdges();
    std::vector<int> getAllVertices();
    std::vector<key> getAllEdges();
    tuple getInDegreeAndOutDegree(int vertex);
    std::vector<int> getInboundNeighbours(int vertex);
    std::vector<int> getOutboundNeighbours(int vertex);
    int getCost(int source_vertex, int target_vertex);

    // Validators

    bool findIfVertexExists(int vertex);
    bool findIfEdgeExists(int source_vertex, int target_vertex);

    // Add, Delete, Update

    bool addVertex(int new_vertex);
    bool deleteVertex(int given_vertex);
    bool addEdge(int source_vertex, int target_vertex, int info);
    bool deleteEdge(int source_vertex, int target_vertex);
    tuple updateEdgeInformation(int source_vertex, int target_vertex, int new_info);

    // Copy graph

    DirectedGraph copyGraph();

    // String Representation

    std::string toString();
};


