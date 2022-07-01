/****************************************************************************
** Meta object code from reading C++ file 'playwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayWindow_t {
    QByteArrayData data[11];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayWindow_t qt_meta_stringdata_PlayWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlayWindow"
QT_MOC_LITERAL(1, 11, 14), // "onTimer_attack"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "onTimer_blockmove"
QT_MOC_LITERAL(4, 45, 19), // "onTimer_blockbirth1"
QT_MOC_LITERAL(5, 65, 19), // "onTimer_blockbirth2"
QT_MOC_LITERAL(6, 85, 19), // "onTimer_blockbirth3"
QT_MOC_LITERAL(7, 105, 20), // "onTimer_monsterbirth"
QT_MOC_LITERAL(8, 126, 18), // "onTimer_changemode"
QT_MOC_LITERAL(9, 145, 16), // "onTimer_backmove"
QT_MOC_LITERAL(10, 162, 11) // "onTimer_out"

    },
    "PlayWindow\0onTimer_attack\0\0onTimer_blockmove\0"
    "onTimer_blockbirth1\0onTimer_blockbirth2\0"
    "onTimer_blockbirth3\0onTimer_monsterbirth\0"
    "onTimer_changemode\0onTimer_backmove\0"
    "onTimer_out"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayWindow *_t = static_cast<PlayWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTimer_attack(); break;
        case 1: _t->onTimer_blockmove(); break;
        case 2: _t->onTimer_blockbirth1(); break;
        case 3: _t->onTimer_blockbirth2(); break;
        case 4: _t->onTimer_blockbirth3(); break;
        case 5: _t->onTimer_monsterbirth(); break;
        case 6: _t->onTimer_changemode(); break;
        case 7: _t->onTimer_backmove(); break;
        case 8: _t->onTimer_out(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PlayWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayWindow.data,
      qt_meta_data_PlayWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayWindow.stringdata0))
        return static_cast<void*>(const_cast< PlayWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
