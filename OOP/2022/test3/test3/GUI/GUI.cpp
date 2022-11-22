//
// Created by Alex Campean on 27.05.2022.
//

#include "GUI.h"
#include "../Exception/CustomException.h"


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
    QObject::connect(this, SIGNAL(addEquationSignal(std::vector<std::string>, QLabel * )), this,
                     SLOT(addEquation(std::vector<std::string>, QLabel * )));
}

void GUI::disableButtons() {
    this->addButton->setDisabled(true);
    this->computeButton->setDisabled(true);
}

void GUI::mainMenu() {
    QWidget *windowWidget = new QWidget{};
    QVBoxLayout *windowLayout = new QVBoxLayout{windowWidget};

    QWidget *topWidget = new QWidget{};
    QHBoxLayout *topLayout = new QHBoxLayout{topWidget};
    std::pair<QWidget *, QLayout *> parentWidgetAndLayout{topWidget, topLayout};

    this->equationList = new QListWidget{};
    this->equationList->setSelectionMode(QAbstractItemView::SingleSelection);
    emit dataBaseUpdate();

    topLayout->addWidget(this->equationList);
    windowLayout->addWidget(topWidget);

    QWidget *bottomWidget = new QWidget{};
    QGridLayout *bottomLayout = new QGridLayout{bottomWidget};

    this->addButton = new QPushButton{"Add Equation"};
    this->addButton->setMinimumHeight(35);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::disableButtons);
    QObject::connect(this->addButton, &QPushButton::clicked, this, [=]() {
        this->addFunctionalityUI(parentWidgetAndLayout);
    });

    this->computeButton = new QPushButton{"Compute equation"};
    this->computeButton->setMinimumHeight(35);
    QObject::connect(this->computeButton, &QPushButton::clicked, this, &GUI::disableButtons);
    QObject::connect(this->computeButton, &QPushButton::clicked, this, [=]() {
        // TODO: add function call
    });

    bottomLayout->addWidget(this->addButton, 0, 0);
    bottomLayout->addWidget(this->computeButton, 0, 1);
    windowLayout->addWidget(bottomWidget);

    this->mainLayout->addWidget(windowWidget);
}

void GUI::updateList() {
    this->equationVector = this->service->getEquationList();

    if (this->equationList->count() > 0)
        this->equationList->clear();

    for (Equation &equation: this->equationVector) {
        QListWidgetItem *movie = new QListWidgetItem{QString::fromStdString(equation.toString())};
        movie->setData(Qt::UserRole, QString::fromStdString(equation.toString()));
//        movie->setBackground(Qt::green);
        this->equationList->addItem(movie);
    }

    if (!this->equationVector.empty())
        this->equationList->setCurrentRow(0);
}

int GUI::getSelectedIndex(QListWidget *givenList) {
    if (givenList->count() == 0)
        return -1;

    QModelIndexList index = givenList->selectionModel()->selectedIndexes();

    if (index.empty()) {
        this->coefficientAInput->clear();
        this->coefficientBInput->clear();
        this->coefficientCInput->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

void GUI::addFunctionalityUI(std::pair<QWidget *, QLayout *> parentWidgetAndLayout) {
    std::pair<QWidget *, QFormLayout *> fieldsWidgetLayout = this->createFields(parentWidgetAndLayout);

    QPushButton *done = new QPushButton{"Done"};
    done->setMinimumHeight(35);
    QPushButton *close = new QPushButton{"Close"};
    close->setMinimumHeight(35);
    QLabel *errorMessage = new QLabel{};
    errorMessage->setMinimumHeight(35);
    QLabel *spacing1 = new QLabel{""};
    spacing1->setMinimumHeight(35);
    QLabel *spacing2 = new QLabel{""};
    spacing2->setMinimumHeight(35);
    fieldsWidgetLayout.second->addRow(spacing1);
    fieldsWidgetLayout.second->addRow(done);
    fieldsWidgetLayout.second->addRow(close);
    fieldsWidgetLayout.second->addRow(spacing2);
    fieldsWidgetLayout.second->addRow(errorMessage);


    QObject::connect(done, &QPushButton::clicked, this, [=]() {
        errorMessage->setText("");
        std::vector<std::string> receivedFields = this->getFieldsContent();
        emit this->addEquationSignal(receivedFields, errorMessage);
    });

    QObject::connect(close, &QPushButton::clicked, this, [=]() {
        delete done;
        delete close;
        delete errorMessage;
        delete spacing1;
        delete spacing2;

        this->deleteFields(fieldsWidgetLayout);

        this->addButton->setDisabled(false);
        this->computeButton->setDisabled(false);
    });
}

void GUI::addEquation(std::vector<std::string> receivedFields, QLabel *errorMessage) {
    bool flag = true;
    try {
        this->service->addElementService(receivedFields[0], receivedFields[1], receivedFields[2]);
    }
    catch (const CustomException &e) {
        errorMessage->setText(QString::fromStdString(e.what()));
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag)
            emit this->dataBaseUpdate();
}

std::pair<QWidget *, QFormLayout *> GUI::createFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout) {
    QWidget *movieFieldsWidget = new QWidget{};
    QFormLayout *movieFieldsLayout = new QFormLayout{movieFieldsWidget};

    this->coefficientAInput = new QLineEdit{};
    this->coefficientAInput->setMinimumHeight(35);
    this->coefficientAInput->setPlaceholderText("Coefficient A: ");

    this->coefficientBInput = new QLineEdit{};
    this->coefficientBInput->setMinimumHeight(35);
    this->coefficientBInput->setPlaceholderText("Coefficient B: ");

    this->coefficientCInput = new QLineEdit{};
    this->coefficientCInput->setMinimumHeight(35);
    this->coefficientCInput->setPlaceholderText("Coefficient C: ");

    movieFieldsLayout->addRow(this->coefficientAInput);
    movieFieldsLayout->addRow(this->coefficientBInput);
    movieFieldsLayout->addRow(this->coefficientCInput);

    receivedWidgetLayout.second->addWidget(movieFieldsWidget);

    std::pair<QWidget *, QFormLayout *> returnValue{movieFieldsWidget, movieFieldsLayout};
    return returnValue;
}

void GUI::deleteFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout) {
    delete this->coefficientAInput;
    delete this->coefficientBInput;
    delete this->coefficientCInput;

    delete receivedWidgetLayout.second;
    delete receivedWidgetLayout.first;
}

std::vector<std::string> GUI::getFieldsContent() {
    std::vector<std::string> receivedFields;
    QString a = this->coefficientAInput->text();
    QString b = this->coefficientBInput->text();
    QString c = this->coefficientCInput->text();

    receivedFields.push_back(a.toStdString());
    receivedFields.push_back(b.toStdString());
    receivedFields.push_back(c.toStdString());

    return receivedFields;
}
