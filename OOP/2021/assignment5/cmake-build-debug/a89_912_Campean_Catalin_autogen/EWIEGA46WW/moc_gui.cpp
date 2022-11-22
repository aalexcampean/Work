/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../gui.h"
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
    const uint offsetsAndSize[48];
    char stringdata0[355];
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
QT_MOC_LITERAL(101, 16), // "filterListSignal"
QT_MOC_LITERAL(118, 20), // "addToWatchListSignal"
QT_MOC_LITERAL(139, 25), // "deleteFromWatchlistSignal"
QT_MOC_LITERAL(165, 14), // "dataBaseUpdate"
QT_MOC_LITERAL(180, 16), // "moviesListUpdate"
QT_MOC_LITERAL(197, 12), // "QListWidget*"
QT_MOC_LITERAL(210, 18), // "std::vector<Movie>"
QT_MOC_LITERAL(229, 15), // "watchListUpdate"
QT_MOC_LITERAL(245, 12), // "populateList"
QT_MOC_LITERAL(258, 17), // "populateUserLists"
QT_MOC_LITERAL(276, 8), // "addMovie"
QT_MOC_LITERAL(285, 11), // "deleteMovie"
QT_MOC_LITERAL(297, 11), // "updateMovie"
QT_MOC_LITERAL(309, 10), // "filterList"
QT_MOC_LITERAL(320, 14), // "addToWatchList"
QT_MOC_LITERAL(335, 19) // "deleteFromWatchlist"

    },
    "GUI\0addMovieSignal\0\0std::vector<std::string>\0"
    "QLabel*\0updateMovieSignal\0deleteMovieSignal\0"
    "std::string\0filterListSignal\0"
    "addToWatchListSignal\0deleteFromWatchlistSignal\0"
    "dataBaseUpdate\0moviesListUpdate\0"
    "QListWidget*\0std::vector<Movie>\0"
    "watchListUpdate\0populateList\0"
    "populateUserLists\0addMovie\0deleteMovie\0"
    "updateMovie\0filterList\0addToWatchList\0"
    "deleteFromWatchlist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  116,    2, 0x06,    1 /* Public */,
       5,    2,  121,    2, 0x06,    4 /* Public */,
       6,    1,  126,    2, 0x06,    7 /* Public */,
       8,    1,  129,    2, 0x06,    9 /* Public */,
       9,    0,  132,    2, 0x06,   11 /* Public */,
      10,    0,  133,    2, 0x06,   12 /* Public */,
      11,    0,  134,    2, 0x06,   13 /* Public */,
      12,    2,  135,    2, 0x06,   14 /* Public */,
      15,    2,  140,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    0,  145,    2, 0x0a,   20 /* Public */,
      17,    2,  146,    2, 0x0a,   21 /* Public */,
      18,    2,  151,    2, 0x0a,   24 /* Public */,
      19,    1,  156,    2, 0x0a,   27 /* Public */,
      20,    2,  159,    2, 0x0a,   29 /* Public */,
      21,    1,  164,    2, 0x0a,   32 /* Public */,
      22,    0,  167,    2, 0x0a,   34 /* Public */,
      23,    0,  168,    2, 0x0a,   35 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 14,    2,    2,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 14,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 14,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
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
        case 3: _t->filterListSignal((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 4: _t->addToWatchListSignal(); break;
        case 5: _t->deleteFromWatchlistSignal(); break;
        case 6: _t->dataBaseUpdate(); break;
        case 7: _t->moviesListUpdate((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<Movie>>>(_a[2]))); break;
        case 8: _t->watchListUpdate((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<Movie>>>(_a[2]))); break;
        case 9: _t->populateList(); break;
        case 10: _t->populateUserLists((*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<Movie>>>(_a[2]))); break;
        case 11: _t->addMovie((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 12: _t->deleteMovie((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 13: _t->updateMovie((*reinterpret_cast< std::add_pointer_t<std::vector<std::string>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[2]))); break;
        case 14: _t->filterList((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 15: _t->addToWatchList(); break;
        case 16: _t->deleteFromWatchlist(); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 13:
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
            using _t = void (GUI::*)(const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::filterListSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::addToWatchListSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::deleteFromWatchlistSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::dataBaseUpdate)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GUI::*)(QListWidget * , std::vector<Movie> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::moviesListUpdate)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GUI::*)(QListWidget * , std::vector<Movie> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI::watchListUpdate)) {
                *result = 8;
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
, QtPrivate::TypeAndForceComplete<GUI, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Movie>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Movie>, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<const std::vector<Movie> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<std::string>, std::false_type>, QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
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
void GUI::filterListSignal(const std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GUI::addToWatchListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GUI::deleteFromWatchlistSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void GUI::dataBaseUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GUI::moviesListUpdate(QListWidget * _t1, std::vector<Movie> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GUI::watchListUpdate(QListWidget * _t1, std::vector<Movie> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
