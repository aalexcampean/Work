#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <cmath>

using namespace std;


MultiMap::MultiMap() {
    this->hash_capacity = 10;
    this->hash_length = 0;
    this->hash_nr_of_elements = 0;

    this->hash_table = new Node*[this->hash_capacity];
    int i;
    for (i = 0; i < this->hash_capacity; i++) {
        this->hash_table[i] = nullptr;
    }
}
// Complexity
//
// Total Complexity: Theta(n) : n = hash_capacity


int MultiMap::hashFunction(TKey given_key) const {
    return abs(given_key) % this->hash_capacity;
}
// Complexity
//
// Total Complexity: Theta(1)


void MultiMap::resize_rehash() {
    this->hash_capacity *= 2;
    Node** resized_hash = new Node*[this->hash_capacity];
    int i;
    for (i = 0; i < this->hash_capacity; i++)
        resized_hash[i] = nullptr;

    Node* current_node;
    for (i = 0; i < this->hash_capacity/2; i++) {
        current_node = this->hash_table[i];
        while (current_node != nullptr) {
            int pos = this->hashFunction(current_node->Key());

            Node* new_node = new Node;
            if (new_node->DACapacity() < current_node->DALength())
                new_node->resize();
            *new_node = current_node;

            new_node->setNext(resized_hash[pos]);
            resized_hash[pos] = new_node;
            current_node = current_node->Next();
        }
    }
    for (i = 0; i < this->hash_capacity / 2; i++) {
        while (this->hash_table[i] != nullptr) {
            current_node = this->hash_table[i]->Next();
            delete this->hash_table[i];
            this->hash_table[i] = current_node;
        }
    }
    delete[] this->hash_table;
    this->hash_table = resized_hash;
}
// Complexity
//
// Total Complexity: Theta(n+n/2 * m + n/2 * m) = Theta(n * m) : n = hash_capacity, m = the number of keys hashed to a given position


void MultiMap::add(TKey c, TValue v) {
	int pos = this->hashFunction(c);

    if (this->hash_table[pos] == nullptr) {
        Node* new_node = new Node;
        new_node->setKey(c);
        new_node->addElement(v);
        this->hash_table[pos] = new_node;
        this->hash_length += 1;
    }
    else {
        Node* current_node = this->hash_table[pos];
        while (current_node != nullptr && current_node->Key() != c) {
            current_node = current_node->Next();
        }
        if (current_node != nullptr) {
            // the key is found so it the value has to be added to the dynamic array associated to it
            current_node->addElement(v);
        }
        else {
            // the key is not found so it has to be added in a new node before all the others
            Node* new_node = new Node;
            new_node->setKey(c);
            new_node->addElement(v);
            new_node->setNext(this->hash_table[pos]);
            this->hash_table[pos] = new_node;
            this->hash_length += 1;
        }
    }
    this->hash_nr_of_elements += 1;

    if ((double)this->hash_length / (double)this->hash_capacity >= 0.7)
        this->resize_rehash();
}
// Complexity
//
// Best Case: Theta(1) - amortized
// when the key which we want to add a value at is hashed first at a given position of the hashtable (if it exists or not)
//
// Worst Case: Theta(n) : n = hash_capacity
// when the key which we want to add a value at is hashed last at a given position of the hashtable (if it exists or not)
// and all keys are hashed on that position
//
// Total Complexity: O(n)


bool MultiMap::remove(TKey c, TValue v) {
    int pos = this->hashFunction(c);

    if (this->hash_table[pos] == nullptr)
        return false;

    if (this->hash_table[pos]->Key() == c) {
        if (this->hash_table[pos]->DAGetIndex(v) == -1)
            return false;
        this->hash_table[pos]->removeElement(v);
        if (this->hash_table[pos]->DALength() == 0) {
            Node* next_node = this->hash_table[pos]->Next();
            delete this->hash_table[pos];
            this->hash_table[pos] = next_node;
            this->hash_length -= 1;
        }
        this->hash_nr_of_elements -= 1;
        return true;
    }

    Node* current_node = this->hash_table[pos];
    Node* previous_node = nullptr;
    while (current_node != nullptr && current_node->Key() != c) {
        previous_node = current_node;
        current_node = current_node->Next();
    }

    if (current_node == nullptr)
        return false;
    else {
        if (current_node->DAGetIndex(v) == -1)
            return false;
        current_node->removeElement(v);
        if (current_node->DALength() == 0) {
            previous_node->setNext(current_node->Next());
            delete current_node;
            this->hash_length -= 1;
        }
        this->hash_nr_of_elements -= 1;
        return true;
    }
}
// Complexity
//
// Best Case: Theta(1)
// when the key which we want to remove a value at is hashed first at a given position of the hashtable (if it exists or not)
//
// Worst Case: Theta(n) : n = hash_capacity
// when the key which we want to remove a value at is hashed last at a given position of the hashtable (if it exists or not)
// and all keys are hashed on that position
//
// Total Complexity: O(n)


vector<TValue> MultiMap::search(TKey c) const {
	int pos = this->hashFunction(c);
	Node* current_node = this->hash_table[pos];
	while (current_node != nullptr && current_node->Key() != c) {
	    current_node = current_node->Next();
	}
    vector<TValue> return_vector;
	if (current_node != nullptr) {
        int i;
        for (i = 0; i < current_node->DALength(); i++) {
            return_vector.push_back(current_node->DA()[i]);
        }
    }
	return return_vector;
}
// Complexity
//
// Best Case: Theta(1)
// when the key which we want to search for is hashed first at a given position of the hashtable (if it exists or not)
// and it has only one value associated to it (here lenDA is 1)
//
// Worst Case: Theta(n+lenDA) : n = hash_capacity
// when the key which we want to search for is hashed last at a given position of the hashtable (if it exists or not)
// and all keys are hashed on that position
//
// Total Complexity: O(n)


int MultiMap::size() const {
	return this->hash_nr_of_elements;
}
// Complexity
//
// Total Complexity: Theta(1)


bool MultiMap::isEmpty() const {
	if (this->hash_length == 0)
	    return true;
    return false;
}
// Complexity
//
// Total Complexity: Theta(1)


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    int i;
    for (i = 0; i < this->hash_capacity; i++) {
        Node* current_node;
        while (this->hash_table[i] != nullptr) {
            current_node = this->hash_table[i]->Next();
            delete this->hash_table[i];
            this->hash_table[i] = current_node;
        }
    }
    delete[] this->hash_table;
}
// Complexity
//
// Total Complexity: Theta(n * m * lenDa[m]) : n = hash_capacity, m = the number of keys hashed to a given position


