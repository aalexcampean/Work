#pragma once
#include "Node.h"
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;


class SortedSet {
	friend class SortedSetIterator;
private:
    Node* elems;
    int head;
    int tail;
    int firstEmpty;
    int capacity;
    int length;
    Relation rel;

    // resizes the array containing the nodes
    void resize();

public:
	//constructor
	SortedSet(Relation r);

    // destructor
    ~SortedSet();

    SortedSet& operator=(const SortedSet& given_set);

    // allocate
    int allocate();

    // free
    void free(int pos);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;

	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//new functionality
    //adds all elements of s into the SortedSet (assume both SortedSets use the same relation)
    void unionOfSets(const SortedSet& s);

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;




};
