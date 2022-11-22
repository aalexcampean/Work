#include "../Service/Service.h"
#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>

class Gui : public QWidget {
Q_OBJECT

public:
    Gui(QWidget *parent = Q_NULLPTR);
    ~Gui();

private:
    Service service;

    std::vector<Weather> weatherVector;
    std::vector<Weather> weatherVectorAuxiliary;
    QListWidget* weatherList;

    QSlider* bFilterPrecipitation;
    QVector<QCheckBox*> checkBoxList;

    QPushButton* bClose;
    QPushButton* bUndo;

    QWidget* mainWidget = new QWidget{};
    QVBoxLayout* mainLayout = new QVBoxLayout{this->mainWidget};

    // methods
    void initGUI();
    void connectSignalsAndSlots();
    void startApplication();

signals:
    void listUpdate(const std::vector<Weather>&);
    void filterListPrecipitationSignal();
    void filterListDescriptionSignal();

public slots:
    void populateList(const std::vector<Weather>&);
    void filterListPrecipitation();
    void filterListDescription();
};


