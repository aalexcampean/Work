//
// Created by Alex Campean on 06.04.2022.
//

#include "Tests/Tests.h"
#include "UserInterface/Ui.h"

int main() {
    testAll();
    Repository repository;
    Service service(&repository);
    Ui ui(&service);
    ui.start();
}