//
// Created by Alex Campean on 05.05.2022.
//
#include "UI/UI.h"

int main() {
    Service service;
    UI ui(&service);
    ui.startUI();

    return 0;
}