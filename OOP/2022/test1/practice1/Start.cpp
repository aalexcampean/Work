//
// Created by Alex Campean on 04.04.2022.
//

#include "Tests/Tests.h"
#include "UserInterface/UI.h"

int main() {
    testAll();

    /// Assemble
    Repository repository;
    Service service(&repository);
    UI ui(&service);
    ui.start();
}