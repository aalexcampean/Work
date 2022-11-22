/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Gui/gui.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI_t {
    const uint offsetsAndSize[56];
    char stringdata0[391];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_GUI_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_GUI_t qt_meta_stringdata_GUI = {
    {
QT_MOC_LITERAL(0, 3), // "GUI"
QT_MOC_LITERAL(4, 14), // "addMovieSignal"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(45, 7), // "QLabel*"
QT_MOC_LITERAL(53, 17), // "updateMovieSignal"
QT_MOC_LITERAL(71, 17), // "deleteMovieSignal"
QT_MOC_LITERAL(89, 11), // "std::string"
QT_MOC_LITERAL(101, 10), // "undoSignal"
QT_MOC_LITERAL(112, 10), // "redoSignal"
QT_MOC_LITERAL(123, 16), // "filterListSignal"
QT_MOC_LITERAL(140, 20), // "addToWatchListSignal"
QT_MOC_LITERAL(161, 25), // "deleteFromWatchlistSignal"
QT_MOC_LITERAL(187, 14), // "dataBaseUpdate"
QT_MOC_LITERAL(202, 16), // "moviesListUpdate"
QT_MOC_LITERAL(219, 18), // "std::vector<Movie>"
QT_MOC_LITERAL(238, 15), // "watchListUpdate"
QT_MOC_LITERAL(254, 12), // "populateList"
QT_MOC_LITERAL(267, 16), // "populateUserList"
QT_MOC_LITERAL(284, 17), // "populateWatchlist"
QT_MOC_LITERAL(302, 8), // "addMovie"
QT_MOC_LITERAL(311, 11), // "deleteMovie"
QT_MOC_LITERAL(323, 4), // "undo"
QT_MOC_LITERAL(328, 4), // "redo"
QT_MOC_LITERAL(333, 11), // "updateMovie"
QT_MOC_LITERAL(345, 10), // "filterList"
QT_MOC_LITERAL(356, 14), // "addToWatchList"
QT_MOC_LITERAL(371, 19) // "deleteFromWatchlist"

    },
    "GUI\0addMovieSignal\0\0std::vector<std::string>\0"
    "QLabel*\0updateMovieSignal\0deleteMovieSignal\0"
    "std::string\0undoSignal\0redoSignal\0"
    "filterListSignal\0addToWatchListSignal\0"
    "deleteFromWatchlistSignal\0dataBaseUpdate\0"
    "moviesListUpdate\0std::vector<Movie>\0"
    "watchListUpdate\0populateList\0"
    "populateUserList\0populateWatchlist\0"
    "addMovie\0deleteMovie\0undo\0redo\0"
    "updateMovie\0filterList\0addToWatchList\0"
    "deleteFromWatchlist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  146,    2, 0x06,    1 /* Public */,
       5,    2,  151,    2, 0x06,    4 /* Public */,
       6,    1,  156,    2, 0x06,    7 /* Public */,
       8,    0,  159,    2, 0x06,    9 /* Public */,
       9,    0,  160,    2, 0x06,   10 /* Public */,
      10,    1,  161,    2, 0x06,   11 /* Public */,
      11,    0,  164,    2, 0x06,   13 /* Public */,
      12,    0,  165,    2, 0x06,   14 /* Public */,
      13,    0,  166,    2, 0x06,   15 /* Public */,
      14,    1,  167,    2, 0x06,   16 /* Public */,
      16,    1,  170,    2, 0x06,   18 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    0,  173,    2, 0x0a,   20 /* Public */,
      18,    1,  174,    2, 0x0a,   21 /* Public */,
      19,    1,  177,    2, 0x0a,   23 /* Public */,
      20,    2,  180,    2, 0x0a,   25 /* Public */,
      21,    1,  185,    2, 0x0a,   28 /* Public */,
      22,    0,  188,    2, 0x0a,   30 /* Public */,
      23,    0,  189,    2, 0x0a,   31 /* Public */,
      24,    2,  190,    2, 0x0a,   32 /* Public */,
      25,    1,  195,    2, 0x0a,   35 /* Public */,
      26,    0,  198,    2, 0x0a,   37 /* Public */,
      27,    0,  199,    2, 0x0a,   38 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 15,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addMovieSignal((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 1: _t->updateMovieSignal((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 2: _t->deleteMovieSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 3: _t->undoSignal(); break;
        case 4: _t->redoSignal(); break;
        case 5: _t->filterListSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 6: _t->addToWatchListSignal(); break;
        case 7: _t->deleteFromWatchlistSignal(); break;
        case 8: _t->dataBaseUpdate(); break;
        case 9: _t->moviesListUpdate((*reinterpret_cast< std::add_pointer_t<std::vector<Movie>>>(_a[1]))); break;
        case 10: _t->watchListUpdate((*reinterpret_cast< std::add_pointer_t<std::vector<Movie>>>(_a[1]))); break;
        case 11: _t->populateList(); break;
        case 12: _t->populateUserList((*reinterpret_cast< std::add_pointer_t<std::vector<Movie>>>(_a[1]))); break;
        case 13: _t->populateWatchlist((*reinterpret_cast< std::add_pointer_t<std::vector<Movie>>>(_a[1]))); break;
        case 14: _t->addMovie((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 15: _t->deleteMovie((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 16: _t->undo(); break;
        case 17: _t->redo(); break;
        case 18: _t->updateMovie((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 19: _t->filterList((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 20: _t->addToWatchList(); break;
        case 21: _t->deleteFromWatchlist(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 18:
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
            using _t = void (GUI::*)(std::vector<std::string> , QLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::addMovieSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GUI::*)(std::vector<std::string> , QLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::updateMovieSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GUI::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::deleteMovieSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::undoSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::redoSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GUI::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::filterListSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::addToWatchListSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::deleteFromWatchlistSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::dataBaseUpdate)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GUI::*)(std::vector<Movie> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::moviesListUpdate)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GUI::*)(std::vector<Movie> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::watchListUpdate)) {
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
, QtPrivate::TypeAndForceComplete<GUI, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Movie>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Movie>, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Movie>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Movie>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void GUI::addMovieSignal(std::vector<std::string> _t1, QLabel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUI::updateMovieSignal(std::vector<std::string> _t1, QLabel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GUI::deleteMovieSignal(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GUI::undoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GUI::redoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GUI::filterListSignal(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GUI::addToWatchListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GUI::deleteFromWatchlistSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void GUI::dataBaseUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void GUI::moviesListUpdate(std::vector<Movie> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GUI::watchListUpdate(std::vector<Movie> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
