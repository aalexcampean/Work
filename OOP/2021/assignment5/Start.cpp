#include <QtWidgets/QApplication>
#include "Tests/Tests.h"
#include "UserInterface/Ui.h"
#include "gui.h"

int main(int argc, char *argv[]){
//    testAll();

    QApplication a(argc, argv);
    GUI gui;
    gui.resize(600, 600);
    gui.show();
//    UserInterface ui;
//    ui.start();

    return a.exec();
}

