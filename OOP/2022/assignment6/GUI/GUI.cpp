//
// Created by Alex Campean on 18.05.2022.
//

#include <QTableWidgetItem>
#include <QApplication>
#include <QFormLayout>
#include "GUI.h"
#include "../Exception/CustomException.h"

GUI::GUI(AdminService *aService, UserService *uService, OperationExecution *opExecution, QWidget *parent) : QWidget(parent) {
    this->adminService = aService;
    this->userService = uService;
    this->op = opExecution;

    mapSignalsToSlots();
    setLayout(this->mainLayout);
    landingMenu();
}

GUI::~GUI() {
}

void GUI::mapSignalsToSlots() {
    QObject::connect(this, &GUI::dataBaseUpdate, this, &GUI::updateList);

    QObject::connect(this, SIGNAL(addDogSignal(std::vector<std::string>, QLabel * )), this,
                     SLOT(addDog(std::vector<std::string>, QLabel * )));
    QObject::connect(this, SIGNAL(updateDogSignal(std::vector<std::string>, QLabel * )), this,
                     SLOT(updateDog(std::vector<std::string>, QLabel * )));
    QObject::connect(this, SIGNAL(deleteDogSignal(const std::string&)), this, SLOT(deleteDog(const std::string&)));

    QObject::connect(this, SIGNAL(undoSignal()),this, SLOT(undo()));
    QObject::connect(this, SIGNAL(redoSignal()),this, SLOT(redo()));

    QObject::connect(shortcutUndo, &QShortcut::activated, [=]() {this->undo();});
    QObject::connect(shortcutRedo, &QShortcut::activated, [=]() {this->redo();});


    QObject::connect(this, SIGNAL(availableDogsUpdateSignal(std::vector<Dog>)), this, SLOT(populateAvailableList(std::vector<Dog>)));
    QObject::connect(this, SIGNAL(adoptionListUpdateSignal(std::vector<Dog>)), this, SLOT(populateAdoptionList(std::vector<Dog>)));

    QObject::connect(this, SIGNAL(filterListSignal(const std::string&)), this,
                     SLOT(filterListByBreed(const std::string&)));
    QObject::connect(this, SIGNAL(adoptDogSignal()), this, SLOT(adoptDog()));
    QObject::connect(this, SIGNAL(dropAdoptionSignal()), this, SLOT(dropAdoption()));
}

/// Start Application & Menus

void GUI::clearLandingMenu(QWidget *landingMenuWidget) {
    delete this->adminButton;
    delete this->userButton;
    delete this->applicationCloseButton;
    delete landingMenuWidget;
}

void GUI::landingMenu() {
    QWidget *optionsWidget = new QWidget{};
    QHBoxLayout *options_layout = new QHBoxLayout{optionsWidget};


    this->adminButton = new QPushButton{"Admin"};
    this->adminButton->setMinimumHeight(35);
    QObject::connect(adminButton, &QPushButton::clicked, this, &GUI::adminMenu);
    QObject::connect(adminButton, &QPushButton::clicked, this, [=]() {
        clearLandingMenu(optionsWidget);
    });


    this->userButton = new QPushButton{"User"};
    this->userButton->setMinimumHeight(35);
    QObject::connect(userButton, &QPushButton::clicked, this, &GUI::userMenuOptions);
    QObject::connect(userButton, &QPushButton::clicked, this, [=]() {
        clearLandingMenu(optionsWidget);
    });


    this->applicationCloseButton = new QPushButton{"Close"};
    this->applicationCloseButton->setMinimumHeight(35);
    QObject::connect(applicationCloseButton, &QPushButton::clicked, this, &QApplication::quit);
    QObject::connect(applicationCloseButton, &QPushButton::clicked, this, [=]() {
        clearLandingMenu(optionsWidget);
    });


    options_layout->addWidget(this->adminButton);
    options_layout->addWidget(this->userButton);
    options_layout->addWidget(this->applicationCloseButton);

    this->mainLayout->addWidget(optionsWidget);
}

