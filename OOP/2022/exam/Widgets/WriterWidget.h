//
// Created by Alex Campean on 11.06.2022.
//
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include "../Repository/IdeaRepo.h"
#include "../Domain/Writer.h"
#include "../TableModel/IdeasTableModel.h"

class WriterWidget : public QWidget{
Q_OBJECT
private:
    Writer writer;
    IdeaRepo& ideaRepo;

    /// Layout
    QWidget *mainWidget = new QWidget{};
    QVBoxLayout *mainLayout = new QVBoxLayout{this->mainWidget};

    /// Ideas List
    std::vector<Idea> ideas;
    IdeasTableModel* ideasTableModel;
    QTableView*  ideasTableView;

    /// Add Idea
    QPushButton* addIdeaButton;
    QLineEdit* ideaDescription;
    QLineEdit* ideaAct;
    QLabel* errorMessage;

    /// Revise Idea
    QPushButton* reviseIdeaButton;

    /// Saving plot
    QPushButton* savePlotButton;

public:
    WriterWidget(Writer &writer, IdeaRepo& ideaRepo, QWidget *parent = Q_NULLPTR);
    ~WriterWidget(){};

signals:
    void addIdeaSignal(const std::string &description, int act);
    void updateIdeasViewSignal(std::vector<Idea> inputVector);
    void reviseIdeaSignal();
    void savePlotSignal();

public slots:
    void initUI();
    void mapSignalsToSlots();
    void addIdea(const std::string &description, int act);
    void updateIdeasView(std::vector<Idea> inputVector);
    void reviseIdea();
    void savePlot();
};


