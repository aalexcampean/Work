/****************************************************************************
** Meta object code from reading C++ file 'ProgrammerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Widgets/ProgrammerWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProgrammerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProgrammerWidget_t {
    const uint offsetsAndSize[44];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ProgrammerWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ProgrammerWidget_t qt_meta_stringdata_ProgrammerWidget = {
    {
QT_MOC_LITERAL(0, 16), // "ProgrammerWidget"
QT_MOC_LITERAL(17, 16), // "updateListSignal"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 13), // "addTaskSignal"
QT_MOC_LITERAL(49, 11), // "std::string"
QT_MOC_LITERAL(61, 11), // "description"
QT_MOC_LITERAL(73, 16), // "deleteTaskSignal"
QT_MOC_LITERAL(90, 2), // "id"
QT_MOC_LITERAL(93, 15), // "startTaskSignal"
QT_MOC_LITERAL(109, 15), // "closeTaskSignal"
QT_MOC_LITERAL(125, 6), // "initUI"
QT_MOC_LITERAL(132, 17), // "mapSignalsToSlots"
QT_MOC_LITERAL(150, 16), // "getSelectedIndex"
QT_MOC_LITERAL(167, 12), // "QListWidget*"
QT_MOC_LITERAL(180, 9), // "givenList"
QT_MOC_LITERAL(190, 13), // "getSelectedId"
QT_MOC_LITERAL(204, 6), // "update"
QT_MOC_LITERAL(211, 10), // "updateList"
QT_MOC_LITERAL(222, 7), // "addTask"
QT_MOC_LITERAL(230, 10), // "deleteTask"
QT_MOC_LITERAL(241, 9), // "startTask"
QT_MOC_LITERAL(251, 9) // "closeTask"

    },
    "ProgrammerWidget\0updateListSignal\0\0"
    "addTaskSignal\0std::string\0description\0"
    "deleteTaskSignal\0id\0startTaskSignal\0"
    "closeTaskSignal\0initUI\0mapSignalsToSlots\0"
    "getSelectedIndex\0QListWidget*\0givenList\0"
    "getSelectedId\0update\0updateList\0addTask\0"
    "deleteTask\0startTask\0closeTask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProgrammerWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x06,    1 /* Public */,
       3,    1,  105,    2, 0x06,    2 /* Public */,
       6,    1,  108,    2, 0x06,    4 /* Public */,
       8,    1,  111,    2, 0x06,    6 /* Public */,
       9,    1,  114,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,  117,    2, 0x0a,   10 /* Public */,
      11,    0,  118,    2, 0x0a,   11 /* Public */,
      12,    1,  119,    2, 0x0a,   12 /* Public */,
      15,    0,  122,    2, 0x0a,   14 /* Public */,
      16,    0,  123,    2, 0x0a,   15 /* Public */,
      17,    0,  124,    2, 0x0a,   16 /* Public */,
      18,    1,  125,    2, 0x0a,   17 /* Public */,
      19,    1,  128,    2, 0x0a,   19 /* Public */,
      20,    1,  131,    2, 0x0a,   21 /* Public */,
      21,    1,  134,    2, 0x0a,   23 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 13,   14,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void ProgrammerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProgrammerWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateListSignal(); break;
        case 1: _t->addTaskSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 2: _t->deleteTaskSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->startTaskSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->closeTaskSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->initUI(); break;
        case 6: _t->mapSignalsToSlots(); break;
        case 7: { int _r = _t->getSelectedIndex((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->getSelectedId();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->update(); break;
        case 10: _t->updateList(); break;
        case 11: _t->addTask((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 12: _t->deleteTask((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->startTask((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->closeTask((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProgrammerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProgrammerWidget::updateListSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProgrammerWidget::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProgrammerWidget::addTaskSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProgrammerWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProgrammerWidget::deleteTaskSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProgrammerWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProgrammerWidget::startTaskSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ProgrammerWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProgrammerWidget::closeTaskSignal)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject ProgrammerWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ProgrammerWidget.offsetsAndSize,
    qt_meta_data_ProgrammerWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ProgrammerWidget_t
, QtPrivate::TypeAndForceComplete<ProgrammerWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *ProgrammerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProgrammerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProgrammerWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Observer"))
        return static_cast< Observer*>(this);
    return QWidget::qt_metacast(_clname);
}

int ProgrammerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ProgrammerWidget::updateListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ProgrammerWidget::addTaskSignal(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProgrammerWidget::deleteTaskSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ProgrammerWidget::startTaskSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ProgrammerWidget::closeTaskSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
