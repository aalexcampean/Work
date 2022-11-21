#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

using namespace std;

bool Greater(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

void testNewFunctionality() {
    cout << "Test new functionality" << endl;

    //create the first set
    SortedSet s1(Greater);
    s1.add(1);
    s1.add(5);
    s1.add(14);
    s1.add(2);
    s1.add(30);
    assert(s1.size() == 5);

    //create the second set
    SortedSet s2(Greater);
    s2.add(1);
    s2.add(4);
    s2.add(20);
    s2.add(3);
    s2.add(29);
    assert(s2.size() == 5);

    //merge the 2 sets
    s1.unionOfSets(s2);
    assert(s1.size() == 9);
    assert(s1.search(4) == true);
    assert(s1.search(20) == true);
    assert(s1.search(3) == true);
    assert(s1.search(29) == true);
}

int main() {
    testNewFunctionality();
	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	system("pause");
}