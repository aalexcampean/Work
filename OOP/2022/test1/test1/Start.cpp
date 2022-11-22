//
// Created by Alex Campean on 06.04.2022.
//

#include "UserInterface/Ui.h"
#include "Tests/Tests.h"

int main() {
    testAll();
    Repository repository;
    Service service(&repository);
    Ui ui(&service);
    ui.start();
}