//
// Created by Alex Campean on 27.05.2022.
//
#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QDebug>

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include "Service.h"

class GUI : public QWidget {
Q_OBJECT
public:
    GUI(Service *inputService, QWidget *parent = Q_NULLPTR);

    ~GUI();

private:
    /// Dependencies
    Service *service;

    /// Layout
    QWidget *mainWidget = new QWidget{};
    QVBoxLayout *mainLayout = new QVBoxLayout{this->mainWidget};

    /// Shopping List Vector
    std::vector<Equation> equationVector;
    /// Shopping List
    QListWidget *equationList;

    QPushButton* addButton;
    QPushButton* computeButton;

    QLineEdit* coefficientAInput;
    QLineEdit* coefficientBInput;
    QLineEdit* coefficientCInput;

    void mapSignalsToSlots();
    void mainMenu();

signals:
    void dataBaseUpdate();
    void addEquationSignal(std::vector<std::string>, QLabel*);

public slots:
    void updateList();
    int getSelectedIndex(QListWidget *givenList);
    void disableButtons();
    void addFunctionalityUI(std::pair<QWidget*, QLayout*> parentWidgetAndLayout);
    void addEquation(std::vector<std::string>, QLabel*);

    std::pair<QWidget *, QFormLayout *> createFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout);
    void deleteFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout);
    std::vector<std::string> getFieldsContent();
};
