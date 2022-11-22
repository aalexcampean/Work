//
// Created by Alex Campean on 27.05.2022.
//

#include "GUI.h"
#include <QApplication>

GUI::GUI(Service *inputService, QWidget *parent) : QWidget(parent) {
    this->service = inputService;
    mapSignalsToSlots();
    setLayout(this->mainLayout);
    mainMenu();
}

GUI::~GUI() {
}

void GUI::mapSignalsToSlots() {
    QObject::connect(this, &GUI::dataBaseUpdate, this, &GUI::updateList);
}

void GUI::mainMenu() {
    //General layout of the window
    QWidget *windowWidget = new QWidget{};
    QVBoxLayout *windowLayout = new QVBoxLayout{windowWidget};

    // Setting the top vertical layout
    QWidget *topWidget = new QWidget{};
    QHBoxLayout *topLayout = new QHBoxLayout{topWidget};
    std::pair<QWidget *, QLayout *> parentWidgetAndLayout{topWidget, topLayout};

    this->shoppingList = new QListWidget{};
    // Setting the selection model such that multiple rows cannot be selected at once
    this->shoppingList->setSelectionMode(QAbstractItemView::SingleSelection);
    // Populating the Table
    emit dataBaseUpdate();

    topLayout->addWidget(this->shoppingList);
    windowLayout->addWidget(topWidget);
    this->mainLayout->addWidget(windowWidget);
}

void GUI::updateList() {
    this->shoppingVector = this->service->getShoppingList();

    if (this->shoppingList->count() > 0)
        this->shoppingList->clear();

    // Populating the list with data from the local vector of dogs
    for (ShoppingItem &item: this->shoppingVector) {
        QListWidgetItem *movie = new QListWidgetItem{QString::fromStdString(item.toString())};
        movie->setData(Qt::UserRole, QString::fromStdString(item.toString()));
        this->shoppingList->addItem(movie);
    }

    // Setting the selection on the first item in the list
    if (!this->shoppingVector.empty())
        this->shoppingList->setCurrentRow(0);
}

