#include "Node.h"

// Constructors, Destructor

Node::Node() {
    DynamicArray<TValue> designated_da;
    this->da = designated_da;
    this->next = nullptr;
}


Node::Node(const Node& n) {
    this->key = n.key;
    this->da = n.da;
    this->next = n.next;
}


Node::~Node() {
//    delete this->next;
}

void Node::resize() {
    this->da.resizeDynamicArray();
}

// Operators Overload

Node& Node::operator=(const Node* n) {
    this->key = n->key;
    this->da = n->da;
    this->next = n->next;

    return *this;
}

TValue Node::operator[](int index) {
    return this->da[index];
}

// Getters

TKey Node::Key() const {
    return this->key;
}

DynamicArray<TValue>& Node::DA() {
    return this->da;
}

int Node::DALength() {
    return this->da.Length();
}

int Node::DACapacity() {
    return this->da.Capacity();
}

//TValue Node::DAElement(int index) {
//    return this->da[index];
//}

Node* Node::Next() const {
    return this->next;
}

// Setters

void Node::setKey(TKey new_key) {
    this->key = new_key;
}


void Node::setNext(Node *new_next) {
    this->next = new_next;
}

// Add, Delete

void Node::addElement(TValue elem) {
    this->da.addElement(elem);
}

void Node::removeElement(TValue elem) {
    this->da.removeElement(elem);
}

int Node::DAGetIndex(TValue elem) {
    return this->da.getIndex(elem);
}