void GUI::adminMenu() {
    //General layout of the window
    QWidget *windowWidget = new QWidget{};
    QVBoxLayout *windowLayout = new QVBoxLayout{windowWidget};

    // Setting the top vertical layout
    QWidget *topWidget = new QWidget{};
    QHBoxLayout *topLayout = new QHBoxLayout{topWidget};
    std::pair<QWidget *, QLayout *> parentWidgetAndLayout{topWidget, topLayout};

    this->dogsList = new QListWidget{};
    // Setting the selection model such that multiple rows cannot be selected at once
    this->dogsList->setSelectionMode(QAbstractItemView::SingleSelection);
    // Populating the Table
    emit dataBaseUpdate();

    topLayout->addWidget(this->dogsList);
    windowLayout->addWidget(topWidget);

    // Setting the bottom grid layout
    QWidget *bottomWidget = new QWidget{};
    QGridLayout *bottomLayout = new QGridLayout{bottomWidget};

    this->adminAddButton = new QPushButton{"Add movie"};
    this->adminAddButton->setMinimumHeight(35);
    QObject::connect(this->adminAddButton, &QPushButton::clicked, this, &GUI::disableAdminMenuButtons);
    QObject::connect(this->adminAddButton, &QPushButton::clicked, this, [=]() {
        this->addFunctionalityUI(parentWidgetAndLayout);
    });


    this->adminUpdateButton = new QPushButton{"Update movie"};
    this->adminUpdateButton->setMinimumHeight(35);
    QObject::connect(this->adminUpdateButton, &QPushButton::clicked, this, &GUI::disableAdminMenuButtons);
    QObject::connect(this->adminUpdateButton, &QPushButton::clicked, this, [=]() {
        this->updateFunctionalityUI(parentWidgetAndLayout);
    });


    this->adminDeleteButton = new QPushButton{"Delete movie"};
    this->adminDeleteButton->setMinimumHeight(35);
    QObject::connect(this->adminDeleteButton, &QPushButton::clicked, this, &GUI::deleteFunctionalityUI);


    this->adminCloseButton = new QPushButton{"Close"};
    this->adminCloseButton->setMinimumHeight(35);
    QObject::connect(this->adminCloseButton, &QPushButton::clicked, this, [=]() {
        delete windowWidget;
        this->landingMenu();
    });

    this->adminUndo = new QPushButton{ "Undo" };
    this->adminUndo->setMinimumHeight(35);
    QObject::connect(adminUndo, &QPushButton::clicked, this, [=]() {
        emit this->undoSignal();
    });

    this->adminRedo = new QPushButton{ "Redo" };
    this->adminRedo->setMinimumHeight(35);
    QObject::connect(adminRedo, &QPushButton::clicked, this, [=]() {
        emit this->redoSignal();
    });

    bottomLayout->addWidget(this->adminUndo, 0, 0);
    bottomLayout->addWidget(this->adminRedo, 0, 1);
    bottomLayout->addWidget(this->adminAddButton, 1, 0);
    bottomLayout->addWidget(this->adminUpdateButton, 1, 1);
    bottomLayout->addWidget(this->adminDeleteButton, 2, 0);
    bottomLayout->addWidget(this->adminCloseButton, 2, 1);
    windowLayout->addWidget(bottomWidget);
    this->mainLayout->addWidget(windowWidget);
}

void GUI::disableAdminMenuButtons() {
    this->adminAddButton->setDisabled(true);
    this->adminDeleteButton->setDisabled(true);
    this->adminUpdateButton->setDisabled(true);
}

