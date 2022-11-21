#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;

void testNewFunctionality() {
    cout << "Test new functionality" << endl;

    MultiMap m;
    assert(m.isEmpty() == true);
    assert(m.size() == 0);
    for (int i = 0; i < 10; i++) {
        m.add(i, i);
    }
    assert(m.size() == 10);

    MultiMapIterator it = m.iterator();
    assert(it.valid() == true);

    TElem pair{0, 0};
    assert(it.getCurrent() == pair);
    it.jumpForward(5);

    pair = {5, 5};
    assert(it.getCurrent() == pair);
    it.jumpForward(4);

    pair = {9, 9};
    assert(it.getCurrent() == pair);

    try {
        it.jumpForward(5);
    }
    catch(exception){

    }
}

int main() {
    testNewFunctionality();
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
