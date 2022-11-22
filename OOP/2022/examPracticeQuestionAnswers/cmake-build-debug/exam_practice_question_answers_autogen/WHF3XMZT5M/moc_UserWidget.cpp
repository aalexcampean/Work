/****************************************************************************
** Meta object code from reading C++ file 'UserWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Widgets/UserWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UserWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserWidget_t {
    const uint offsetsAndSize[54];
    char stringdata0[345];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_UserWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_UserWidget_t qt_meta_stringdata_UserWidget = {
    {
QT_MOC_LITERAL(0, 10), // "UserWidget"
QT_MOC_LITERAL(11, 24), // "updateQuestionListSignal"
QT_MOC_LITERAL(36, 0), // ""
QT_MOC_LITERAL(37, 22), // "updateAnswerListSignal"
QT_MOC_LITERAL(60, 10), // "questionId"
QT_MOC_LITERAL(71, 17), // "addQuestionSignal"
QT_MOC_LITERAL(89, 11), // "std::string"
QT_MOC_LITERAL(101, 4), // "text"
QT_MOC_LITERAL(106, 8), // "userName"
QT_MOC_LITERAL(115, 15), // "addAnswerSignal"
QT_MOC_LITERAL(131, 16), // "voteAnswerSignal"
QT_MOC_LITERAL(148, 2), // "id"
QT_MOC_LITERAL(151, 5), // "votes"
QT_MOC_LITERAL(157, 6), // "initUI"
QT_MOC_LITERAL(164, 17), // "mapSignalsToSlots"
QT_MOC_LITERAL(182, 16), // "getSelectedIndex"
QT_MOC_LITERAL(199, 12), // "QListWidget*"
QT_MOC_LITERAL(212, 9), // "givenList"
QT_MOC_LITERAL(222, 21), // "getSelectedQuestionId"
QT_MOC_LITERAL(244, 17), // "getSelectedAnswer"
QT_MOC_LITERAL(262, 6), // "Answer"
QT_MOC_LITERAL(269, 18), // "updateQuestionList"
QT_MOC_LITERAL(288, 16), // "updateAnswerList"
QT_MOC_LITERAL(305, 6), // "update"
QT_MOC_LITERAL(312, 11), // "addQuestion"
QT_MOC_LITERAL(324, 9), // "addAnswer"
QT_MOC_LITERAL(334, 10) // "voteAnswer"

    },
    "UserWidget\0updateQuestionListSignal\0"
    "\0updateAnswerListSignal\0questionId\0"
    "addQuestionSignal\0std::string\0text\0"
    "userName\0addAnswerSignal\0voteAnswerSignal\0"
    "id\0votes\0initUI\0mapSignalsToSlots\0"
    "getSelectedIndex\0QListWidget*\0givenList\0"
    "getSelectedQuestionId\0getSelectedAnswer\0"
    "Answer\0updateQuestionList\0updateAnswerList\0"
    "update\0addQuestion\0addAnswer\0voteAnswer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    1 /* Public */,
       3,    1,  111,    2, 0x06,    2 /* Public */,
       5,    2,  114,    2, 0x06,    4 /* Public */,
       9,    3,  119,    2, 0x06,    7 /* Public */,
      10,    2,  126,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,  131,    2, 0x0a,   14 /* Public */,
      14,    0,  132,    2, 0x0a,   15 /* Public */,
      15,    1,  133,    2, 0x0a,   16 /* Public */,
      18,    0,  136,    2, 0x0a,   18 /* Public */,
      19,    0,  137,    2, 0x0a,   19 /* Public */,
      21,    0,  138,    2, 0x0a,   20 /* Public */,
      22,    1,  139,    2, 0x0a,   21 /* Public */,
      23,    0,  142,    2, 0x0a,   23 /* Public */,
      24,    2,  143,    2, 0x0a,   24 /* Public */,
      25,    3,  148,    2, 0x0a,   27 /* Public */,
      26,    2,  155,    2, 0x0a,   31 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6, 0x80000000 | 6,    4,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 16,   17,
    QMetaType::Int,
    0x80000000 | 20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6, 0x80000000 | 6,    4,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,

       0        // eod
};

void UserWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateQuestionListSignal(); break;
        case 1: _t->updateAnswerListSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->addQuestionSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2]))); break;
        case 3: _t->addAnswerSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[3]))); break;
        case 4: _t->voteAnswerSignal((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->initUI(); break;
        case 6: _t->mapSignalsToSlots(); break;
        case 7: { int _r = _t->getSelectedIndex((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->getSelectedQuestionId();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: { Answer _r = _t->getSelectedAnswer();
            if (_a[0]) *reinterpret_cast< Answer*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->updateQuestionList(); break;
        case 11: _t->updateAnswerList((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->update(); break;
        case 13: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2]))); break;
        case 14: _t->addAnswer((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[3]))); break;
        case 15: _t->voteAnswer((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
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
            using _t = void (UserWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserWidget::updateQuestionListSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UserWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserWidget::updateAnswerListSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UserWidget::*)(const std::string & , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserWidget::addQuestionSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UserWidget::*)(int , const std::string & , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserWidget::addAnswerSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UserWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserWidget::voteAnswerSignal)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject UserWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_UserWidget.offsetsAndSize,
    qt_meta_data_UserWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_UserWidget_t
, QtPrivate::TypeAndForceComplete<UserWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<Answer, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *UserWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Observer"))
        return static_cast< Observer*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void UserWidget::updateQuestionListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UserWidget::updateAnswerListSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UserWidget::addQuestionSignal(const std::string & _t1, const std::string & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UserWidget::addAnswerSignal(int _t1, const std::string & _t2, const std::string & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UserWidget::voteAnswerSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