void GUI::userMenuOptions() {
    QWidget *windowWidget = new QWidget{};
    QHBoxLayout *windowLayout = new QHBoxLayout{windowWidget};

    this->userHtmlButton = new QPushButton{"HTML"};
    this->userHtmlButton->setMinimumHeight(35);
    this->userCsvButton = new QPushButton{"CSV"};
    this->userCsvButton->setMinimumHeight(35);

    windowLayout->addWidget(this->userHtmlButton);
    windowLayout->addWidget(this->userCsvButton);
    this->mainLayout->addWidget(windowWidget);

    QObject::connect(this->userHtmlButton, &QPushButton::clicked, this, [=]() {
        delete this->userHtmlButton;
        delete this->userCsvButton;
        delete windowLayout;
        delete windowWidget;
        this->userService->setRepositoryType("html");
        this->userMenu();
    });

    QObject::connect(this->userCsvButton, &QPushButton::clicked, this, [=]() {
        delete this->userHtmlButton;
        delete this->userCsvButton;
        delete windowLayout;
        delete windowWidget;
        this->userService->setRepositoryType("csv");
        this->userMenu();
    });
}

void GUI::userMenu() {
    //General layout of the window
    QWidget *windowWidget = new QWidget{};
    QVBoxLayout *windowLayout = new QVBoxLayout{windowWidget};

    // the top layout - a vertical one
    QWidget *topWidget = new QWidget{};
    QHBoxLayout *topLayout = new QHBoxLayout{topWidget};

    std::pair<QWidget *, QLayout *> topWidgetLayout{topWidget, topLayout};

    // the bottom layout - a grid one
    QWidget *bottomWidget = new QWidget{};
    QGridLayout *bottomLayout = new QGridLayout{bottomWidget};

    this->userAvailableView = new QTableView();
    this->userAvailableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->userAvailableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->userAvailableModel = new DogsTableModel(this->userAvailableVector = this->adminService->getRepository());
    this->userAvailableView->setModel(this->userAvailableModel);


    this->userFilterInput = new QLineEdit{};
    this->userFilterInput->setMinimumHeight(35);
    this->userFilterInput->setPlaceholderText("Breed: ");

    this->userFilterButton = new QPushButton{"Filter"};
    this->userFilterButton->setMinimumHeight(35);
    QObject::connect(this->userFilterButton, &QPushButton::clicked, this, [=]() {
        std::string searchBreed = this->userFilterInput->text().toStdString();
        emit filterListSignal(searchBreed);
    });

    this->userAdoptButton = new QPushButton{"Adopt"};
    this->userAdoptButton->setMinimumHeight(35);
    QObject::connect(this->userAdoptButton, &QPushButton::clicked, this, [=]() {
        this->userAdoptButton->setDisabled(true);
        this->manageAdoptionList(topWidgetLayout);
    });

    this->userCloseButton = new QPushButton{"Close"};
    this->userCloseButton->setMinimumHeight(35);
    QObject::connect(this->userCloseButton, &QPushButton::clicked, this, [=]() {
        delete windowWidget;
        this->landingMenu();
    });

    topLayout->addWidget(this->userAvailableView);
    bottomLayout->addWidget(userFilterInput, 0, 0);
    bottomLayout->addWidget(this->userFilterButton, 0, 1);
    bottomLayout->addWidget(this->userAdoptButton, 1, 0);
    bottomLayout->addWidget(this->userCloseButton, 1, 1);

    windowLayout->addWidget(topWidget);
    windowLayout->addWidget(bottomWidget);
    this->mainLayout->addWidget(windowWidget);
}

