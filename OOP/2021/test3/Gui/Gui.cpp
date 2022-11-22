#include "Gui.h"


Gui::Gui(QWidget *parent) : QWidget(parent) {
    Service designatedService{};
    this->service = designatedService;
    this->connectSignalsAndSlots();
    this->initGUI();
}

Gui::~Gui() {
}

void Gui::initGUI() {
    setLayout(this->mainLayout);
    this->startApplication();
}

void Gui::connectSignalsAndSlots() {
    QObject::connect(this, SIGNAL(listUpdate(const std::vector<Weather> &)), this, SLOT(populateList(const std::vector<Weather> &)));
    QObject::connect(this, SIGNAL(filterListPrecipitationSignal()), this, SLOT(filterListPrecipitation()));
    QObject::connect(this, SIGNAL(filterListDescriptionSignal()), this, SLOT(filterListDescription()));
}

void Gui::populateList(const std::vector<Weather>& inputVector) {
    if (this->weatherList->count() > 0)
        this->weatherList->clear();

    std::vector<Weather> db = inputVector;
    for (auto it : db) {
        QListWidgetItem* bill = new QListWidgetItem{ QString::fromStdString(it.toString()) };
        bill->setData(Qt::UserRole, QString::fromStdString(it.toString()));
        this->weatherList->addItem(bill);
    }

    // set the selection on the first item in the list
    if (!inputVector.empty())
        this->weatherList->setCurrentRow(0);
}

void Gui::startApplication() {
    //General layout of the window
    QWidget* windowWidget = new QWidget{};
    QVBoxLayout* windowLayout = new QVBoxLayout{windowWidget};

    // the top layout - a vertical one
    QWidget* topWidget = new QWidget{};
    QHBoxLayout* topLayout = new QHBoxLayout{topWidget};

    // the bottom layout - a grid one
    QWidget* bottomWidget = new QWidget{};
    QVBoxLayout* bottomLayout = new QVBoxLayout{bottomWidget};

    // the list of movies - on the left
    this->weatherList = new QListWidget{};
    // set the selection model
    this->weatherList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->weatherVector = this->service.getDataBase();
    this->populateList(this->weatherVector);

    this->bFilterPrecipitation = new QSlider;
    this->bFilterPrecipitation->setLayoutDirection(Qt::LeftToRight);
    this->bFilterPrecipitation->setOrientation(Qt::Horizontal);
    this->bFilterPrecipitation->setFocusPolicy(Qt::StrongFocus);
    this->bFilterPrecipitation->setTickPosition(QSlider::TicksBothSides);
    this->bFilterPrecipitation->setTickInterval(100);
    this->bFilterPrecipitation->setSingleStep(1);
    this->bFilterPrecipitation->setMinimumHeight(35);


    QWidget* checkBoxWidget = new QWidget{};
    QGridLayout* checkBoxLayout = new QGridLayout{checkBoxWidget};

    this->weatherVectorAuxiliary = this->weatherVector;
    int i = 0;
    std::vector<std::string> descriptions = this->service.getDescriptions();
    for (auto &it : descriptions) {
        QCheckBox* checkBox = new QCheckBox{};
        checkBox->setText(QString::fromStdString(it));
        this->checkBoxList.push_back(checkBox);
        checkBoxLayout->addWidget(checkBox, 0, i);
        QObject::connect(checkBox, &QCheckBox::stateChanged, this, [=](){
            emit this->filterListDescriptionSignal();
        });
        i += 1;
    }

    this->bClose = new QPushButton{ "Close" };
    this->bClose->setMinimumHeight(35);

    this->bUndo = new QPushButton{ "Undo" };
    this->bUndo->setMinimumHeight(35);


    QObject::connect(this->bFilterPrecipitation, &QSlider::valueChanged, this, [=](){
        emit this->filterListPrecipitationSignal();
    });

    QObject::connect(this->bUndo, &QPushButton::clicked, this, [=](){
        this->bFilterPrecipitation->setValue(0);
        for (auto &it : this->checkBoxList) {
            it->setCheckState(Qt::CheckState::Unchecked);
        }
        emit this->listUpdate(this->weatherVector);
    });

    QObject::connect(this->bClose, &QPushButton::clicked, this, &QApplication::quit);

    topLayout->addWidget(this->weatherList);

    bottomLayout->addWidget(checkBoxWidget);
    bottomLayout->addWidget(this->bFilterPrecipitation);
    bottomLayout->addWidget(this->bUndo);
    bottomLayout->addWidget(this->bClose);

    windowLayout->addWidget(topWidget);
    windowLayout->addWidget(bottomWidget);

    this->mainLayout->addWidget(windowWidget);
}

void Gui::filterListPrecipitation() {
    int precipitation = this->bFilterPrecipitation->value();
    std::vector<Weather> filteredVector = this->service.filterDataBasePrecipitation(precipitation);
    emit this->listUpdate(filteredVector);
}

void Gui::filterListDescription() {
    std::vector<std::string> descriptions;

    for (auto &it : this->checkBoxList) {
        if (it->isChecked()) {
            std::string name = it->text().toStdString();
            descriptions.push_back(name);
        }
    }

    std::vector<Weather> sortedVector = this->service.filterDataBaseDescription(descriptions);
    emit this->listUpdate(sortedVector);
}


