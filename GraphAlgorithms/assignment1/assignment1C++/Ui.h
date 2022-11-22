#pragma once
#include "Graph.h"

class UserInterface {
private:
    DirectedGraph main_graph;
    DirectedGraph copy_graph;

public:
    UserInterface();
    ~UserInterface();

    void readGraph1(const std::string& file_name, DirectedGraph &my_graph);
    void readGraph2(const std::string& file_name, DirectedGraph &my_graph);
    void saveGraph(const std::string &file_name, DirectedGraph &my_graph);
    DirectedGraph createRandomGraph();
    tuple handleEdgeString(const std::string& given_input);

    void printMenu();
    void startUi();
};

