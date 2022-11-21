#include "Node.h"

// Constructor, Destructor

Node::Node() {

}

Node::Node(const Node &n) {
    this->info = n.info;
    this->prev = n.prev;
    this->next = n.next;
}

Node::~Node() {

}

// Getters

TElem Node::getInfo() const {
    return this->info;
}

int Node::getPrev() const {
    return this->prev;
}

int Node::getNext() const {
    return this->next;
}

// Setters

void Node::setInfo(TElem new_info) {
    this->info = new_info;
}

void Node::setPrev(int new_prev) {
    this->prev = new_prev;
}

void Node::setNext(int new_next) {
    this->next = new_next;
}

Node& Node::operator=(const Node& given_node) {

    this->prev = given_node.prev;
    this->next = given_node.next;
    this->info = given_node.info;

    return *this;
}
