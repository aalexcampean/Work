//
// Created by Alex Campean on 10.06.2022.
//

#include "ProgrammerWidget.h"
#include "../Exception/CustomException.h"

ProgrammerWidget::ProgrammerWidget(Programmer &programmer, TaskRepo &tasks, QWidget *parent) : programmer(programmer), tasks(tasks), QWidget(parent) {
    mapSignalsToSlots();
    setLayout(this->mainLayout);
    setWindowTitle(QString::fromStdString(this->programmer.getName()));

    initUI();
    tasks.addObserver(this);
}

void ProgrammerWidget::mapSignalsToSlots() {
    QObject::connect(this, &ProgrammerWidget::updateListSignal, this, &ProgrammerWidget::updateList);
    QObject::connect(this, SIGNAL(addTaskSignal(std::string)), this,
                     SLOT(addTask(std::string)));
    QObject::connect(this, SIGNAL(deleteTaskSignal(int)), this,
                     SLOT(deleteTask(int)));
    QObject::connect(this, SIGNAL(startTaskSignal(int)), this,
                     SLOT(startTask(int)));
    QObject::connect(this, SIGNAL(closeTaskSignal(int)), this,
                     SLOT(closeTask(int)));
}

int ProgrammerWidget::getSelectedId() {
    int idx = this->getSelectedIndex(tasksList);
    if (idx == -1)
        return -1;

    if (idx >= tasks.getAll().size())
        return -1;

    std::vector<Task> sortedTasks = tasks.getAll();
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](Task &t1, Task &t2) {
        return t1.getStatus() > t2.getStatus();
    });
    return sortedTasks[idx].getId();
}

void ProgrammerWidget::initUI() {
    QWidget * startEndTaskWidget = new QWidget{};
    QVBoxLayout * startEndTaskLayout = new QVBoxLayout{startEndTaskWidget};

    startTaskButton = new QPushButton{"Start"};
    startTaskButton->setMinimumHeight(35);
    QObject::connect(startTaskButton, &QPushButton::clicked, this, [=]() {
        emit this->startTaskSignal(this->getSelectedId());
    });

    closeTaskButton = new QPushButton{"Done"};
    closeTaskButton->setMinimumHeight(35);
    QObject::connect(closeTaskButton, &QPushButton::clicked, this, [=]() {
        emit this->closeTaskSignal(this->getSelectedId());
    });

    startEndTaskLayout->addWidget(startTaskButton);
    startEndTaskLayout->addWidget(closeTaskButton);

    tasksList = new QListWidget{};
    // Setting the selection model such that multiple rows cannot be selected at once
    tasksList->setSelectionMode(QAbstractItemView::SingleSelection);
    // Populating the Table
    emit updateListSignal();

    QObject::connect(tasksList, &QListWidget::itemSelectionChanged, this, [=]() {
        int idx = this->getSelectedIndex(tasksList);
        if (idx == -1)
            return;

        if (idx >= tasks.getAll().size())
            return;

        std::vector<Task> sortedTasks = tasks.getAll();
        std::sort(sortedTasks.begin(), sortedTasks.end(), [](Task &t1, Task &t2) {
            return t1.getStatus() > t2.getStatus();
        });
        Task task = sortedTasks[idx];

        if (task.getStatus() == "open") {
            startTaskButton->setDisabled(false);
            closeTaskButton->setDisabled(true);
        } else if (task.getStatus() == "in progress" && task.getProgrammerId() == programmer.getId()) {
            closeTaskButton->setDisabled(false);
            startTaskButton->setDisabled(true);
        }
        else {
            startTaskButton->setDisabled(true);
            closeTaskButton->setDisabled(true);
        }
    });

    QWidget * addDeleteTaskWidget = new QWidget{};
    QVBoxLayout * addDeleteTaskLayout = new QVBoxLayout{addDeleteTaskWidget};

    taskDescription = new QLineEdit{};
    taskDescription->setMinimumHeight(35);
    taskDescription->setPlaceholderText("Description: ");

    addTaskButton = new QPushButton{"Add Task"};
    addTaskButton->setMinimumHeight(35);
    QObject::connect(addTaskButton, &QPushButton::clicked, this, [=]() {
        emit this->addTaskSignal(taskDescription->text().toStdString());
    });

    deleteTaskButton = new QPushButton{"Delete Task"};
    deleteTaskButton->setMinimumHeight(35);
    QObject::connect(deleteTaskButton, &QPushButton::clicked, this, [=]() {
        emit this->deleteTaskSignal(this->getSelectedId());
    });

    errorMessage = new QLabel{};
    errorMessage->setMinimumHeight(35);

    addDeleteTaskLayout->addWidget(taskDescription);
    addDeleteTaskLayout->addWidget(addTaskButton);
    addDeleteTaskLayout->addWidget(deleteTaskButton);

    mainLayout->addWidget(startEndTaskWidget);
    mainLayout->addWidget(tasksList);
    mainLayout->addWidget(addDeleteTaskWidget);
}

void ProgrammerWidget::update() {
    emit updateListSignal();
}

void ProgrammerWidget::updateList() {
    if (tasksList->count() > 0)
        tasksList->clear();

    // Sort the list by score
    std::vector<Task> sortedTasks = tasks.getAll();
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](Task &t1, Task &t2) {
        return t1.getStatus() > t2.getStatus();
    });

    // Populating the list with data from the local vector of dogs
    for (Task &task: sortedTasks) {
        QListWidgetItem *questionItem = new QListWidgetItem{QString::fromStdString(task.toString())};
        questionItem->setData(Qt::UserRole, QString::fromStdString(task.toString()));
        tasksList->addItem(questionItem);
    }

    // Setting the selection on the first item in the list
    if (!tasks.getAll().empty())
        tasksList->setCurrentRow(0);
}

int ProgrammerWidget::getSelectedIndex(QListWidget *givenList) {
    if (givenList->count() == 0)
        return -1;

    // Getting selected index
    QModelIndexList index = givenList->selectionModel()->selectedIndexes();

    // In case the lost is empty, clear the input fields
    if (index.empty()) {
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

void ProgrammerWidget::addTask(const std::string &description) {
    bool flag = true;
    try {
        Task newTask{description};
        this->tasks.addTask(newTask);
    }
    catch (const CustomException &e) {
        errorMessage->setText(QString::fromStdString(e.what()));
        errorMessage->setStyleSheet("QLabel { color : red; }");
        flag = false;
    }

    if (flag) {
        taskDescription->setText("");
    }
}

void ProgrammerWidget::deleteTask(int id) {
    try {
        this->tasks.deleteTask(id);
    }
    catch (const CustomException &e) {
        errorMessage->setText(QString::fromStdString(e.what()));
        errorMessage->setStyleSheet("QLabel { color : red; }");
    }
}

void ProgrammerWidget::startTask(int id) {
    this->tasks.startTask(id, programmer.getId());
}

void ProgrammerWidget::closeTask(int id) {
    this->tasks.closeTask(id);
}
