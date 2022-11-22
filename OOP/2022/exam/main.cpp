//
// Created by Alex Campean on 11.06.2022.
//


#include <QApplication>
#include "Repository/IdeaRepo.h"
#include "Repository/WriterRepo.h"
#include "Widgets/WriterWidget.h"

int Idea::currentId;
int Writer::currentId;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    IdeaRepo ideas{};
    WriterRepo writers{};

    std::vector<WriterWidget *> writersWidgets;
    for (auto &writer: writers.getAll()) {
        writersWidgets.push_back(new WriterWidget(writer, ideas));
    }

    for (auto &writer: writersWidgets) {
        writer->show();
    }

    return a.exec();
}