void GUI::manageAdoptionList(std::pair<QWidget *, QLayout *> receivedWidgetLayout) {
    QWidget *verticalButtonWidget = new QWidget{};
    QVBoxLayout *verticalButtonLayout = new QVBoxLayout{verticalButtonWidget};

    this->userAddButton = new QPushButton{"Add"};
    this->userAddButton->setMinimumHeight(10);
    this->userDeleteButton = new QPushButton{"Delete"};
    this->userDeleteButton->setMinimumHeight(10);
    this->userDoneButton = new QPushButton{"Done"};
    this->userDoneButton->setMinimumHeight(10);

    verticalButtonLayout->addWidget(this->userAddButton);
    verticalButtonLayout->addWidget(this->userDeleteButton);
    verticalButtonLayout->addWidget(this->userDoneButton);

    this->userAdoptionsView = new QTableView();
    this->userAdoptionsView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->userAdoptionsView->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->userAdoptionsModel = new DogsTableModel(this->userAdoptionVector = {});
    this->userAdoptionsView->setModel(this->userAdoptionsModel);

    QObject::connect(this->userAddButton, &QPushButton::clicked, this, [=]() {
        emit this->adoptDogSignal();
    });
    QObject::connect(this->userDeleteButton, &QPushButton::clicked, this, [=]() {
        emit this->dropAdoptionSignal();

    });
    QObject::connect(this->userDoneButton, &QPushButton::clicked, this, [=]() {
        delete this->userAddButton;
        delete this->userDeleteButton;
        delete this->userDoneButton;

        delete this->userAdoptionList;
        delete verticalButtonLayout;
        delete verticalButtonWidget;
        this->userService->openFile();
    });

    receivedWidgetLayout.second->addWidget(verticalButtonWidget);
    receivedWidgetLayout.second->addWidget(this->userAdoptionsView);
}

void GUI::filterListByBreed(const std::string &inputBreed) {
    std::vector<Dog> filteredDogs;
    if (inputBreed.empty()){
        std::for_each(this->userAvailableVector.begin(), this->userAvailableVector.end(), [&filteredDogs](auto &it){filteredDogs.push_back(it);});
    }
    else {
        std::for_each(this->userAvailableVector.begin(), this->userAvailableVector.end(), [&filteredDogs, inputBreed](auto &it){if (it.getBreed() == inputBreed) filteredDogs.push_back(it);});
    }

    emit this->availableDogsUpdateSignal(filteredDogs);
}

void GUI::adoptDog() {
    int idx = this->userAvailableView->selectionModel()->currentIndex().row();
    Dog *addDog = &this->userAvailableVector[idx];

    auto it = std::find(this->userAvailableVector.begin(), this->userAvailableVector.end(), addDog->getImage());
    if (it == this->userAvailableVector.end()) {
        return;
    }

    this->userService->addElementService(addDog->getBreed(), addDog->getName(), std::to_string(addDog->getAge()),
                                         addDog->getImage());

    this->userAdoptionVector.push_back(*addDog);
    this->userAvailableVector.erase(it);

    emit availableDogsUpdateSignal(this->userAvailableVector);
    emit adoptionListUpdateSignal(this->userAdoptionVector);
//    std::string url = std::string("open ").append(addDog->getTrailer());
//    system(url.c_str());
}

void GUI::dropAdoption() {
    int idx = this->userAdoptionsView->selectionModel()->currentIndex().row();
    if (idx != -1) {
        Dog *deleteDog = &this->userAdoptionVector[idx];
        auto it = std::find(this->userAdoptionVector.begin(), this->userAdoptionVector.end(),
                            deleteDog->getImage());
        if (it == this->userAdoptionVector.end()) {
            return;
        }

        this->userService->deleteElementService(this->userAdoptionVector[idx].getImage());

        this->userAvailableVector.push_back(this->userAdoptionVector[idx]);
        this->userAdoptionVector.erase(it);

        emit availableDogsUpdateSignal(this->userAvailableVector);
        emit adoptionListUpdateSignal(this->userAdoptionVector);
    }
}

void GUI::populateList(QListWidget *givenList, const std::vector<Dog> &inputVector) {
    if (givenList->count() > 0)
        givenList->clear();

    for (const Dog &it: inputVector) {
        QListWidgetItem *movie = new QListWidgetItem{QString::fromStdString(it.toString())};
        movie->setData(Qt::UserRole, QString::fromStdString(it.toString()));
        givenList->addItem(movie);
    }

    // set the selection on the first item in the list
    if (!inputVector.empty())
        givenList->setCurrentRow(0);
}

