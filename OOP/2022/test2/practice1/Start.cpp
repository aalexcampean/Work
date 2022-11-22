//
// Created by Alex Campean on 05.05.2022.
//
#include "UI/UI.h"

int main() {
    Repository repository;
    Service service(&repository);
    UI ui(&service);
    ui.startUI();

    return 0;
}
