#pragma once
#include "SortedIndexedList.h"
#include <stack>


//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	Node* currentNode;
	std::stack<Node*> stack;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
    //moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the SortedList.
    // throws an exception if the iterator is invalid or if k is negative or zero
    void jumpForward(int k);
};


