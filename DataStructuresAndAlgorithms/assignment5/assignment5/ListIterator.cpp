#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    this->currentNode = list.root;
    while (currentNode != nullptr) {
        this->stack.push(currentNode);
        currentNode = currentNode->getLeft();
    }

    if (!this->stack.empty())
        this->currentNode = this->stack.top();
    else
        currentNode = nullptr;
}
// Complexity :
// Best Case : Theta(1) - if the root has an empty left subtree
// Worst Case : Theta(n) - if all the node are on the left of their parents
// Total Complexity : O(n)

void ListIterator::first() {
    std::stack<Node*> newStack;
    this->stack = newStack;

    this->currentNode = list.root;
    while (currentNode != nullptr) {
        this->stack.push(currentNode);
        currentNode = currentNode->getLeft();
    }

    if (!this->stack.empty())
        this->currentNode = this->stack.top();
    else
        currentNode = nullptr;
}
// Complexity :
// Best Case : Theta(1) - if the root has an empty left subtree
// Worst Case : Theta(n) - if all the node are on the left of their parents
// Total Complexity : O(n)

void ListIterator::next() {
    if (!this->valid())
        throw exception();

    this->currentNode = this->stack.top();
    this->stack.pop();

    if (currentNode->getRight() != nullptr) {
        currentNode = currentNode->getRight();
        while (currentNode != nullptr) {
            this->stack.push(currentNode);
            currentNode = currentNode->getLeft();
        }
    }

    if (!this->stack.empty())
        this->currentNode = this->stack.top();
    else
        this->currentNode = nullptr;
}
// Complexity :
// Best Case : Theta(1) - when we the next node we have to visit is already in the stack
// Worst Case : Theta(n) - when the current node has 1 right child that has all the other nodes on its left
// Total Complexity : O(n)

bool ListIterator::valid() const {
	if (currentNode == nullptr)
	    return false;
    return true;
}
// Complexity :
// Total Complexity : Theta(1)

TComp ListIterator::getCurrent() const {
    if (!this->valid())
        throw exception();
    else
        return currentNode->getInfo();
}
// Complexity :
// Total Complexity : Theta(1)


void ListIterator::jumpForward(int k) {
    if (k <= 0)
        throw exception();

    while (k > 0) {
        if (!this->valid())
            throw exception();

        this->currentNode = this->stack.top();
        this->stack.pop();

        if (currentNode->getRight() != nullptr) {
            currentNode = currentNode->getRight();
            while (currentNode != nullptr) {
                this->stack.push(currentNode);
                currentNode = currentNode->getLeft();
            }
        }

        if (!this->stack.empty())
            this->currentNode = this->stack.top();
        else
            this->currentNode = nullptr;

        k -= 1;
    }

}
// Complexity :
// Best Case : Theta(1) - when k is 1 and we need to essentially perform a next operation that would also be in best case
// Worst Case : Theta(k*n)
// Total Complexity : O(n)

