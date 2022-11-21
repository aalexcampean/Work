#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
    Node* current_node;
    int current_pos;
    int current_da_pos;

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
    //moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the MultiMap.
    //throws an exception if the iterator is invalid or if k is 0 zero negative
    void jumpForward(int k);
};

