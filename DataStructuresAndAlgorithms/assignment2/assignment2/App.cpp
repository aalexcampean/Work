
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;

void testNewFunctionality() {
    cout << "Test new functionality" << endl;
    Matrix m(10, 10);
    m.modify(0, 0, 10);
    m.modify(0, 5, 10);
    m.modify(0, 1, 10);

    m.modify(1, 0, 10);
    m.modify(1, 5, 10);
    m.modify(1, 6, 10);
    m.modify(1, 9, 10);

    m.modify(2, 0, 10);
    m.modify(2, 3, 10);

    m.modify(0, 4, 10);
    m.modify(0, 3, 10);

    m.modify(1, 0, 333);

    m.modify(9, 9, 4);

    assert(m.element(0, 0) == 10);
    assert(m.element(9, 9) == 4);

    m.setMainDiagonal(66);
    assert(m.element(0, 0) == 66);
    assert(m.element(1, 1) == 66);
    assert(m.element(2, 2) == 66);
    assert(m.element(3, 3) == 66);
    assert(m.element(4, 4) == 66);
    assert(m.element(5, 5) == 66);
    assert(m.element(6, 6) == 66);
    assert(m.element(7, 7) == 66);
    assert(m.element(8, 8) == 66);
    assert(m.element(9, 9) == 66);

    Matrix m1(5, 10);
    try {
        m1.setMainDiagonal(33);
    }
    catch (exception) {

    }
}

int main() {

    testNewFunctionality();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}