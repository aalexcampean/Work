#include "Node.h"

// Constructors, Destructor

Node::Node() {
    this->prev = nullptr;
    this->next = nullptr;
}
// Total complexity: Theta(1) - constant number of operations


Node::Node(const Node& n) {
    this->info = n.info;
    this->prev = n.prev;
    this->next = n.next;
}
// Total complexity: Theta(1) - constant number of operations


Node::~Node() {
}
// Total complexity: Theta(1) - constant number of operations


// Getters

int Node::Value() const {
    return get<0>(this->info);
}
// Total complexity: Theta(1) - constant number of operations


int Node::Row() const {
    return get<1>(this->info);
}
// Total complexity: Theta(1) - constant number of operations


int Node::Col() const {
    return get<2>(this->info);
}
// Total complexity: Theta(1) - constant number of operations


Node *Node::Prev() const {
    return this->prev;
}
// Total complexity: Theta(1) - constant number of operations


Node *Node::Next() const {
    return this->next;
}
// Total complexity: Theta(1) - constant number of operations


// Setters

void Node::setValue(int new_value) {
    get<0>(this->info) = new_value;
}
// Total complexity: Theta(1) - constant number of operations


void Node::setRow(int new_row) {
    get<1>(this->info) = new_row;
}
// Total complexity: Theta(1) - constant number of operations


void Node::setColumn(int new_column) {
    get<2>(this->info) = new_column;
}
// Total complexity: Theta(1) - constant number of operations


void Node::setNext(Node *new_next) {
    this->next = new_next;
}
// Total complexity: Theta(1) - constant number of operations


void Node::setPrev(Node *new_prev) {
    this->prev = new_prev;
}
// Total complexity: Theta(1) - constant number of operations




