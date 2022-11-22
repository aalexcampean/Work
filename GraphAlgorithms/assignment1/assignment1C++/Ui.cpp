#include "Ui.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>


UserInterface::UserInterface() {
    this->main_graph = {};
    this->copy_graph = {};
}

UserInterface::~UserInterface() {

}

void UserInterface::readGraph1(const std::string& file_name, DirectedGraph &my_graph) {
    std::ifstream input(file_name, 0);
    std::string input1, input2;

    input >> input1 >> input2;
    int nr_vertices = stoi(input1);
    int nr_edges = stoi(input2);

    for (int i = 0; i < nr_vertices; i++) {
        my_graph.addVertex(i);
    }

    int source_vertex, target_vertex, cost;
    for (int i = 0; i < nr_edges; i++) {
        input >> source_vertex >> target_vertex >> cost;
        my_graph.addEdge(source_vertex, target_vertex, cost);
    }
}

void UserInterface::readGraph2(const std::string& file_name, DirectedGraph &my_graph) {
    std::ifstream input(file_name, 0);
    while (input) {
        std::string input1, input2, input3;
        input >> input1 >> input2 >> input3;
        int source_vertex = stoi(input1);

        if (input2.empty()) {
            int target_vertex = stoi(input2);
            int cost = stoi(input3);

            my_graph.addVertex(source_vertex);
            my_graph.addVertex(target_vertex);
            my_graph.addEdge(source_vertex, target_vertex, cost);
        }
        else {
            my_graph.addVertex(source_vertex);
        }
    }
}

void UserInterface::saveGraph(const std::string &file_name, DirectedGraph &my_graph) {
    std::ofstream output(file_name);

    for (auto& it1 : my_graph.getDictOut()) {
        if (my_graph.getDictOut()[it1.first].empty() && my_graph.getDictIn()[it1.first].empty()) {
            output << std::to_string(it1.first) << std::endl;
        } else {
            for (auto &it2 : it1.second) {
                output << std::to_string(it1.first) << " " << std::to_string(it2) << " " << my_graph.getCost(it1.first, it2) << std::endl;
            }
        }
    }
    output.close();
}

DirectedGraph UserInterface::createRandomGraph() {
    DirectedGraph new_graph;
    int nr_of_vertices;
    int nr_of_edges;
    std::cout << "Enter the number of vertices: ";
    std::cin >> nr_of_vertices;
    std::cout << "Enter the number of edge: ";
    std::cin >> nr_of_edges;

    if (nr_of_edges > nr_of_vertices * nr_of_vertices) {
        throw std::string("Impossible to create such a graph (the number of edges should be smaller or equal than the number of vertices^2");
    }
    else {
        for (int i = 0; i < nr_of_vertices; i++) {
            new_graph.addVertex(i);
        }

        int i = 0;
        while (i <= nr_of_edges) {
            int source_vertex = 0 + (rand() % (nr_of_vertices - 1));
            int target_vertex = 0 + (rand() % (nr_of_vertices - 1));
            int cost = -nr_of_vertices + (rand() % (nr_of_vertices - 1));

            if (new_graph.addEdge(source_vertex, target_vertex, cost)) {
                i += 1;
            }
        }
    }
    return new_graph;
}

tuple UserInterface::handleEdgeString(const std::string& input_text){
    std::istringstream iss(input_text);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    if (results.size() != 2) {
        throw std::string("Invalid number of parameters");
    }
    int source_vertex = stoi(results[0]);
    int target_vertex = stoi(results[1]);
    tuple result(source_vertex, target_vertex);

    return result;
}

void UserInterface::printMenu() {
    std::cout << "\n-----------------------------------------------------------------------------------------" << std::left << std::setw(58) << std::endl;
    std::cout << "|    1. Read from a file" << "11. Find if a vertex exists"  << "   |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    2. Save graph in a file" << "12. Find if an edge exists" << "    |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    3. Get number of vertices" << "13. Add a vertex" << "              |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    4. Get number of edges" << "14. Delete a vertex" << "           |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    5. Get all vertices" << "15. Add an edge" << "               |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    6. Get all edges" << "16. Delete an edge" << "            |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    7. Get in and out degree of a vertex" << "17. Update edge info" << "          |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    8. Get the inbound neighbours of a vertex" << "18. Print graph" << "               |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    9. Get the outbound neighbours of a vertex" << "19. Copy graph" << "                |" << std::left << std::setw(58) << std::endl;
    std::cout << "|    10. Get the cost of an edge" << "20. Create random graph" << "       |" << std::left << std::setw(58) << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------" << std::left << std::setw(58) << std::endl;
    std::cout << "|                                       0. Exit" << "                              |" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
}

