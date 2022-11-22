/****************************************************************************
** Meta object code from reading C++ file 'GUI.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../GUI/GUI.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI_t {
    const uint offsetsAndSize[102];
    char stringdata0[783];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI_t qt_meta_stringdata_GUI = {
    {
QT_MOC_LITERAL(0, 3), // "GUI"
QT_MOC_LITERAL(4, 14), // "dataBaseUpdate"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 12), // "addDogSignal"
QT_MOC_LITERAL(33, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(58, 7), // "QLabel*"
QT_MOC_LITERAL(66, 15), // "updateDogSignal"
QT_MOC_LITERAL(82, 15), // "deleteDogSignal"
QT_MOC_LITERAL(98, 11), // "std::string"
QT_MOC_LITERAL(110, 10), // "undoSignal"
QT_MOC_LITERAL(121, 10), // "redoSignal"
QT_MOC_LITERAL(132, 16), // "filterListSignal"
QT_MOC_LITERAL(149, 14), // "adoptDogSignal"
QT_MOC_LITERAL(164, 18), // "dropAdoptionSignal"
QT_MOC_LITERAL(183, 25), // "availableDogsUpdateSignal"
QT_MOC_LITERAL(209, 16), // "std::vector<Dog>"
QT_MOC_LITERAL(226, 24), // "adoptionListUpdateSignal"
QT_MOC_LITERAL(251, 16), // "clearLandingMenu"
QT_MOC_LITERAL(268, 8), // "QWidget*"
QT_MOC_LITERAL(277, 17), // "landingMenuWidget"
QT_MOC_LITERAL(295, 10), // "updateList"
QT_MOC_LITERAL(306, 12), // "populateList"
QT_MOC_LITERAL(319, 12), // "QListWidget*"
QT_MOC_LITERAL(332, 20), // "populateAdoptionList"
QT_MOC_LITERAL(353, 21), // "populateAvailableList"
QT_MOC_LITERAL(375, 16), // "getSelectedIndex"
QT_MOC_LITERAL(392, 9), // "givenList"
QT_MOC_LITERAL(402, 9), // "adminMenu"
QT_MOC_LITERAL(412, 23), // "disableAdminMenuButtons"
QT_MOC_LITERAL(436, 8), // "userMenu"
QT_MOC_LITERAL(445, 15), // "userMenuOptions"
QT_MOC_LITERAL(461, 18), // "addFunctionalityUI"
QT_MOC_LITERAL(480, 28), // "std::pair<QWidget*,QLayout*>"
QT_MOC_LITERAL(509, 21), // "parentWidgetAndLayout"
QT_MOC_LITERAL(531, 6), // "addDog"
QT_MOC_LITERAL(538, 21), // "updateFunctionalityUI"
QT_MOC_LITERAL(560, 9), // "updateDog"
QT_MOC_LITERAL(570, 21), // "deleteFunctionalityUI"
QT_MOC_LITERAL(592, 9), // "deleteDog"
QT_MOC_LITERAL(602, 4), // "undo"
QT_MOC_LITERAL(607, 4), // "redo"
QT_MOC_LITERAL(612, 12), // "createFields"
QT_MOC_LITERAL(625, 32), // "std::pair<QWidget*,QFormLayout*>"
QT_MOC_LITERAL(658, 20), // "receivedWidgetLayout"
QT_MOC_LITERAL(679, 12), // "deleteFields"
QT_MOC_LITERAL(692, 16), // "getFieldsContent"
QT_MOC_LITERAL(709, 14), // "populateFields"
QT_MOC_LITERAL(724, 17), // "filterListByBreed"
QT_MOC_LITERAL(742, 8), // "adoptDog"
QT_MOC_LITERAL(751, 12), // "dropAdoption"
QT_MOC_LITERAL(764, 18) // "manageAdoptionList"

    },
    "GUI\0dataBaseUpdate\0\0addDogSignal\0"
    "std::vector<std::string>\0QLabel*\0"
    "updateDogSignal\0deleteDogSignal\0"
    "std::string\0undoSignal\0redoSignal\0"
    "filterListSignal\0adoptDogSignal\0"
    "dropAdoptionSignal\0availableDogsUpdateSignal\0"
    "std::vector<Dog>\0adoptionListUpdateSignal\0"
    "clearLandingMenu\0QWidget*\0landingMenuWidget\0"
    "updateList\0populateList\0QListWidget*\0"
    "populateAdoptionList\0populateAvailableList\0"
    "getSelectedIndex\0givenList\0adminMenu\0"
    "disableAdminMenuButtons\0userMenu\0"
    "userMenuOptions\0addFunctionalityUI\0"
    "std::pair<QWidget*,QLayout*>\0"
    "parentWidgetAndLayout\0addDog\0"
    "updateFunctionalityUI\0updateDog\0"
    "deleteFunctionalityUI\0deleteDog\0undo\0"
    "redo\0createFields\0std::pair<QWidget*,QFormLayout*>\0"
    "receivedWidgetLayout\0deleteFields\0"
    "getFieldsContent\0populateFields\0"
    "filterListByBreed\0adoptDog\0dropAdoption\0"
    "manageAdoptionList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  236,    2, 0x06,    1 /* Public */,
       3,    2,  237,    2, 0x06,    2 /* Public */,
       6,    2,  242,    2, 0x06,    5 /* Public */,
       7,    1,  247,    2, 0x06,    8 /* Public */,
       9,    0,  250,    2, 0x06,   10 /* Public */,
      10,    0,  251,    2, 0x06,   11 /* Public */,
      11,    1,  252,    2, 0x06,   12 /* Public */,
      12,    0,  255,    2, 0x06,   14 /* Public */,
      13,    0,  256,    2, 0x06,   15 /* Public */,
      14,    1,  257,    2, 0x06,   16 /* Public */,
      16,    1,  260,    2, 0x06,   18 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    1,  263,    2, 0x0a,   20 /* Public */,
      20,    0,  266,    2, 0x0a,   22 /* Public */,
      21,    2,  267,    2, 0x0a,   23 /* Public */,
      23,    1,  272,    2, 0x0a,   26 /* Public */,
      24,    1,  275,    2, 0x0a,   28 /* Public */,
      25,    1,  278,    2, 0x0a,   30 /* Public */,
      27,    0,  281,    2, 0x0a,   32 /* Public */,
      28,    0,  282,    2, 0x0a,   33 /* Public */,
      29,    0,  283,    2, 0x0a,   34 /* Public */,
      30,    0,  284,    2, 0x0a,   35 /* Public */,
      31,    1,  285,    2, 0x0a,   36 /* Public */,
      34,    2,  288,    2, 0x0a,   38 /* Public */,
      35,    1,  293,    2, 0x0a,   41 /* Public */,
      36,    2,  296,    2, 0x0a,   43 /* Public */,
      37,    0,  301,    2, 0x0a,   46 /* Public */,
      38,    1,  302,    2, 0x0a,   47 /* Public */,
      39,    0,  305,    2, 0x0a,   49 /* Public */,
      40,    0,  306,    2, 0x0a,   50 /* Public */,
      41,    1,  307,    2, 0x0a,   51 /* Public */,
      44,    1,  310,    2, 0x0a,   53 /* Public */,
      45,    0,  313,    2, 0x0a,   55 /* Public */,
      46,    0,  314,    2, 0x0a,   56 /* Public */,
      47,    1,  315,    2, 0x0a,   57 /* Public */,
      48,    0,  318,    2, 0x0a,   59 /* Public */,
      49,    0,  319,    2, 0x0a,   60 /* Public */,
      50,    1,  320,    2, 0x0a,   61 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 15,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 15,    2,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Int, 0x80000000 | 22,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 42, 0x80000000 | 32,   43,
    QMetaType::Void, 0x80000000 | 32,   43,
    0x80000000 | 4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   43,

       0        // eod
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataBaseUpdate(); break;
        case 1: _t->addDogSignal((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 2: _t->updateDogSignal((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 3: _t->deleteDogSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 4: _t->undoSignal(); break;
        case 5: _t->redoSignal(); break;
        case 6: _t->filterListSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 7: _t->adoptDogSignal(); break;
        case 8: _t->dropAdoptionSignal(); break;
        case 9: _t->availableDogsUpdateSignal((*reinterpret_cast< std::add_pointer_t<std::vector<Dog>>>(_a[1]))); break;
        case 10: _t->adoptionListUpdateSignal((*reinterpret_cast< std::add_pointer_t<std::vector<Dog>>>(_a[1]))); break;
        case 11: _t->clearLandingMenu((*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[1]))); break;
        case 12: _t->updateList(); break;
        case 13: _t->populateList((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<Dog>>>(_a[2]))); break;
        case 14: _t->populateAdoptionList((*reinterpret_cast< std::add_pointer_t<std::vector<Dog>>>(_a[1]))); break;
        case 15: _t->populateAvailableList((*reinterpret_cast< std::add_pointer_t<std::vector<Dog>>>(_a[1]))); break;
        case 16: { int _r = _t->getSelectedIndex((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->adminMenu(); break;
        case 18: _t->disableAdminMenuButtons(); break;
        case 19: _t->userMenu(); break;
        case 20: _t->userMenuOptions(); break;
        case 21: _t->addFunctionalityUI((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1]))); break;
        case 22: _t->addDog((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 23: _t->updateFunctionalityUI((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1]))); break;
        case 24: _t->updateDog((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 25: _t->deleteFunctionalityUI(); break;
        case 26: _t->deleteDog((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 27: _t->undo(); break;
        case 28: _t->redo(); break;
        case 29: { std::pair<QWidget*,QFormLayout*> _r = _t->createFields((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::pair<QWidget*,QFormLayout*>*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->deleteFields((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1]))); break;
        case 31: { std::vector<std::string> _r = _t->getFieldsContent();
            if (_a[0]) *reinterpret_cast< std::vector<std::string>*>(_a[0]) = std::move(_r); }  break;
        case 32: _t->populateFields(); break;
        case 33: _t->filterListByBreed((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 34: _t->adoptDog(); break;
        case 35: _t->dropAdoption(); break;
        case 36: _t->manageAdoptionList((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::dataBaseUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GUI::*)(std::vector<std::string> , QLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::addDogSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GUI::*)(std::vector<std::string> , QLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::updateDogSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GUI::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::deleteDogSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::undoSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::redoSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GUI::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::filterListSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::adoptDogSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::dropAdoptionSignal)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GUI::*)(std::vector<Dog> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::availableDogsUpdateSignal)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GUI::*)(std::vector<Dog> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::adoptionListUpdateSignal)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject GUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GUI.offsetsAndSize,
    qt_meta_data_GUI,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GUI_t
, QtPrivate::TypeAndForceComplete<GUI, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Dog>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Dog>, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<const std::vector<Dog> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Dog>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Dog>, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QFormLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>


>,
    nullptr
} };


const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void GUI::dataBaseUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GUI::addDogSignal(std::vector<std::string> _t1, QLabel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GUI::updateDogSignal(std::vector<std::string> _t1, QLabel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GUI::deleteDogSignal(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GUI::undoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GUI::redoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void GUI::filterListSignal(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GUI::adoptDogSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void GUI::dropAdoptionSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void GUI::availableDogsUpdateSignal(std::vector<Dog> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GUI::adoptionListUpdateSignal(std::vector<Dog> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
