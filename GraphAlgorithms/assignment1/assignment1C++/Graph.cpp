#include "Graph.h"

// Constructor, Destructor

DirectedGraph::DirectedGraph() {
    this->din = {};
    this->dout = {};
    this->dcost = {};
}

DirectedGraph::DirectedGraph(DirectedGraph &given_graph) {
    this->din = given_graph.din;
    this->dout = given_graph.dout;
    this->dcost = given_graph.dcost;
}

DirectedGraph::~DirectedGraph() {

}

// Getters

std::map<int, std::vector<int>> DirectedGraph::getDictIn() {
    return this->din;
}

std::map<int, std::vector<int>> DirectedGraph::getDictOut() {
    return this->dout;
}

std::map<key, int> DirectedGraph::getDictCost() {
    return this->dcost;
}

int DirectedGraph::getNrOfVertices() {
    return this->din.size();
}

int DirectedGraph::getNrOfEdges() {
    return this->dcost.size();
}

std::vector<int> DirectedGraph::getAllVertices() {
    std::vector<int> result;
    auto it = this->din.begin();

    while (it != this->din.end()) {
        int vertex = it->first;
        result.push_back(vertex);
        it ++;
    }
    return result;
}

std::vector<key> DirectedGraph::getAllEdges() {
    std::vector<key> result;
    auto it = this->dcost.begin();

    while (it != this->dcost.end()) {
        key edge = it->first;
        result.push_back(edge);
        it ++;
    }
    return result;
}

tuple DirectedGraph::getInDegreeAndOutDegree(int vertex) {
    if (!this->findIfVertexExists(vertex)) {
        std::string exception_string = "Vertex " + std::to_string(vertex) + " does not exist";
        throw exception_string;
    }
    int in_degree = this->din[vertex].size();
    int out_degree = this->dout[vertex].size();
    tuple result(in_degree, out_degree);
    return result;
}

std::vector<int> DirectedGraph::getInboundNeighbours(int vertex) {
    if (!this->findIfVertexExists(vertex)) {
        std::string exception_string = "Vertex " + std::to_string(vertex) + " does not exist";
        throw exception_string;
    }
    return this->din[vertex];
}

std::vector<int> DirectedGraph::getOutboundNeighbours(int vertex) {
    if (!this->findIfVertexExists(vertex)) {
        std::string exception_string = "Vertex " + std::to_string(vertex) + " does not exist";
        throw exception_string;
    }
    return this->dout[vertex];
}

int DirectedGraph::getCost(int source_vertex, int target_vertex) {
    if (!this->findIfEdgeExists(source_vertex, target_vertex)) {
        std::string exception_string = "Edge (" + std::to_string(source_vertex) + " " + std::to_string(target_vertex) + ") does not exist";
        throw exception_string;
    }
    key edge(source_vertex, target_vertex);
    return this->dcost[edge];
}

// Validators

bool DirectedGraph::findIfVertexExists(int vertex) {
    std::vector<int> list_of_vertices = this->getAllVertices();
    std::vector<int>::iterator it;

    it = find(list_of_vertices.begin(), list_of_vertices.end(), vertex);
    if (it != list_of_vertices.end()) {
        return true;
    }
    return false;
}

bool DirectedGraph::findIfEdgeExists(int source_vertex, int target_vertex) {
    if (!this->findIfVertexExists(source_vertex) || !this->findIfVertexExists(target_vertex)) {
        return false;
    }
    std::vector<int> outbound_vertices = this->getOutboundNeighbours(source_vertex);
    std::vector<int>::iterator it;
    it = find(outbound_vertices.begin(), outbound_vertices.end(), target_vertex);
    if (it != outbound_vertices.end()){
        return true;
    }
    return false;
}

// Add, Delete, Update

bool DirectedGraph::addVertex(int new_vertex) {
    if (this->findIfVertexExists(new_vertex)) {
        return false;
    }
    this->din[new_vertex] = {};
    this->dout[new_vertex] = {};
    return true;
}

bool DirectedGraph::deleteVertex(int given_vertex) {
    if (!this->findIfVertexExists(given_vertex)) {
        return false;
    }

    std::vector<int> outbound_vertices = this->getOutboundNeighbours(given_vertex);
    for (auto &it1 : outbound_vertices){
        this->din[it1].erase(remove(this->din[it1].begin(), this->din[it1].end(), given_vertex), this->din[it1].end());
        key edge(given_vertex, it1);
        this->dcost.erase(edge);
    }
    this->dout.erase(given_vertex);

    std::vector<int> inbound_vertices = this->getInboundNeighbours(given_vertex);
    for (auto it2 : inbound_vertices) {
        this->dout[it2].erase(remove(this->dout[it2].begin(), this->dout[it2].end(), given_vertex), this->dout[it2].end());
        key edge(it2, given_vertex);
        this->dcost.erase(edge);
    }
    this->din.erase(given_vertex);
    return true;
}

bool DirectedGraph::addEdge(int source_vertex, int target_vertex, int info) {
    if (!this->findIfVertexExists(source_vertex) || !this->findIfVertexExists(target_vertex)) {
        return false;
    }
    if (this->findIfEdgeExists(source_vertex, target_vertex)) {
        return false;
    }

    this->dout[source_vertex].push_back(target_vertex);
    this->din[target_vertex].push_back(source_vertex);

    key edge(source_vertex, target_vertex);
    this->dcost[edge] = info;
    return true;
}

bool DirectedGraph::deleteEdge(int source_vertex, int target_vertex) {
    if (!this->findIfVertexExists(source_vertex) || !this->findIfVertexExists(target_vertex)) {
        return false;
    }
    if (!this->findIfEdgeExists(source_vertex, target_vertex)) {
        return false;
    }

    this->dout[source_vertex].erase(remove(this->dout[source_vertex].begin(), this->dout[source_vertex].end(), target_vertex), this->dout[source_vertex].end());
    this->din[target_vertex].erase(remove(this->din[target_vertex].begin(), this->din[target_vertex].end(), source_vertex), this->din[target_vertex].end());
    key edge(source_vertex, target_vertex);
    this->dcost.erase(edge);
    return true;
}

tuple DirectedGraph::updateEdgeInformation(int source_vertex, int target_vertex, int new_info) {
    if (!this->findIfEdgeExists(source_vertex, target_vertex)) {
        std::string exception_string = "Edge (" + std::to_string(source_vertex) + " " + std::to_string(target_vertex) + ") does not exist";
        throw exception_string;
    }
    key edge(source_vertex, target_vertex);
    int old_info = this->dcost[edge];
    this->dcost[edge] = new_info;

    tuple result(old_info, new_info);
    return result;
}

// Copy graph

DirectedGraph DirectedGraph::copyGraph() {
    DirectedGraph copy_graph;
    copy_graph.din = this->din;
    copy_graph.dout = this->dout;
    copy_graph.dcost = this->dcost;
    return copy_graph;
}

// String Representation

std::string DirectedGraph::toString() {
    std::string destination_string;
    destination_string += "-----------------------------------------------------------------------------------------\n";
    for (auto it1 = this->dout.begin(); it1 != this->dout.end(); it1++) {
        if (this->dout[it1->first].empty() && this->din[it1->first].empty()) {
            destination_string += "|    " + std::to_string(it1->first) + " is an isolated vertex\n";
        }
        else {
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
                destination_string += "|    (" + std::to_string(it1->first) + " " + std::to_string(*it2) + ") with the cost of " + std::to_string(this->getCost(it1->first, *it2)) + "\n";
            }
        }
    }
    destination_string += "-----------------------------------------------------------------------------------------\n";
    return destination_string;
}




