//
// Created by Alex Campean on 16.03.2022.
//
#include "Tests/Tests.h"
#include "Ui/Ui.h"
#include <stdlib.h>

int main(){
    system("leaks a3_4_aalexcampean");
    testAll();
    UserInterface* ui = createUserInterface();
    startUi(ui);
    system("leaks a3_4_aalexcampean");

}