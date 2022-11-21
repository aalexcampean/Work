#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    this->nrOfLines = nrLines;
    this->nrOfColumns = nrCols;
    this->nrOfNonZeroElements = 0;

    this->head = nullptr;
    this->tail = nullptr;
}
// Total complexity: Theta(1) - constant number of operations


int Matrix::nrLines() const {
    return this->nrOfLines;
}
// Total complexity: Theta(1) - constant number of operations


int Matrix::nrColumns() const {
    return this->nrOfColumns;
}
// Total complexity: Theta(1) - constant number of operations


TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->nrOfLines || j < 0 || j >= this->nrOfColumns) {
        throw std::exception();
	}

    // the list is empty so we return the NULL_TELEM
	if (this->head == nullptr) {
        return NULL_TELEM;
	}
    // the list has only one element and it's coordinates are different from th desired ones so we return the NULL_TELEM
	if (this->head == this->tail) {
	    if (this->head->Row() == i && this->head->Col() == j) {
            return this->head->Value();
	    }
	    else {
            return NULL_TELEM;
	    }
	}

    // we parse the list in the search fo the given element
    Node *current_node = head;
    while (current_node != nullptr && current_node->Row() <= i) {
        if ((current_node->Row() < i) || (current_node->Row() == i && current_node->Col() < j)) {
            current_node = current_node->Next();
        }
        else {
            break;
        }
    }

    // we got to the end of the list and did not find anything so we return the NULL_TELEM
    if (current_node == nullptr) {
        return NULL_TELEM;
    }
    // we reached an element which has the i coordinate is grater than the given i so we return the NULL_TELEM
    else if (current_node->Row() > i) {
        return NULL_TELEM;
    }
    // we reached an element which has the i coordinate equal to the given one but the j coordinate is greater than the given one so we return the NULL_TELEM
    else if (current_node->Row() == i && current_node->Col() > j) {
        return NULL_TELEM;
    }
    // we have a case where we found the element in the list so we return its value
    else {
        return current_node->Value();
    }
}
// Best Case: Theta(1) - when the element that we search for is on the first position / should be on the first position
// Worst Case: Theta(nrOfNonZeroElements) - when the element that we search for is on the last position or it should be on the last position
// Total Complexity: O(n)


TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->nrOfLines || j < 0 || j >= this->nrOfColumns) {
        throw std::exception();
    }

    // the list is empty so we add the first element
    if (this->head == this->tail && this->head == nullptr && e != 0) {
        Node *new_node = new Node;
        new_node->setRow(i);
        new_node->setColumn(j);
        new_node->setValue(e);

        head = new_node;
        tail = new_node;
        this->nrOfNonZeroElements += 1;
        return NULL_TELEM;
    }
    // the list is empty but the element that needs to be added is 0 so we do nothing
    else if (this->head == this->tail && this->head == nullptr && e == 0) {
        return NULL_TELEM;
    }
    else {
        // we parse the list in the search fo the given element
        Node *current_node = head;
        while (current_node != tail && current_node->Row() <= i) {
            if ((current_node->Row() < i) || (current_node->Row() == i && current_node->Col() < j)) {
                current_node = current_node->Next();
            }
            else {
                break;
            }
        }

        // we find the element in the list
        // we are on the head and the new value is 0 so we need to delete it
        if (current_node == head && current_node->Row() == i && current_node->Col() == j && e == 0) {
            head = current_node->Next();
            head->setPrev(nullptr);
            current_node->setNext(nullptr);
            int old_value = current_node->Value();
            delete current_node;
            return old_value;
        }
        // we are on the tail and the new value is 0 so we need to delete it
        else if (current_node == tail && current_node->Row() == i && current_node->Col() == j && e == 0) {
            tail = current_node->Prev();
            tail->setNext(nullptr);
            current_node->setPrev(nullptr);
            int old_value = current_node->Value();
            delete current_node;
            return old_value;
        }
        // we are on a random element in the middle of the list and the new value is 0 so we need to delete it
        else if (current_node->Row() == i && current_node->Col() == j && e == 0) {
            current_node->Next()->setPrev(current_node->Prev());
            current_node->Prev()->setNext(current_node->Next());
            current_node->setPrev(nullptr);
            current_node->setNext(nullptr);
            int old_value = current_node->Value();
            delete current_node;
            return old_value;
        }
        // we are on a random element in the middle of the list and the new value is different from 0 so we need to change the old value
        else if (current_node->Row() == i && current_node->Col() == j && e != 0) {
            int old_value = current_node->Value();
            current_node->setValue(e);
            return old_value;
        }
        else {
            // we don't find the element in the list
            // we are on the head and the element is different from 0 so we need to add a new head
            if (current_node == head && ((current_node->Row() > i) || (current_node->Row() == i && current_node->Col() > j)) && e != 0) {
                Node *new_node = new Node;
                new_node->setRow(i);
                new_node->setColumn(j);
                new_node->setValue(e);

                new_node->setNext(head);
                head->setPrev(new_node);
                head = new_node;
                this->nrOfNonZeroElements += 1;
                return NULL_TELEM;
            }
            // we are on the tail and the element is different from 0 so we need to add a new tail
            else if (current_node == tail && ((current_node->Row() < i) || (current_node->Row() == i && current_node->Col() < j)) && e != 0) {
                Node *new_node = new Node;
                new_node->setRow(i);
                new_node->setColumn(j);
                new_node->setValue(e);

                new_node->setPrev(tail);
                tail->setNext(new_node);
                tail = new_node;
                this->nrOfNonZeroElements += 1;
                return NULL_TELEM;
            }
            // we are on a random element in the middle of the list and the element is from 0 so we need to add a new element
            else if (((current_node->Row() > i) || (current_node->Row() == i && current_node->Col() > j)) && e != 0) {
                Node *new_node = new Node;
                new_node->setRow(i);
                new_node->setColumn(j);
                new_node->setValue(e);

                current_node->Prev()->setNext(new_node);
                new_node->setPrev(current_node->Prev());

                current_node->setPrev(new_node);
                new_node->setNext(current_node);
                this->nrOfNonZeroElements += 1;
                return NULL_TELEM;
            }
            // we did not find the element which means it is not a NonZero element so we return the value corresponding to that
            else {
                return NULL_TELEM;
            }
        }
    }
}
// Best Case: Theta(1) - when the element that we search for is on the first position / should be on the first position
// Worst Case: Theta(nrOfNonZeroElements) - when the element that we search for is on the last position or it should be on the last position
// Total Complexity: O(nrOfNonZeroElements)


// New Functionality

void Matrix::setMainDiagonal(TElem elem) {
    if (this->nrOfLines != this->nrOfColumns) {
        throw std::exception();
    }
    for (int i = 0; i < this->nrOfLines; i++) {
        this->modify(i, i, elem);
    }
}
// Best Case: ~Theta(n^2) - when none of the elements from the main diagonal are NonZero || Theta(1 + 2 + ... + n) = Theta(n(n+1)/2) = ~Theta(n^2)
// Worst Case: ~Theta(nrOfNonZeroElements^3) - when all the elements of the matrix are NonZero which means we have to parse the list of NonZero elements for each element of the main diagonal
// depending on their distance from the beginning of the line ||
// Theta(1 + (n + 2) + (2n + 3) + ... + (n(n-1) + n)) = Theta((1 + 2 + 3 + ... + n) + n(1 + 2 + 3 + ... + n - 1)) = Theta(n(n+1)/2 + n^2(n-1)/2) = Theta(1/2(n^3 + n)) = ~Theta(n^3)
// Total Complexity: O(nrOfNonZeroElements^3)
