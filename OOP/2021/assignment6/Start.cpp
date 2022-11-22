#include <QtWidgets/QApplication>
#include "UserInterface/Ui.h"
#include "Gui/gui.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    GUI gui;
    gui.resize(600, 600);
    gui.show();
//    UserInterface ui;
//    ui.start();
    return a.exec();
}

