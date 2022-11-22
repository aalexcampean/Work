//
// Created by Alex Campean on 18.05.2022.
//


#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QShortcut>
#include "../Service/AdminService.h"
#include "DogsTableModel.h"
#include "../Operation/OperationExecution.h"

class GUI : public QWidget {
Q_OBJECT

public:
    GUI(AdminService *aService, UserService *uService, OperationExecution *opExecution, QWidget *parent = Q_NULLPTR);

    ~GUI();

private:
    /// Dependencies
    AdminService *adminService;
    UserService *userService;
    OperationExecution* op;

    /// Layout
    QWidget *mainWidget = new QWidget{};
    QVBoxLayout *mainLayout = new QVBoxLayout{this->mainWidget};

    /// Dogs Vector
    std::vector<Dog> dogsVector;
    std::vector<Dog> userAvailableVector;
    std::vector<Dog> userAdoptionVector;

    /// Dogs Lists
    QListWidget *dogsList;

    DogsTableModel* userAvailableModel;
    QTableView*  userAvailableView;

    DogsTableModel* userAdoptionsModel;
    QTableView*  userAdoptionsView;

    QListWidget *userAvailableList;
    QListWidget *userAdoptionList;

    /// Landing Menu
    QPushButton* adminButton;
    QPushButton* userButton;
    QPushButton* applicationCloseButton;

    /// Admin Menu
    QPushButton* adminAddButton;
    QPushButton* adminDeleteButton;
    QPushButton* adminUpdateButton;
    QPushButton* adminCloseButton;

    QPushButton* adminUndo;
    QPushButton* adminRedo;
    QShortcut* shortcutUndo = new QShortcut(QKeySequence("Command + Z"), this);
    QShortcut* shortcutRedo = new QShortcut(QKeySequence("Command + Shift + Z"), this);

    QLineEdit* breedInput;
    QLineEdit* nameInput;
    QLineEdit* ageInput;
    QLineEdit* imageInput;

    /// User Menu
    QPushButton* userHtmlButton;
    QPushButton* userCsvButton;

    QLineEdit* userFilterInput;

    QPushButton* userAddButton;
    QPushButton* userDeleteButton;
    QPushButton* userDoneButton;
    QPushButton* userFilterButton;
    QPushButton* userAdoptButton;
    QPushButton* userCloseButton;

    void mapSignalsToSlots();
    void landingMenu();


signals:
    void dataBaseUpdate();

    void addDogSignal(std::vector<std::string>, QLabel*);
    void updateDogSignal(std::vector<std::string>, QLabel*);
    void deleteDogSignal(const std::string&);

    void undoSignal();
    void redoSignal();

    void filterListSignal(const std::string&);

    void adoptDogSignal();
    void dropAdoptionSignal();

    void availableDogsUpdateSignal(std::vector<Dog>);
    void adoptionListUpdateSignal(std::vector<Dog>);

public slots:
    void clearLandingMenu(QWidget *landingMenuWidget);

    void updateList();
    void populateList(QListWidget*, const std::vector<Dog>&);

    void populateAdoptionList(std::vector<Dog>);
    void populateAvailableList(std::vector<Dog>);

    int getSelectedIndex(QListWidget *givenList);

    void adminMenu();
    void disableAdminMenuButtons();

    void userMenu();
    void userMenuOptions();

    void addFunctionalityUI(std::pair<QWidget*, QLayout*> parentWidgetAndLayout);
    void addDog(std::vector<std::string>, QLabel*);

    void updateFunctionalityUI(std::pair<QWidget *, QLayout *> parentWidgetAndLayout);
    void updateDog(std::vector<std::string>, QLabel*);

    void deleteFunctionalityUI();
    void deleteDog(const std::string&);

    void undo();
    void redo();

    std::pair<QWidget *, QFormLayout *> createFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout);
    void deleteFields(std::pair<QWidget *, QLayout *> receivedWidgetLayout);
    std::vector<std::string> getFieldsContent();
    void populateFields();

    void filterListByBreed(const std::string&);

    void adoptDog();
    void dropAdoption();

    void manageAdoptionList(std::pair<QWidget *, QLayout *> receivedWidgetLayout);
};
