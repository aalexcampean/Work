#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    this->current_pos = 0;
    while (this->current_pos < c.hash_capacity && c.hash_table[this->current_pos] == nullptr)
        this->current_pos += 1;

    if (this->current_pos == c.hash_capacity)
        this->current_node = nullptr;
    else {
        this->current_node = c.hash_table[this->current_pos];
        this->current_da_pos = 0;
    }
}
// Complexity
//
// Best Case: Theta(1)
// when there is a key hashed on the first position
//
// Worst Case: Theta(n) : n = hash_capacity
// when there is a key hashed only on the last position or the hashtable is empty
//
// Total Complexity: O(n)


TElem MultiMapIterator::getCurrent() const{
    if (!this->valid())
        throw exception();
    TElem return_pair{this->current_node->Key(), this->current_node->DA()[this->current_da_pos]};
    return return_pair;
}
// Complexity
// Total Complexity: Theta(1)


bool MultiMapIterator::valid() const {
    if (this->current_pos == this->col.hash_capacity)
        return false;
    return true;
}
// Complexity
// Total Complexity: Theta(1)


void MultiMapIterator::next() {
    if (!this->valid())
        throw exception();
    if (this->current_node->Next() != nullptr) {
        if (this->current_da_pos < this->current_node->DALength() - 1)
            this->current_da_pos += 1;
        else {
            this->current_node = this->current_node->Next();
            this->current_da_pos = 0;
        }
    }
    else {
        if (this->current_da_pos < this->current_node->DALength() - 1)
            this->current_da_pos += 1;
        else {
            this->current_pos += 1;
            while (this->current_pos < this->col.hash_capacity && this->col.hash_table[this->current_pos] == nullptr) {
                this->current_pos += 1;
            }
            if (this->current_pos == this->col.hash_capacity)
                this->current_node = nullptr;
            else {
                this->current_node = this->col.hash_table[this->current_pos];
                this->current_da_pos = 0;
            }
        }
    }
}
// Complexity
//
// Best Case: Theta(1)
// when either there are elements left in the dynamic array associated to the current key,
// when there is another key hashed to the same position after the current one
// or when the next key is hashed on the next position in the hashtable
//
// Worst Case: Theta(n) : n = hash_capacity
// when the next key is hashed on the last position of the hashtable and the current one is on the first
//
// Total Complexity: O(n)


void MultiMapIterator::first() {
    this->current_pos = 0;
    while (this->current_pos < this->col.hash_capacity && this->col.hash_table[this->current_pos] == nullptr)
        this->current_pos += 1;

    if (this->current_pos == this->col.hash_capacity)
        this->current_node = nullptr;
    else {
        this->current_node = this->col.hash_table[this->current_pos];
        this->current_da_pos = 0;
    }
}
// Complexity
// Best Case: Theta(1)
// when there is a key hashed on the first position
//
// Worst Case: Theta(n) : n = hash_capacity
// when there is a key hashed only on the last position or the hashtable is empty
//
// Total Complexity: O(n)

void MultiMapIterator::jumpForward(int k) {
    if (k <= 0)
        throw exception();
    while (k > 0) {
        this->next();
        k -= 1;
    }
}
// Complexity
// Best Case: Theta(1)
// when we actually have to perform just 1 next operation that is in best case
//
// Worst Case: Theta(n) : n = hash_capacity
// when there is a key hashed only on the last position or the hashtable is empty
//
// Total Complexity: O(n)
