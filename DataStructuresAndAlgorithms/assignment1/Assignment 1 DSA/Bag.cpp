#include "Bag.h"
#include "BagIterator.h"
#include <iostream>
#include <exception>

using namespace std;


Bag::Bag() {

    this->capacity = 10;
	this->nrOfPairs = 0;
    this->list = new TPair[this->capacity];
}
// Theta(1)
// constant number of operations

Bag::~Bag() {
    delete[] this->list;
}
// Theta(1)
// constant number of operations

void Bag::resize() {
    this->capacity *= 2;

    TPair* new_list = new TPair[this->capacity];
    for (int i = 0; i < this->nrOfPairs; i++) {
        new_list[i] = this->list[i];
    }

    delete[] this->list;
    this->list = new_list;
}
// Theta(nrOfPairs)
// when performing this operation in all cases the bag has to be parsed completely in order for all the elements to be copied to the new dynamic array

void Bag::add(TElem elem) {
	if (this->capacity == this->nrOfPairs) {
        this->resize();
	}

    bool found = false;
	int index = 0;

	while (index < this->nrOfPairs && !found) {
	    if (this->list[index].first == elem) {
	        this->list[index].second += 1;
	        found = true;
	    }
	    index += 1;
	}

	if (!found){
        this->list[nrOfPairs].first = elem;
        this->list[nrOfPairs].second = 1;
        this->nrOfPairs += 1;
	}
}
// Best Case: Theta(1), Worst Case: Theta(nrOfPairs), Total Complexity: O(nrOfPairs)
// best case is considered when the element that should be added is on the first position
// worst case is when the element has to be added on the last position

bool Bag::remove(TElem elem) {
	bool found = false;
	int index = 0;

	while (index < this->nrOfPairs && !found) {
	    if (this->list[index].first == elem) {
            this->list[index].second -= 1;
            found = true;

            if (this->list[index].second == 0) {
                this->list[index] = this->list[nrOfPairs - 1];
                nrOfPairs -= 1;
            }
	    }
	    index += 1;
	}

    return found;
}
// Best Case: Theta(1), Worst Case: Theta(nrOfPairs), Total Complexity: O(nrOfPairs)
// best case is considered when the element that has to be deleted is on the first position
// worst case is when the element has to be deleted from the last position or it does not exist in the bag

bool Bag::search(TElem elem) const {
	bool found = false;
	int index = 0;

	while (index < this->nrOfPairs && !found) {
	    if (this->list[index].first == elem) {
            found = true;
	    }
	    index += 1;
	}

 	return found;
}
// Best Case: Theta(1), Worst Case: Theta(nrOfPairs), Total Complexity: O(nrOfPairs)
// best case is considered when the element that has to be searched for is on the first position
// worst case is when the element that has to be searched for is on the last position or it does not exist in the bag

int Bag::nrOccurrences(TElem elem) const {
    bool found = false;
    int index = 0;
    int occurrences = 0;

	while (index < this->nrOfPairs && !found) {
	    if (this->list[index].first == elem){
            occurrences = this->list[index].second;
            found = true;
	    }
	    index += 1;
	}
	return occurrences;
}
// Best Case: Theta(1), Worst Case: Theta(nrOfPairs), Total Complexity: O(nrOfPairs)
// best case is considered when the element which the nr of occurrences has to be counted is on the first position
// worst case is when the element which the nr of occurrences has to be counted is on the last position or it does not exist in the bag

int Bag::size() const {
    int count = 0;

    for (int i = 0; i < this->nrOfPairs; i++) {
        count += this->list[i].second;
    }

    return count;
}
// Theta(nrOfPairs)
// when performing this operation in all cases the bag has to be parsed completely

bool Bag::isEmpty() const {
	if (this->nrOfPairs == 0){
        return true;
	}
	return false;
}
// Theta(1)
// constant number of operations

int Bag::elementsWithThisFrequency(int frequency) const{
    if (frequency <= 0){
        throw exception();
    }
    int count = 0;
    for (int i = 0; i < this->nrOfPairs; i++) {
        if (this->list[i].second == frequency){
            count += 1;
        }
    }
    return count;
}
// Total Complexity: Theta(nrOfPairs)
// in all cases, all the elements have to be parsed in order to return a correct counter

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
// Theta(1)
// constant number of operations

