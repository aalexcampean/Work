#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>
#include <algorithm>

SortedIndexedList::SortedIndexedList(Relation r) {
    this->root = nullptr;
    this->numberOfElements = 0;
    this->relation = r;
}
// Complexity :
// Total Complexity : Theta(1)

int SortedIndexedList::size() const {
    return this->numberOfElements;
}
// Complexity :
// Total Complexity : Theta(1)

bool SortedIndexedList::isEmpty() const {
	if (this->numberOfElements == 0)
        return true;
	return false;
}
// Complexity :
// Total Complexity : Theta(1)

TComp SortedIndexedList::getElement(int i) const {
    if (i < 0 || i >= this->numberOfElements)
        throw exception();

    Node *currentNode = this->root;
    int currentPosition = currentNode->getLeftCounter();
    int currentLeftCounter = 0;

    while (currentPosition != i) {
        if (i < currentPosition) {
            currentLeftCounter = currentNode->getLeftCounter();
            currentNode = currentNode->getLeft();
            currentPosition -= (currentLeftCounter - currentNode->getLeftCounter());
        }
        else {
            currentNode = currentNode->getRight();
            currentPosition += currentNode->getLeftCounter() + 1;
        }
    }

    return currentNode->getInfo();
}
// Complexity :
// Best Case : Theta(1) - when we want to return the element on the first position
// Worst Case : Theta(n) - when we want to return the element on the last position
// Total Complexity : O(n)

TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= this->numberOfElements)
        throw exception();

    // if the current node is the root and we don't have any other nodes in the tree
    if (this->numberOfElements == 1) {
        TComp returnValue = this->root->getInfo();
        delete this->root;
        this->numberOfElements -= 1;
        return returnValue;
    }

    // perform a search on the tree until we find the desired node
    Node *deleteNode = this->getNode(i);
    Node *parentNode = this->findParent(deleteNode);

    // if the current node has no children
    if (this->noChildren(deleteNode))
        this->linkParentChild(parentNode, deleteNode, nullptr);

    // if the current node has 1 child
    else if (deleteNode->getLeft() == nullptr || deleteNode->getRight() == nullptr)
        // if the current node has a left child
        if (deleteNode->getLeft()  == nullptr)
            if (deleteNode == this->root)
                this->root = deleteNode->getRight();
            else
                this->linkParentChild(parentNode, deleteNode, deleteNode->getRight());
        // if the current node has a right child
        else
            if (deleteNode == this->root)
                this->root = deleteNode->getRight();
            else
                this->linkParentChild(parentNode, deleteNode, deleteNode->getLeft());

    // if the current node has 2 children
    else {
        Node* maxNode = this->findMaxInSubtree(deleteNode);
        Node* parentMaxNode = this->findParent(maxNode);

        this->linkParentChild(parentMaxNode, maxNode, maxNode->getLeft());

        // link the new max with the children of the current node
        maxNode->setLeft(deleteNode->getLeft());
        maxNode->setRight(deleteNode->getRight());
        if (parentMaxNode == deleteNode)
            maxNode->setLeftCounter(deleteNode->getLeftCounter());
        else
            maxNode->setLeftCounter(deleteNode->getLeftCounter() - 1);

        if (deleteNode != this->root)
            // link the new max to the parent of the deleted node
            this->linkParentChild(parentNode, deleteNode, maxNode);
        else
            this->root = maxNode;
    }

    Node* parseNode = this->root;
    while (parseNode != parentNode && parentNode != nullptr) {
        if (this->relation(parseNode->getInfo(), parentNode->getInfo()))
            parseNode = parseNode->getRight();
        else {
            parseNode->decreaseLeftCounter();
            parseNode = parseNode->getLeft();
        }
    }

    TComp returnValue = deleteNode->getInfo();
    deleteNode->setLeft(nullptr);
    deleteNode->setRight(nullptr);

    delete deleteNode;
    this->numberOfElements -= 1;
    return returnValue;
}
// Complexity :
// Best Case : Theta(1) - when the position we want to remove a node from belongs to the root
// Worst Case : Theta(n) - when the position we want to remove a node from belongs to a node that has 2 children
// Total Complexity : O(n)

int SortedIndexedList::search(TComp e) const {
    if (this->numberOfElements == 0)
        return -1;

    Node *currentNode = this->root;
    int currentPosition = currentNode->getLeftCounter();
    int currentLeftCounter = 0;

    while (currentNode->getInfo() != e) {
        if (this->relation(currentNode->getInfo(), e)) {
            currentNode = currentNode->getRight();
            if (currentNode == nullptr)
                break;
            currentPosition += currentNode->getLeftCounter() + 1;
        }
        else {
            currentLeftCounter = currentNode->getLeftCounter();
            currentNode = currentNode->getLeft();
            if (currentNode == nullptr)
                break;
            currentPosition -= (currentLeftCounter - currentNode->getLeftCounter());
        }
    }

    if (currentNode == nullptr)
        currentPosition = -1;
    return currentPosition;
}
// Complexity :
// Best Case : Theta(1) - the element we are searching for is exactly the root
// Worst Case : Theta(n) - the element we are searching for is on the left most / right most node and all the nodes of the tree are on that same side
// Total Complexity : O(n)