void UserInterface::startUi() {
    this->printMenu();
    bool done = false;
    int option;

    while (!done) {
        try {
            std::cout << "Enter the number of the command: " << std::endl;
            std::cin >> option;

            if (option == 1) {
                std::string desired_file;
                int read_format;

                std::cout << "Enter the name of the file: " << std::endl;
                std::cin >> desired_file;

                std::cout << "The reading format is (1. including number of vertices | 2. excluding the number of vertices): " << std::endl;;
                std::cin >> read_format;

                if (read_format == 1) {
                    this->readGraph1(desired_file, this->main_graph);
                }
                else if (read_format == 2) {
                    this->readGraph2(desired_file, this->main_graph);
                }
                else {
                    std::cout << "No such format";
                }
            }

            else if (option == 2) {
                std::string desired_file;
                std::cout << "Enter the name of the file: ";
                std::cin >> desired_file;
                this->saveGraph(desired_file, this->main_graph);
            }

            else if (option == 3) {
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    Number of vertices: " << std::to_string(this->main_graph.getNrOfVertices()) << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 4) {
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    Number of edges: " << std::to_string(this->main_graph.getNrOfEdges()) << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 5) {
                std::string destination_string;
                for (auto &it : this->main_graph.getAllVertices()) {
                    destination_string += std::to_string(it) + ", ";
                }
                destination_string.pop_back();
                destination_string.pop_back();
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    Number vertices: " << destination_string << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 6) {
                std::string destination_string;
                for (auto &it : this->main_graph.getAllEdges()) {
                    destination_string += "(" + std::to_string(it.first) + " " + std::to_string(it.second) + ")" + ", ";
                }
                destination_string.pop_back();
                destination_string.pop_back();
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    The edges: " << destination_string << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 7) {
                int desired_vertex;
                std::cout << "Enter the desired vertex: ";
                std::cin >> desired_vertex;
                tuple neighbours = this->main_graph.getInDegreeAndOutDegree(desired_vertex);
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    The in degree of the vertex " << std::to_string(desired_vertex) << " is " << std::to_string(neighbours.first) << std::endl;
                std::cout << "|    The out degree of the vertex " << std::to_string(desired_vertex) << " is " << std::to_string(neighbours.second) << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 8) {
                int desired_vertex;
                std::cout << "Enter the desired vertex: ";
                std::cin >> desired_vertex;
                std::string destination_string;
                for (auto &it : this->main_graph.getInboundNeighbours(desired_vertex)) {
                    destination_string += std::to_string(it) + ", ";
                }
                destination_string.pop_back();
                destination_string.pop_back();
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    The inbound neighbours of the vertex " << std::to_string(desired_vertex) << " are " << destination_string << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 9) {
                int desired_vertex;
                std::cout << "Enter the desired vertex: ";
                std::cin >> desired_vertex;
                std::string destination_string;
                for (auto &it : this->main_graph.getOutboundNeighbours(desired_vertex)) {
                    destination_string += std::to_string(it) + ", ";
                }
                destination_string.pop_back();
                destination_string.pop_back();
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    The outbound neighbours of the vertex " << std::to_string(desired_vertex) << " are " << destination_string << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 10) {
                std::string input_text;
                std::cout << "Enter the edge in this format - sourceEdge targetEdge: ";
                std::getline(std::cin.ignore(), input_text);

                tuple vertices = this->handleEdgeString(input_text);
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    The cost of the edge (" << std::to_string(vertices.first) << " " << std::to_string(vertices.second) << ") is "
                          << std::to_string(this->main_graph.getCost(vertices.first, vertices.second)) << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 11) {
                int desired_vertex;
                std::cout << "Enter the desired vertex: ";
                std::cin >> desired_vertex;
                if (this->main_graph.findIfVertexExists(desired_vertex)) {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Vertex " << std::to_string(desired_vertex) << " exists" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
                else {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Vertex " << std::to_string(desired_vertex) << " does not exist" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
            }

            else if (option == 12) {
                std::string input_text;
                std::cout << "Enter the edge in this format - sourceEdge targetEdge: ";
                std::getline(std::cin.ignore(), input_text);

                tuple vertices = this->handleEdgeString(input_text);
                if (this->main_graph.findIfEdgeExists(vertices.first, vertices.second)) {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Edge (" << std::to_string(vertices.first) << " " << std::to_string(vertices.second) << ") exists" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
                else {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Edge (" << std::to_string(vertices.first) << " " << std::to_string(vertices.second) << ") does not exist" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
            }

            else if (option == 13) {
                int desired_vertex;
                std::cout << "Enter the desired vertex: ";
                std::cin >> desired_vertex;
                if (this->main_graph.addVertex(desired_vertex)) {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Vertex " << std::to_string(desired_vertex) << " was added successfully" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
                else {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Vertex " << std::to_string(desired_vertex) << " already exists" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
            }

            else if (option == 14) {
                int desired_vertex;
                std::cout << "Enter the desired vertex: ";
                std::cin >> desired_vertex;
                if (this->main_graph.deleteVertex(desired_vertex)) {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Vertex " << std::to_string(desired_vertex) << " was deleted successfully" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
                else {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Vertex " << std::to_string(desired_vertex) << " does not exist" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
            }

            else if (option == 15) {
                std::string input_text;
                std::cout << "Enter the edge in this format - sourceEdge targetEdge cost: ";
                std::getline(std::cin.ignore(), input_text);

                std::istringstream iss(input_text);
                std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                 std::istream_iterator<std::string>());
                if (results.size() != 3) {
                    throw std::string("Invalid number of parameters");
                }
                int source_vertex = stoi(results[0]);
                int target_vertex = stoi(results[1]);
                int cost = stoi(results[2]);
                if (this->main_graph.addEdge(source_vertex, target_vertex, cost)) {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Edge (" << results[0] << " " << results[1] << ") was added successfully" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
                else {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Edge (" << results[0] << " " << results[1] << ") already exists" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
            }

            else if (option == 16) {
                std::string input_text;
                std::cout << "Enter the edge in this format - sourceEdge targetEdge: ";
                std::getline(std::cin.ignore(), input_text);

                tuple vertices = this->handleEdgeString(input_text);
                if (this->main_graph.deleteEdge(vertices.first, vertices.second)) {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Edge (" << std::to_string(vertices.first) << " " << std::to_string(vertices.second) << ") was deleted successfully" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
                else {
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                    std::cout << "|    Edge (" << std::to_string(vertices.first) << " " << std::to_string(vertices.second) << ") does not exist" << std::endl;
                    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                }
            }

            else if (option == 17) {
                std::string input_text;
                std::cout << "Enter the edge in this format - sourceEdge targetEdge newCost: ";
                std::getline(std::cin.ignore(), input_text);

                std::istringstream iss(input_text);
                std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                 std::istream_iterator<std::string>());
                if (results.size() != 3) {
                    throw std::string("Invalid number of parameters");
                }
                int source_vertex = stoi(results[0]);
                int target_vertex = stoi(results[1]);
                int new_cost = stoi(results[2]);

                tuple values = this->main_graph.updateEdgeInformation(source_vertex, target_vertex, new_cost);
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
                std::cout << "|    Edge's (" << results[0] << " " << results[1] << ") old cost of "
                          << std::to_string(values.first) << " was updated to " << std::to_string(values.second) << std::endl;
                std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            }

            else if (option == 18) {
                int desired_graph;
                std::cout << "Print (1. main graph | 2. copy graph): " << std::endl;
                std::cin >> desired_graph;
                if (desired_graph == 1) {
                    std::cout << this->main_graph.toString() << std::endl;
                }
                else if (desired_graph == 2) {
                    std::cout << this->copy_graph.toString() << std::endl;
                }
                else {
                    std::cout << "No such command";
                }
            }

            else if (option == 19) {
                this->copy_graph = this->main_graph.copyGraph();
            }

            else if (option == 20) {
                std::string desired_file;
                std::cout << "Enter the name of the file: ";
                std::cin >> desired_file;
                this->copy_graph = this->createRandomGraph();
                this->saveGraph(desired_file, this->copy_graph);
            }
            else if (option == 0) {
                done = true;
                std::cout << "Exiting..." << std::endl;
            }
            else {
                std::cout << "No such command";
            }
        }
        catch (std::string exception_string) {
            std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
            std::cout << "|    " << exception_string << std::endl;
            std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
        }
    }
}
