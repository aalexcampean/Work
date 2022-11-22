/****************************************************************************
** Meta object code from reading C++ file 'PresenterWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Widgets/PresenterWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PresenterWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PresenterWidget_t {
    const uint offsetsAndSize[28];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PresenterWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PresenterWidget_t qt_meta_stringdata_PresenterWidget = {
    {
QT_MOC_LITERAL(0, 15), // "PresenterWidget"
QT_MOC_LITERAL(16, 16), // "updateListSignal"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 17), // "addQuestionSignal"
QT_MOC_LITERAL(52, 11), // "std::string"
QT_MOC_LITERAL(64, 2), // "id"
QT_MOC_LITERAL(67, 4), // "text"
QT_MOC_LITERAL(72, 13), // "correctAnswer"
QT_MOC_LITERAL(86, 5), // "score"
QT_MOC_LITERAL(92, 6), // "initUI"
QT_MOC_LITERAL(99, 17), // "mapSignalsToSlots"
QT_MOC_LITERAL(117, 6), // "update"
QT_MOC_LITERAL(124, 10), // "updateList"
QT_MOC_LITERAL(135, 11) // "addQuestion"

    },
    "PresenterWidget\0updateListSignal\0\0"
    "addQuestionSignal\0std::string\0id\0text\0"
    "correctAnswer\0score\0initUI\0mapSignalsToSlots\0"
    "update\0updateList\0addQuestion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PresenterWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    4,   57,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   66,    2, 0x0a,    7 /* Public */,
      10,    0,   67,    2, 0x0a,    8 /* Public */,
      11,    0,   68,    2, 0x0a,    9 /* Public */,
      12,    0,   69,    2, 0x0a,   10 /* Public */,
      13,    4,   70,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4,    5,    6,    7,    8,

       0        // eod
};

void PresenterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PresenterWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateListSignal(); break;
        case 1: _t->addQuestionSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[4]))); break;
        case 2: _t->initUI(); break;
        case 3: _t->mapSignalsToSlots(); break;
        case 4: _t->update(); break;
        case 5: _t->updateList(); break;
        case 6: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PresenterWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PresenterWidget::updateListSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PresenterWidget::*)(const std::string & , const std::string & , const std::string & , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PresenterWidget::addQuestionSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PresenterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PresenterWidget.offsetsAndSize,
    qt_meta_data_PresenterWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PresenterWidget_t
, QtPrivate::TypeAndForceComplete<PresenterWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>


>,
    nullptr
} };


const QMetaObject *PresenterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PresenterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PresenterWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Observer"))
        return static_cast< Observer*>(this);
    return QWidget::qt_metacast(_clname);
}

int PresenterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PresenterWidget::updateListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PresenterWidget::addQuestionSignal(const std::string & _t1, const std::string & _t2, const std::string & _t3, const std::string & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
