#include "Node.h"

// Constructor, Destructor

Node::Node() {
    this->info = NULLTElem;
    this->leftCounter = 0;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const Node &n) {
    this->info = n.info;
    this->leftCounter = n.leftCounter;
    this->left = n.left;
    this->right = n.right;
}

Node::~Node() {

}

// Getters

TElem Node::getInfo() const {
    return this->info;
}

int Node::getLeftCounter() const {
    return this->leftCounter;
}

Node* Node::getLeft() const {
    return this->left;
}

Node* Node::getRight() const {
    return this->right;
}

// Setters

void Node::setInfo(TElem new_info) {
    this->info = new_info;
}

void Node::increaseLeftCounter() {
    this->leftCounter += 1;
}

void Node::decreaseLeftCounter() {
    this->leftCounter -= 1;
}

void Node::setLeftCounter(int new_value) {
    this->leftCounter = new_value;
}

void Node::setLeft(Node* new_left) {
    this->left = new_left;
}

void Node::setRight(Node* new_right) {
    this->right = new_right;
}

Node& Node::operator=(const Node& given_node) {

    this->left = given_node.left;
    this->right = given_node.right;
    this->info = given_node.info;

    return *this;
}


