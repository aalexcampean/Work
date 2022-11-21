#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

void testNewFunctionality(){
    cout << "Test new functionality" << endl;
    Bag b;
    assert(b.isEmpty() == true);
    assert(b.size() == 0);
    b.add(5);
    b.add(5);
    b.add(5);
    b.add(5);
    assert(b.size() == 4);
    b.add(1);
    b.add(1);
    b.add(1);
    b.add(1);
    assert(b.size() == 8);
    b.add(10);
    b.add(10);
    b.add(10);
    b.add(10);
    b.add(10);
    assert(b.size() == 13);
    b.add(7);
    b.add(7);
    b.add(7);
    assert(b.size() == 16);
    b.add(11);
    b.add(11);
    assert(b.size() == 18);
    b.add(13);
    assert(b.size() == 19);
    b.add(-3);
    b.add(-3);
    b.add(-3);
    b.add(-3);
    assert(b.size() == 23);

    assert(b.elementsWithThisFrequency(4) == 3);

    b.add(13);
    b.add(13);
    b.add(13);
    assert(b.size() == 26);

    assert(b.elementsWithThisFrequency(4) == 4);

    b.remove(5);
    b.remove(5);
    b.remove(5);
    b.remove(5);
    assert(b.size() == 22);
    b.remove(-3);
    b.remove(-3);
    b.remove(-3);
    b.remove(-3);
    assert(b.size() == 18);
    assert(b.elementsWithThisFrequency(4) == 2);

    try{
        assert(b.elementsWithThisFrequency(0) == 0);
    }
    catch (exception){
    }

    try{
        assert(b.elementsWithThisFrequency(-5) == 0);
    }
    catch (exception){
    }

}

int main() {
    system("leaks Assignment1_DSA");

    testNewFunctionality();
    cout << "Test new functionality over" << endl;

	testAll();
	cout << "Short tests over" << endl;

	testAllExtended();
	cout << "All test over" << endl;

    system("leaks Assignment1_DSA");
}