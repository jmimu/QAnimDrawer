/****************************************************************************
** Meta object code from reading C++ file 'graphviewjm.h'
**
** Created: Sun Dec 6 11:20:32 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphviewjm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphviewjm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphViewJM[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphViewJM[] = {
    "GraphViewJM\0\0ask_shot()\0"
};

const QMetaObject GraphViewJM::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphViewJM,
      qt_meta_data_GraphViewJM, 0 }
};

const QMetaObject *GraphViewJM::metaObject() const
{
    return &staticMetaObject;
}

void *GraphViewJM::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphViewJM))
        return static_cast<void*>(const_cast< GraphViewJM*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphViewJM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ask_shot(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
