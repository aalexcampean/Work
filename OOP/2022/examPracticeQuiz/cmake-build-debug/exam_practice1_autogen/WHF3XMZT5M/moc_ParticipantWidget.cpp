/****************************************************************************
** Meta object code from reading C++ file 'ParticipantWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Widgets/ParticipantWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParticipantWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParticipantWidget_t {
    const uint offsetsAndSize[28];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ParticipantWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ParticipantWidget_t qt_meta_stringdata_ParticipantWidget = {
    {
QT_MOC_LITERAL(0, 17), // "ParticipantWidget"
QT_MOC_LITERAL(18, 16), // "updateListSignal"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 20), // "answerQuestionSignal"
QT_MOC_LITERAL(57, 11), // "std::string"
QT_MOC_LITERAL(69, 6), // "initUI"
QT_MOC_LITERAL(76, 17), // "mapSignalsToSlots"
QT_MOC_LITERAL(94, 16), // "getSelectedIndex"
QT_MOC_LITERAL(111, 12), // "QListWidget*"
QT_MOC_LITERAL(124, 9), // "givenList"
QT_MOC_LITERAL(134, 6), // "update"
QT_MOC_LITERAL(141, 10), // "updateList"
QT_MOC_LITERAL(152, 14), // "answerQuestion"
QT_MOC_LITERAL(167, 6) // "answer"

    },
    "ParticipantWidget\0updateListSignal\0\0"
    "answerQuestionSignal\0std::string\0"
    "initUI\0mapSignalsToSlots\0getSelectedIndex\0"
    "QListWidget*\0givenList\0update\0updateList\0"
    "answerQuestion\0answer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParticipantWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    1,   63,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   66,    2, 0x0a,    4 /* Public */,
       6,    0,   67,    2, 0x0a,    5 /* Public */,
       7,    1,   68,    2, 0x0a,    6 /* Public */,
      10,    0,   71,    2, 0x0a,    8 /* Public */,
      11,    0,   72,    2, 0x0a,    9 /* Public */,
      12,    1,   73,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,   13,

       0        // eod
};

void ParticipantWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ParticipantWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateListSignal(); break;
        case 1: _t->answerQuestionSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 2: _t->initUI(); break;
        case 3: _t->mapSignalsToSlots(); break;
        case 4: { int _r = _t->getSelectedIndex((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->update(); break;
        case 6: _t->updateList(); break;
        case 7: _t->answerQuestion((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
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
            using _t = void (ParticipantWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParticipantWidget::updateListSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ParticipantWidget::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParticipantWidget::answerQuestionSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ParticipantWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ParticipantWidget.offsetsAndSize,
    qt_meta_data_ParticipantWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ParticipantWidget_t
, QtPrivate::TypeAndForceComplete<ParticipantWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::string, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::string, std::false_type>


>,
    nullptr
} };


const QMetaObject *ParticipantWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParticipantWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParticipantWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Observer"))
        return static_cast< Observer*>(this);
    return QWidget::qt_metacast(_clname);
}

int ParticipantWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ParticipantWidget::updateListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ParticipantWidget::answerQuestionSignal(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
