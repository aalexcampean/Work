#include "SortedSet.h"
#include "SortedSetIterator.h"

// constructor
SortedSet::SortedSet(Relation r) {
    this->rel = r;

    // let the INIT_CAPACITY be 10
    this->capacity = 10;
    this->length = 0;

    // allocating space for the array of nodes
    this->elems = new Node[this->capacity];

    // initializing the head and tail
    this->head = -1;
    this->tail = -1;

    // setting the links for all the positions excluding the first and the last one
    for (int i = 1; i < this->capacity - 1; i++) {
        this->elems[i].setPrev(i - 1);
        this->elems[i].setNext(i + 1);
    }

    // setting the links for the first position
    this->elems[0].setPrev(-1);
    this->elems[0].setNext(1);

    // setting the links for the last position
    this->elems[this->capacity - 1].setPrev(this->capacity - 2);
    this->elems[this->capacity - 1].setNext(-1);

    // setting first empty to be the first element
    this->firstEmpty = 0;
}
// Complexity
// Total Complexity: Theta(n), n = capacity


// destructor
SortedSet::~SortedSet() {
    delete[] this->elems;
}
// Complexity
// Total Complexity: Theta(n), n = capacity (the delete function is called for all elements of the set


// resize
void SortedSet::resize() {
    this->capacity *= 2;

    Node* new_elems = new Node[this->capacity];
    for (int i = 0; i < this->length; i++) {
        new_elems[i] = this->elems[i];
    }

    this->firstEmpty = this->length;

    // setting the links for all the newly added positions excluding the first and the last one
    for (int i = this->length + 1; i < this->capacity - 1; i++) {
        new_elems[i].setPrev(i - 1);
        new_elems[i].setNext(i + 1);
    }

    // setting the links for the first position
    new_elems[this->length].setPrev(-1);
    new_elems[this->length].setNext(this->length + 1);

    // setting the links for the last position
    new_elems[this->capacity - 1].setPrev(this->capacity - 2);
    new_elems[this->capacity - 1].setNext(-1);

    delete[] this->elems;
    this->elems = new_elems;
}
// Complexity
// Total Complexity: Theta(n), n = capacity (the delete function is called for all elements of the set


// allocate
int SortedSet::allocate() {
    int new_elem = this->firstEmpty;
    if (new_elem != -1) {
        this->firstEmpty = this->elems[this->firstEmpty].getNext();
        if (this->firstEmpty != -1)
            this->elems[this->firstEmpty].setPrev(-1);
        this->elems[new_elem].setNext(-1);
        this->elems[new_elem].setPrev(-1);
    }
    return new_elem;
}
// Complexity
// Total Complexity: Theta(1)


// free
void SortedSet::free(int pos) {
    this->elems[pos].setNext(this->firstEmpty);
    this->elems[pos].setPrev(-1);
    if (this->firstEmpty != -1)
        this->elems[this->firstEmpty].setPrev(pos);
    this->firstEmpty = pos;
}
// Complexity
// Total Complexity: Theta(1)


// add functionality
bool SortedSet::add(TComp elem) {
    // the set is empty
    if (this->head == -1) {
        int pos = this->allocate();
        this->elems[pos].setInfo(elem);
        this->head = pos;
        this->tail = pos;
        this->length += 1;
    }
    else {
        int current = this->head;
        while (current != -1 && this->rel(this->elems[current].getInfo(), elem)) {
            // the element is already in the set
            if (this->elems[current].getInfo() == elem) {
                return false;
            }
            current = this->elems[current].getNext();
        }

        int insert_pos = this->allocate();
        // the set is full and we need to make a resize
        if (insert_pos == -1) {
            this->resize();
            insert_pos = this->allocate();
        }

        // setting the provided info to the new element
        this->elems[insert_pos].setInfo(elem);

        // the element to be added should be the head
        if (current == this->head) {
            this->elems[insert_pos].setNext(head);
            this->elems[head].setPrev(insert_pos);
            head = insert_pos;
        }
        // the element to be added should be the tail
        else if (current == -1) {
            this->elems[insert_pos].setPrev(tail);
            this->elems[tail].setNext(insert_pos);
            tail = insert_pos;
        }
        // the element to be added should be on a random position in the set (taking into consideration the relation)
        else {
            // linking the new element to the rest of the set
            this->elems[insert_pos].setNext(current);
            this->elems[insert_pos].setPrev(this->elems[current].getPrev());

            // linking the rest of the set with the new element
            this->elems[this->elems[current].getPrev()].setNext(insert_pos);
            this->elems[current].setPrev(insert_pos);
        }
        this->length += 1;
    }
	return true;
}
// Complexity
// Best Case: Theta(1), when the element we want to add should be on the first position (the head) or it already exists on the first position and we do not have to do a resize
// Worst Case: Theta(n), when the element we want to add should be on the last position (the tail) or it already exists on the last position and we have to do a resize
// Total Complexity: O(n)


