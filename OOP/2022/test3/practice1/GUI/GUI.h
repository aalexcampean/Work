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
    std::vector<ShoppingItem> shoppingVector;
    /// Shopping List
    QListWidget *shoppingList;

    void mapSignalsToSlots();
    void mainMenu();

signals:
    void dataBaseUpdate();

public slots:
    void updateList();
};

