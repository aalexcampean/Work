//
// Created by Alex Campean on 11.06.2022.
//

#include "WriterWidget.h"
#include "../Exception/CustomException.h"

WriterWidget::WriterWidget(Writer &writer, IdeaRepo &ideaRepo,
                           QWidget *parent) : writer(writer), ideaRepo(ideaRepo),
                                              QWidget(parent) {
    mapSignalsToSlots();
    setLayout(this->mainLayout);
    setWindowTitle(QString::fromStdString(this->writer.getName()));
    initUI();
}

void WriterWidget::mapSignalsToSlots() {
    QObject::connect(this, SIGNAL(updateIdeasViewSignal(std::vector<Idea>)), this,
                     SLOT(updateIdeasView(std::vector<Idea>)));
    QObject::connect(this, SIGNAL(addIdeaSignal(const std::string &, int)), this,
                     SLOT(addIdea(const std::string &, int)));
    QObject::connect(this, SIGNAL(reviseIdeaSignal()), this,
                     SLOT(reviseIdea()));
    QObject::connect(this, SIGNAL(savePlotSignal()), this,
                     SLOT(savePlot()));
}

void WriterWidget::initUI() {
    QWidget * ideasListWidget = new QWidget{};
    QHBoxLayout * ideasListLayout = new QHBoxLayout{ideasListWidget};

    ideasTableView = new QTableView();
    ideasTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ideasTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ideasTableModel = new IdeasTableModel(ideas = ideaRepo.sortAllByAct());
    ideasTableView->setModel(ideasTableModel);

    ideasListLayout->addWidget(ideasTableView);

    if (writer.getExpertise() == "Senior") {
        reviseIdeaButton = new QPushButton{"Revise Idea"};
        reviseIdeaButton->setMinimumHeight(35);
        QObject::connect(reviseIdeaButton, &QPushButton::clicked, this, [=]() {
            emit reviseIdeaSignal();
        });
        ideasListLayout->addWidget(reviseIdeaButton);
    }


    QWidget * addIdeaWidget = new QWidget{};
    QHBoxLayout * addIdeaLayout = new QHBoxLayout{addIdeaWidget};

    ideaDescription = new QLineEdit{};
    ideaDescription->setMinimumHeight(35);
    ideaDescription->setPlaceholderText("Description: ");

    ideaAct = new QLineEdit{};
    ideaAct->setMinimumHeight(35);
    ideaAct->setPlaceholderText("Act: ");

    addIdeaLayout->addWidget(ideaDescription);
    addIdeaLayout->addWidget(ideaAct);

    addIdeaButton = new QPushButton{"Add Idea"};
    addIdeaButton->setMinimumHeight(35);
    QObject::connect(addIdeaButton, &QPushButton::clicked, this, [=]() {
        emit this->addIdeaSignal(ideaDescription->text().toStdString(), std::stoi(ideaAct->text().toStdString()));
    });

    savePlotButton = new QPushButton{"Save Plot"};
    savePlotButton->setMinimumHeight(35);
    QObject::connect(savePlotButton, &QPushButton::clicked, this, [=]() {
        emit savePlotSignal();
    });

    mainLayout->addWidget(ideasListWidget);
    mainLayout->addWidget(addIdeaWidget);
    mainLayout->addWidget(addIdeaButton);
    mainLayout->addWidget(savePlotButton);
}

void WriterWidget::updateIdeasView(std::vector<Idea> inputVector) {
    delete ideasTableModel;
    this->ideasTableModel = new IdeasTableModel(inputVector);
    this->ideasTableView->setModel(this->ideasTableModel);
}

void WriterWidget::addIdea(const std::string &description, int act) {
    bool flag = true;
    try {
        Idea newIdea{description, writer.getName(), act};
        ideaRepo.addIdea(newIdea);
    }
    catch (const CustomException &e) {
        errorMessage->setText(QString::fromStdString(e.what()));
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag) {
        ideaDescription->setText("");
        ideaAct->setText("");
        emit updateIdeasViewSignal(ideaRepo.sortAllByAct());
    }
}

void WriterWidget::reviseIdea() {
    int idx = this->ideasTableView->selectionModel()->currentIndex().row();
    int selectedId = ideas[idx].getId();
    ideaRepo.reviseIdea(selectedId);
    emit updateIdeasViewSignal(ideaRepo.sortAllByAct());
}

void WriterWidget::savePlot() {
    ideaRepo.savePlot();
}
