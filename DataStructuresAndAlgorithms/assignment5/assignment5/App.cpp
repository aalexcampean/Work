#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

#include "ListIterator.h"
#include "SortedIndexedList.h"

bool relation12(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

void firstTests() {
    SortedIndexedList list = SortedIndexedList(relation12);
    assert(list.size() == 0);
    assert(list.isEmpty());
    list.add(11);
    list.add(7);
    list.add(2);
    list.add(9);
    list.add(4);
    list.add(8);
    list.add(20);
    list.add(19);
    list.add(25);
    list.add(15);
    list.add(13);
    list.add(17);

    ListIterator li = list.iterator();
    assert(li.getCurrent() == 2);
    li.jumpForward(3);
    assert(li.getCurrent() == 8);

    li.jumpForward(4);
    assert(li.getCurrent() == 15);

    li.jumpForward(3);
    assert(li.getCurrent() == 20);

    try {
        li.jumpForward(3);
    }
    catch (std::exception){
//        std::cout << "--exception caught--\n";
    }

}


int main(){
    firstTests();
    testAll();
    testAllExtended();
    std::cout<<"Finished ALL Tests!"<<std::endl;
	system("pause");
}