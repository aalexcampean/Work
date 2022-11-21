#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = 0;
}
// Theta(1)
// constant number of operations

void BagIterator::first() {
    this->current = 0;
}
// Theta(1)
// constant number of operations

void BagIterator::next() {
    if (!this->valid()){
        throw exception();
    }
    this->current += 1;
}
// Theta(1)
// constant number of operations

bool BagIterator::valid() const {
	if (this->current < this->bag.size()){
        return true;
	}
	return false;
}
// Theta(1)
// constant number of operations

TElem BagIterator::getCurrent() const
{
    if (!this->valid()){
        throw exception();
    }

    int count = 0;
    int index = 0;
//    bool first = true;

    while (count <= this->current){
        count += this->bag.list[index].second;
        index += 1;
//        first = false;
    }

    //    if (!first){
//        index -= 1;
//    }
    index -= 1;
    return this->bag.list[index].first;
}
// Best Case: Theta(1), Worst Case: Theta(size), Total Complexity: O(size)
// best case is when the current element is found on the first position of the bag
// worst case is when the current element is found on the last position of the bag