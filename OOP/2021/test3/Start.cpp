#include <QtWidgets/QApplication>
#include "Gui/Gui.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    Gui myGui;
    myGui.resize(600, 600);
    myGui.show();

    return a.exec();
}