void SortedIndexedList::add(TComp e) {
    this->root = this->addRecursive(this->root, e);
    this->numberOfElements += 1;
}
// Complexity :
// Best Case : Theta(1) - the element we want to add should be added right after the root, left / right
// Worst Case : Theta(n) - the element we want to add is on the left most / right most node and all the nodes of the tree are on that same side
// Total Complexity : O(n)

Node* SortedIndexedList::addRecursive(Node* currentNode, TComp e) {
    if (currentNode == nullptr) {
        Node* newNode = new Node;
        newNode->setInfo(e);
        currentNode = newNode;
    }
    else if (this->relation(currentNode->getInfo(), e))
        currentNode->setRight(this->addRecursive(currentNode->getRight(), e));
    else {
        currentNode->setLeft(this->addRecursive(currentNode->getLeft(), e));
        currentNode->increaseLeftCounter();
    }
    return currentNode;
}
// Complexity :
// Best Case : Theta(1) - the element we want to add should be added right after the root, left / right
// Worst Case : Theta(n) - the element we want to add is on the left most / right most node and all the nodes of the tree are on that same side
// Total Complexity : O(n)

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
//    std::stack<Node*> nodeStack;
//    Node* currentNode = this->root;
//    while (currentNode != nullptr) {
//        nodeStack.push(currentNode);
//        currentNode = currentNode->getLeft();
//    }
//
//    while (!nodeStack.empty()) {
//        currentNode = nodeStack.top();
//        nodeStack.pop();
//
//        Node* deleteNode = currentNode;
//        currentNode = currentNode->getRight();
//        delete deleteNode;
//
//        while (currentNode != nullptr) {
//            nodeStack.push(currentNode);
//            currentNode = currentNode->getLeft();
//        }
//    }
}

Node *SortedIndexedList::findMaxInSubtree(Node *subRoot) {
    Node *maxNode = subRoot->getLeft();
    if (maxNode == nullptr)
        return nullptr;

    while (maxNode->getRight() != nullptr) {
        maxNode = maxNode->getRight();
    }
    return maxNode;
}
// Complexity :
// Best Case : Theta(1) - the element we are searching for is the only one in the left subtree that has the subRoot as the root
// Worst Case : Theta(n) - the element we are searching for is on the right most node in the left subtree that has the subRoot as the root and all the nodes of the tree are on that same side
// Total Complexity : O(n)

Node *SortedIndexedList::findParent(Node* child) {
    Node *parseNode = this->root;
    if (parseNode == child)
        return nullptr;

    while (parseNode != nullptr && parseNode->getLeft() != child && parseNode->getRight() != child) {
        if (this->relation(parseNode->getInfo(), child->getInfo()))
            parseNode = parseNode->getRight();
        else
            parseNode = parseNode->getLeft();
    }
    return parseNode;
}
// Complexity :
// Best Case : Theta(1) - the element we are searching a parent for is exactly the root
// Worst Case : Theta(n) - the element we are searching a parent for is on the left most / right most node and all the nodes of the tree are on that same side
// Total Complexity : O(n)

Node* SortedIndexedList::getNode(int i) {
    if (i < 0 || i >= this->numberOfElements)
        throw exception();

    Node *currentNode = this->root;
    int currentPosition = currentNode->getLeftCounter();
    int currentLeftCounter = 0;

    while (currentPosition != i) {
        if (i < currentPosition) {
            currentLeftCounter = currentNode->getLeftCounter();
            currentNode = currentNode->getLeft();
            currentPosition -= (currentLeftCounter - currentNode->getLeftCounter());
        }
        else {
            currentNode = currentNode->getRight();
            currentPosition += currentNode->getLeftCounter() + 1;
        }
    }

    return currentNode;
}
// Complexity :
// Best Case : Theta(1) - the element we are searching for on the given position is exactly the root
// Worst Case : Theta(n) - the element we are searching a parent for on the given position is on the left most / right most node and all the nodes of the tree are on that same side
// Total Complexity : O(n)

bool SortedIndexedList::noChildren(Node* node) {
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        return true;
    }
    return false;
}
// Complexity :
// Total Complexity : Theta(1)

void SortedIndexedList::linkParentChild(Node* parent, Node* child, Node* newNode) {
    // if it is a right child
    if (parent->getLeft() == child){
        parent->decreaseLeftCounter();
        parent->setLeft(newNode);
    }
    //if it is a right child
    else
        parent->setRight(newNode);
}
// Complexity :
// Total Complexity : Theta(1)