void GUI::populateAdoptionList(std::vector<Dog> inputVector) {
    delete this->userAdoptionsModel;
    this->userAdoptionsModel = new DogsTableModel(inputVector);
    this->userAdoptionsView->setModel(this->userAdoptionsModel);
}

void GUI::populateAvailableList(std::vector<Dog> inputVector) {
    delete this->userAvailableModel;
    this->userAvailableModel = new DogsTableModel(inputVector);
    this->userAvailableView->setModel(this->userAvailableModel);
}

void GUI::updateList() {
    this->dogsVector = this->adminService->getRepository();

    if (this->dogsList->count() > 0)
        this->dogsList->clear();

    // Populating the list with data from the local vector of dogs
    for (Dog &dog: this->dogsVector) {
        QListWidgetItem *movie = new QListWidgetItem{QString::fromStdString(dog.toString())};
        movie->setData(Qt::UserRole, QString::fromStdString(dog.toString()));
        this->dogsList->addItem(movie);
    }

    // Setting the selection on the first item in the list
    if (!this->dogsVector.empty())
        this->dogsList->setCurrentRow(0);
}

/// Retrieving the index of the selected row
int GUI::getSelectedIndex(QListWidget *givenList) {
    if (givenList->count() == 0)
        return -1;

    // Getting selected index
    QModelIndexList index = givenList->selectionModel()->selectedIndexes();

    // In case the lost is empty, clear the input fields
    if (index.empty()) {
        this->breedInput->clear();
        this->nameInput->clear();
        this->ageInput->clear();
        this->imageInput->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

/// Creating input fields for Add / Update operations
/// These fields will be displayed on the right of the parent widget
std::pair<QWidget *, QFormLayout *> GUI::createFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout) {
    // the fields for add/update - on the right
    QWidget *movieFieldsWidget = new QWidget{};
    QFormLayout *movieFieldsLayout = new QFormLayout{movieFieldsWidget};

    this->breedInput = new QLineEdit{};
    this->breedInput->setMinimumHeight(35);
    this->breedInput->setPlaceholderText("Breed: ");

    this->nameInput = new QLineEdit{};
    this->nameInput->setMinimumHeight(35);
    this->nameInput->setPlaceholderText("Name: ");

    this->ageInput = new QLineEdit{};
    this->ageInput->setMinimumHeight(35);
    this->ageInput->setPlaceholderText("Age: ");

    this->imageInput = new QLineEdit{};
    this->imageInput->setMinimumHeight(35);
    this->imageInput->setPlaceholderText("Image: ");

    movieFieldsLayout->addRow(this->breedInput);
    movieFieldsLayout->addRow(this->nameInput);
    movieFieldsLayout->addRow(this->ageInput);
    movieFieldsLayout->addRow(this->imageInput);
    receivedWidgetLayout.second->addWidget(movieFieldsWidget);

    std::pair<QWidget *, QFormLayout *> returnValue{movieFieldsWidget, movieFieldsLayout};
    return returnValue;
}

/// Deleting the input fields from the parent Widget
void GUI::deleteFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout) {
    delete this->breedInput;
    delete this->nameInput;
    delete this->ageInput;
    delete this->imageInput;

    delete receivedWidgetLayout.second;
    delete receivedWidgetLayout.first;
}

/// Retrieving the the information found in ther input fields
std::vector<std::string> GUI::getFieldsContent() {
    std::vector<std::string> receivedFields;
    QString breed = this->breedInput->text();
    QString name = this->nameInput->text();
    QString age = this->ageInput->text();
    QString imageLink = this->imageInput->text();

    receivedFields.push_back(breed.toStdString());
    receivedFields.push_back(name.toStdString());
    receivedFields.push_back(age.toStdString());
    receivedFields.push_back(imageLink.toStdString());

    return receivedFields;
}

