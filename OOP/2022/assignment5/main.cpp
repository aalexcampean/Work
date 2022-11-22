#include <QApplication>
#include <QPushButton>
#include "GUI/GUI.h"

int main(int argc, char *argv[]) {
    /// Admin Assemble
    TextFileRepository adminRepository("Database.txt", "Database.txt");
    AdminService adminService(&adminRepository);

    /// User Assemble
    TextFileRepository userRepository("AdoptionList.txt", "AdoptionList.txt");
    UserService userService(&userRepository);

    /// GUI Assemble
    QApplication a(argc, argv);
    GUI gui(&adminService, &userService);
    gui.resize(600, 600);
    gui.show();

    return a.exec();
}
