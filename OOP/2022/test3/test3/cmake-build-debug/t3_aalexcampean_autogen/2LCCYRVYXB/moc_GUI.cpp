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
    const uint offsetsAndSize[40];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI_t qt_meta_stringdata_GUI = {
    {
QT_MOC_LITERAL(0, 3), // "GUI"
QT_MOC_LITERAL(4, 14), // "dataBaseUpdate"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 17), // "addEquationSignal"
QT_MOC_LITERAL(38, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(63, 7), // "QLabel*"
QT_MOC_LITERAL(71, 10), // "updateList"
QT_MOC_LITERAL(82, 16), // "getSelectedIndex"
QT_MOC_LITERAL(99, 12), // "QListWidget*"
QT_MOC_LITERAL(112, 9), // "givenList"
QT_MOC_LITERAL(122, 14), // "disableButtons"
QT_MOC_LITERAL(137, 18), // "addFunctionalityUI"
QT_MOC_LITERAL(156, 28), // "std::pair<QWidget*,QLayout*>"
QT_MOC_LITERAL(185, 21), // "parentWidgetAndLayout"
QT_MOC_LITERAL(207, 11), // "addEquation"
QT_MOC_LITERAL(219, 12), // "createFields"
QT_MOC_LITERAL(232, 32), // "std::pair<QWidget*,QFormLayout*>"
QT_MOC_LITERAL(265, 20), // "receivedWidgetLayout"
QT_MOC_LITERAL(286, 12), // "deleteFields"
QT_MOC_LITERAL(299, 16) // "getFieldsContent"

    },
    "GUI\0dataBaseUpdate\0\0addEquationSignal\0"
    "std::vector<std::string>\0QLabel*\0"
    "updateList\0getSelectedIndex\0QListWidget*\0"
    "givenList\0disableButtons\0addFunctionalityUI\0"
    "std::pair<QWidget*,QLayout*>\0"
    "parentWidgetAndLayout\0addEquation\0"
    "createFields\0std::pair<QWidget*,QFormLayout*>\0"
    "receivedWidgetLayout\0deleteFields\0"
    "getFieldsContent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,
       3,    2,   75,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   80,    2, 0x0a,    5 /* Public */,
       7,    1,   81,    2, 0x0a,    6 /* Public */,
      10,    0,   84,    2, 0x0a,    8 /* Public */,
      11,    1,   85,    2, 0x0a,    9 /* Public */,
      14,    2,   88,    2, 0x0a,   11 /* Public */,
      15,    1,   93,    2, 0x0a,   14 /* Public */,
      18,    1,   96,    2, 0x0a,   16 /* Public */,
      19,    0,   99,    2, 0x0a,   18 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,
    0x80000000 | 16, 0x80000000 | 12,   17,
    QMetaType::Void, 0x80000000 | 12,   17,
    0x80000000 | 4,

       0        // eod
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataBaseUpdate(); break;
        case 1: _t->addEquationSignal((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 2: _t->updateList(); break;
        case 3: { int _r = _t->getSelectedIndex((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->disableButtons(); break;
        case 5: _t->addFunctionalityUI((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1]))); break;
        case 6: _t->addEquation((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 7: { std::pair<QWidget*,QFormLayout*> _r = _t->createFields((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::pair<QWidget*,QFormLayout*>*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->deleteFields((*reinterpret_cast< std::add_pointer_t<std::pair<QWidget*,QLayout*>>>(_a[1]))); break;
        case 9: { std::vector<std::string> _r = _t->getFieldsContent();
            if (_a[0]) *reinterpret_cast< std::vector<std::string>*>(_a[0]) = std::move(_r); }  break;
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
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 6:
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::addEquationSignal)) {
                *result = 1;
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
, QtPrivate::TypeAndForceComplete<GUI, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QFormLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::pair<QWidget*,QLayout*>, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>


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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void GUI::dataBaseUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GUI::addEquationSignal(std::vector<std::string> _t1, QLabel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
