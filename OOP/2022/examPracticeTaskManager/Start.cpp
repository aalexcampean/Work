//
// Created by Alex Campean on 10.06.2022.
//

#include <QApplication>
#include "Repository/TaskRepo.h"
#include "Repository/ProgrammerRepo.h"
#include "Widgets/ProgrammerWidget.h"

int Task::current_id;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TaskRepo taskRepo{};
    ProgrammerRepo programmersRepo{};

    std::vector<ProgrammerWidget*> programmers;
    for (auto& programmer : programmersRepo.getAll()) {
        programmers.push_back(new ProgrammerWidget(programmer, taskRepo));
    }

    for (auto& programmer : programmers) {
        programmer->show();
    }

    return a.exec();
}