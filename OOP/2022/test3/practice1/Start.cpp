//
// Created by Alex Campean on 27.05.2022.
//

#include <QApplication>
#include "GUI.h"

int main(int argc, char *argv[]) {
    /// Service Assemble
    FileRepository repository("Database.txt");
    Service service(&repository);

    /// GUI Assemble
    QApplication a(argc, argv);
    GUI gui(&service);
    gui.resize(600, 600);
    gui.show();

    return a.exec();
}