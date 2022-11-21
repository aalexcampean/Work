#pragma once
#include <utility>
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
typedef int TFrequency;
typedef std::pair<TElem, TFrequency> TPair;

class BagIterator; 
class Bag {

private:

    TPair* list;
    int capacity; // maximum number of elements of type TElem stored in the list
    int nrOfPairs; // current number of elements of type TElem stored in the list

	//DO NOT CHANGE THIS PART
	friend class BagIterator;

public:
	//constructor
	Bag();

    //destructor
    ~Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appears is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

    //checks if the bag is empty
    bool isEmpty() const;

    //returns the number of elements that appear frequency times
    //throws an exception if frequency is negative or zero
    int elementsWithThisFrequency(int frequency) const;

	//returns an iterator for this bag
	BagIterator iterator() const;

private:
    // resize
    void resize();
};