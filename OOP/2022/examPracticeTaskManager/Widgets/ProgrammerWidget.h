//
// Created by Alex Campean on 10.06.2022.
//
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include "../Observer.h"
#include "../Repository/TaskRepo.h"
#include "../Domain/Programmer.h"

class ProgrammerWidget: public QWidget, public Observer {
Q_OBJECT

private:
    Programmer programmer;
    TaskRepo& tasks;

    /// Layout
    QWidget *mainWidget = new QWidget{};
    QHBoxLayout *mainLayout = new QHBoxLayout{this->mainWidget};

    /// Questions List
    QListWidget *tasksList;

    /// Add/Delete Task
    QPushButton* addTaskButton;
    QPushButton* deleteTaskButton;
    QLineEdit* taskDescription;
    QLabel* errorMessage;

    /// Start Task
    QPushButton* startTaskButton;
    QPushButton* closeTaskButton;

public:
    ProgrammerWidget(Programmer &programmer, TaskRepo &tasks, QWidget *parent = Q_NULLPTR);
    ~ProgrammerWidget(){};

signals:
    void updateListSignal();
    void addTaskSignal(const std::string &description);
    void deleteTaskSignal(int id);
    void startTaskSignal(int id);
    void closeTaskSignal(int id);

public slots:
    void initUI();
    void mapSignalsToSlots();
    int getSelectedIndex(QListWidget *givenList);
    int getSelectedId();

    void update() override;
    void updateList();

    void addTask(const std::string &description);
    void deleteTask(int id);

    void startTask(int id);
    void closeTask(int id);
};