void GUI::populateFields() {
    int idx = this->getSelectedIndex(this->dogsList);
    if (idx == -1)
        return;

    if (idx >= this->dogsVector.size())
        return;

    Dog dog = this->dogsVector[idx];

    this->breedInput->setText(QString::fromStdString(dog.getBreed()));
    this->nameInput->setText(QString::fromStdString(dog.getName()));
    this->ageInput->setText(QString::fromStdString(std::to_string(dog.getAge())));
    this->imageInput->setText(QString::fromStdString(dog.getImage()));
    this->imageInput->setReadOnly(true);
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
        emit this->addDogSignal(receivedFields, errorMessage);
    });

    QObject::connect(close, &QPushButton::clicked, this, [=]() {
        delete done;
        delete close;
        delete errorMessage;
        delete spacing1;
        delete spacing2;

        this->deleteFields(fieldsWidgetLayout);

        this->adminAddButton->setDisabled(false);
        this->adminDeleteButton->setDisabled(false);
        this->adminUpdateButton->setDisabled(false);
    });
}

void GUI::addDog(std::vector<std::string> receivedFields, QLabel *errorMessage) {
    bool flag = true;
    try {
        Dog newDog(receivedFields[0], receivedFields[1], std::stoi(receivedFields[2]), receivedFields[3]);
        AddOperation* newOperation = new AddOperation(newDog, this->adminService->getRepoState());
        this->op->saveOperation(newOperation);
    }
    catch (const CustomException& e) {
        errorMessage->setText(QString::fromStdString(e.what()));
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag)
            emit this->dataBaseUpdate();
}


void GUI::updateFunctionalityUI(std::pair<QWidget *, QLayout *> parentWidgetAndLayout) {
    std::pair<QWidget *, QFormLayout *> fieldsWidgetLayout = this->createFields(parentWidgetAndLayout);

    QObject::connect(this->dogsList, &QListWidget::itemSelectionChanged, this, &GUI::populateFields);

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
        emit this->updateDogSignal(receivedFields, errorMessage);
    });

    QObject::connect(close, &QPushButton::clicked, this, [=]() {
        delete done;
        delete close;
        delete errorMessage;
        delete spacing1;
        delete spacing2;

        this->deleteFields(fieldsWidgetLayout);

        this->adminAddButton->setDisabled(false);
        this->adminDeleteButton->setDisabled(false);
        this->adminUpdateButton->setDisabled(false);

        QObject::disconnect(this->dogsList, &QListWidget::itemSelectionChanged, this, &GUI::populateFields);
    });
}

void GUI::updateDog(std::vector<std::string> receivedFields, QLabel *errorMessage) {
    bool flag = true;
    try {
        Dog newDog(receivedFields[0], receivedFields[1], std::stoi(receivedFields[2]), receivedFields[3]);
        Dog oldDog = this->adminService->getDogByImage(receivedFields[3]);
        UpdateOperation* newOperation = new UpdateOperation(oldDog, newDog, this->adminService->getRepoState());
        this->op->saveOperation(newOperation);
    }
    catch (const CustomException& e) {
        errorMessage->setText(e.what());
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag)
            emit this->dataBaseUpdate();
}


void GUI::deleteFunctionalityUI() {
    int idx = this->getSelectedIndex(this->dogsList);
    if (idx == -1)
        return;

    if (idx >= this->dogsVector.size())
        return;
    std::string receivedTitle = this->dogsVector[idx].getImage();
    emit this->deleteDogSignal(receivedTitle);
}

void GUI::deleteDog(const std::string &receivedImageLink) {
    try {
        Dog oldDog = this->adminService->getDogByImage(receivedImageLink);
        DeleteOperation* newOperation = new DeleteOperation(oldDog, this->adminService->getRepoState());
        this->op->saveOperation(newOperation);
    }
    catch (const CustomException& e) {
    }
    emit this->dataBaseUpdate();
}

void GUI::undo() {
    this->op->undo();
    emit this->dataBaseUpdate();
}

void GUI::redo() {
    this->op->redo();
    emit this->dataBaseUpdate();
}