// remove functionality
bool SortedSet::remove(TComp elem) {
    if (this->head == -1) {
        return false;
    }
    else {
        int current = this->head;
        while (current != -1 && this->rel(this->elems[current].getInfo(), elem)) {
            if (this->elems[current].getInfo() == elem) {
                break;
            }
            current = this->elems[current].getNext();
        }

        // the element is not in the set
        if (current == -1 || this->elems[current].getInfo() != elem) {
            return false;
        }

        // we have one element element in the set
        if (this->head == this->tail){
            this->free(head);
            this->head = -1;
            this->tail = -1;
        }
        else {
            // the element to be deleted is exactly the head
            if (current == this->head) {
                int delete_pos = this->head;
                this->head = this->elems[this->head].getNext();
                this->elems[this->head].setPrev(-1);
                this->free(delete_pos);
            }
            // the element to be deleted is exactly the tail
            else if (current == this->tail) {
                int delete_pos = this->tail;
                this->tail = this->elems[this->tail].getPrev();
                this->elems[this->tail].setNext(-1);
                this->free(delete_pos);
            }
            // the element to be deleted is on a random position in the set (taking into consideration the relation)
            else {
                int delete_pos = current;
                this->elems[this->elems[current].getNext()].setPrev(this->elems[current].getPrev());
                this->elems[this->elems[current].getPrev()].setNext(this->elems[current].getNext());
                this->free(delete_pos);
            }
        }
        this->length -= 1;
        return true;
    }
}
// Complexity
// Best Case: Theta(1), when the element we want to remove is on the first position (the head) or it should have been on the first position but it doesn't exist in the set
// Worst Case: Theta(n), when the element we want to remove is on the last position (the tail) or it should have been on the last position but it doesn't exist in the set
// Total Complexity: O(n)


// search functionality
bool SortedSet::search(TComp elem) const {
	int current = this->head;
    while (current != -1 && this->elems[current].getInfo() != elem) {
        current = this->elems[current].getNext();
    }
    if (current != -1) {
        return true;
    }
	return false;
}
// Complexity
// Best Case: Theta(1), when the element we want to find is on the first position (the head) or it should have been on the first position but it doesn't exist in the set
// Worst Case: Theta(n), when the element we want to find is on the last position (the tail) or it should have been on the last position but it doesn't exist in the set
// Total Complexity: O(n)


// size
int SortedSet::size() const {
    return this->length;
}
// Complexity
// Total Complexity: Theta(1)


// is empty
bool SortedSet::isEmpty() const {
	if (this->length == 0) {
        return true;
	}
    return false;
}
// Complexity
// Total Complexity: Theta(1)


void SortedSet::unionOfSets(const SortedSet& s) {
    SortedSet new_set(s.rel);
    int current_s = s.head;
    int current_set = this->head;

    while (current_s != -1 && current_set != -1) {
        if (this->rel(this->elems[current_set].getInfo(), s.elems[current_s].getInfo())) {
            new_set.add(this->elems[current_set].getInfo());
            current_set = this->elems[current_set].getNext();
        }
        else {
            new_set.add(s.elems[current_s].getInfo());
            current_s = s.elems[current_s].getNext();
        }
    }

    if (current_s == -1 && current_set != -1) {
        new_set.add(this->elems[current_set].getInfo());
        current_set = this->elems[current_set].getNext();
    }
    else if (current_s != -1) {
        new_set.add(s.elems[current_s].getInfo());
        current_s = s.elems[current_s].getNext();
    }
    *this = new_set;
}
// Complexity
// Total Complexity: Theta(size_of_s + size_of_current_set)


SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet &SortedSet::operator=(const SortedSet &given_set) {
    delete[] this->elems;
    this->elems = new Node[given_set.capacity];
    for (int i = 0; i < given_set.capacity; i++) {
        this->elems[i] = given_set.elems[i];
    }
    this->head = given_set.head;
    this->tail = given_set.tail;
    this->firstEmpty = given_set.firstEmpty;
    this->capacity = given_set.capacity;
    this->length = given_set.length;

    return *this;
}
// Complexity
// Total Complexity: Theta(size_of_s + size_of_current_set)







