/****************************************************************************
** Meta object code from reading C++ file 'WriterWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Widgets/WriterWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WriterWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WriterWidget_t {
    const uint offsetsAndSize[34];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_WriterWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_WriterWidget_t qt_meta_stringdata_WriterWidget = {
    {
QT_MOC_LITERAL(0, 12), // "WriterWidget"
QT_MOC_LITERAL(13, 13), // "addIdeaSignal"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 11), // "std::string"
QT_MOC_LITERAL(40, 11), // "description"
QT_MOC_LITERAL(52, 3), // "act"
QT_MOC_LITERAL(56, 21), // "updateIdeasViewSignal"
QT_MOC_LITERAL(78, 17), // "std::vector<Idea>"
QT_MOC_LITERAL(96, 11), // "inputVector"
QT_MOC_LITERAL(108, 16), // "reviseIdeaSignal"
QT_MOC_LITERAL(125, 14), // "savePlotSignal"
QT_MOC_LITERAL(140, 6), // "initUI"
QT_MOC_LITERAL(147, 17), // "mapSignalsToSlots"
QT_MOC_LITERAL(165, 7), // "addIdea"
QT_MOC_LITERAL(173, 15), // "updateIdeasView"
QT_MOC_LITERAL(189, 10), // "reviseIdea"
QT_MOC_LITERAL(200, 8) // "savePlot"

    },
    "WriterWidget\0addIdeaSignal\0\0std::string\0"
    "description\0act\0updateIdeasViewSignal\0"
    "std::vector<Idea>\0inputVector\0"
    "reviseIdeaSignal\0savePlotSignal\0initUI\0"
    "mapSignalsToSlots\0addIdea\0updateIdeasView\0"
    "reviseIdea\0savePlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WriterWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   74,    2, 0x06,    1 /* Public */,
       6,    1,   79,    2, 0x06,    4 /* Public */,
       9,    0,   82,    2, 0x06,    6 /* Public */,
      10,    0,   83,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,   84,    2, 0x0a,    8 /* Public */,
      12,    0,   85,    2, 0x0a,    9 /* Public */,
      13,    2,   86,    2, 0x0a,   10 /* Public */,
      14,    1,   91,    2, 0x0a,   13 /* Public */,
      15,    0,   94,    2, 0x0a,   15 /* Public */,
      16,    0,   95,    2, 0x0a,   16 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WriterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WriterWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addIdeaSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->updateIdeasViewSignal((*reinterpret_cast< std::add_pointer_t<std::vector<Idea>>>(_a[1]))); break;
        case 2: _t->reviseIdeaSignal(); break;
        case 3: _t->savePlotSignal(); break;
        case 4: _t->initUI(); break;
        case 5: _t->mapSignalsToSlots(); break;
        case 6: _t->addIdea((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->updateIdeasView((*reinterpret_cast< std::add_pointer_t<std::vector<Idea>>>(_a[1]))); break;
        case 8: _t->reviseIdea(); break;
        case 9: _t->savePlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WriterWidget::*)(const std::string & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WriterWidget::addIdeaSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WriterWidget::*)(std::vector<Idea> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WriterWidget::updateIdeasViewSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WriterWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WriterWidget::reviseIdeaSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WriterWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WriterWidget::savePlotSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject WriterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_WriterWidget.offsetsAndSize,
    qt_meta_data_WriterWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_WriterWidget_t
, QtPrivate::TypeAndForceComplete<WriterWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Idea>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Idea>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *WriterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WriterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WriterWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WriterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void WriterWidget::addIdeaSignal(const std::string & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WriterWidget::updateIdeasViewSignal(std::vector<Idea> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WriterWidget::reviseIdeaSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WriterWidget::savePlotSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
