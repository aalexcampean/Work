#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : set(m) {
    this->current = this->set.head;
}
// Complexity
// Total Complexity: Theta(1)


void SortedSetIterator::first() {
    this->current = this->set.head;
}
// Complexity
// Total Complexity: Theta(1)


void SortedSetIterator::next() {
    if (!this->valid()) {
        throw exception();
    }
    this->current = this->set.elems[this->current].getNext();
}
// Complexity
// Total Complexity: Theta(1)


TElem SortedSetIterator::getCurrent() {
    if (!this->valid()) {
        throw exception();
    }
    return this->set.elems[this->current].getInfo();
}
// Complexity
// Total Complexity: Theta(1)


bool SortedSetIterator::valid() const {
	if (this->current == -1) {
        return false;
	}
	return true;
}
// Complexity
// Total Complexity: Theta(1)

