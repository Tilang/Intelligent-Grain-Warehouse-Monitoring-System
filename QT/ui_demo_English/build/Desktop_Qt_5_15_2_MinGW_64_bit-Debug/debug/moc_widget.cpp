/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[24];
    char stringdata0[322];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 12), // "requestToken"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 15), // "onTokenReceived"
QT_MOC_LITERAL(4, 37, 14), // "sendCommandAPI"
QT_MOC_LITERAL(5, 52, 11), // "commandName"
QT_MOC_LITERAL(6, 64, 5), // "value"
QT_MOC_LITERAL(7, 70, 19), // "sendCommandViaToken"
QT_MOC_LITERAL(8, 90, 13), // "onCommandSent"
QT_MOC_LITERAL(9, 104, 17), // "fetchDeviceStatus"
QT_MOC_LITERAL(10, 122, 22), // "onDeviceStatusReceived"
QT_MOC_LITERAL(11, 145, 18), // "updateDeviceStatus"
QT_MOC_LITERAL(12, 164, 10), // "properties"
QT_MOC_LITERAL(13, 175, 20), // "updateControlButtons"
QT_MOC_LITERAL(14, 196, 11), // "sendCommand"
QT_MOC_LITERAL(15, 208, 13), // "deviceService"
QT_MOC_LITERAL(16, 222, 15), // "toggleAutoMode1"
QT_MOC_LITERAL(17, 238, 15), // "toggleAutoMode2"
QT_MOC_LITERAL(18, 254, 21), // "autoControlWarehouse1"
QT_MOC_LITERAL(19, 276, 4), // "temp"
QT_MOC_LITERAL(20, 281, 8), // "humidity"
QT_MOC_LITERAL(21, 290, 5), // "light"
QT_MOC_LITERAL(22, 296, 21), // "autoControlWarehouse2"
QT_MOC_LITERAL(23, 318, 3) // "co2"

    },
    "Widget\0requestToken\0\0onTokenReceived\0"
    "sendCommandAPI\0commandName\0value\0"
    "sendCommandViaToken\0onCommandSent\0"
    "fetchDeviceStatus\0onDeviceStatusReceived\0"
    "updateDeviceStatus\0properties\0"
    "updateControlButtons\0sendCommand\0"
    "deviceService\0toggleAutoMode1\0"
    "toggleAutoMode2\0autoControlWarehouse1\0"
    "temp\0humidity\0light\0autoControlWarehouse2\0"
    "co2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    2,   86,    2, 0x08 /* Private */,
       7,    2,   91,    2, 0x08 /* Private */,
       8,    0,   96,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    1,   99,    2, 0x08 /* Private */,
      13,    0,  102,    2, 0x08 /* Private */,
      14,    1,  103,    2, 0x08 /* Private */,
      16,    0,  106,    2, 0x08 /* Private */,
      17,    0,  107,    2, 0x08 /* Private */,
      18,    3,  108,    2, 0x08 /* Private */,
      22,    4,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   19,   20,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   19,   20,   21,   23,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestToken(); break;
        case 1: _t->onTokenReceived(); break;
        case 2: _t->sendCommandAPI((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->sendCommandViaToken((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onCommandSent(); break;
        case 5: _t->fetchDeviceStatus(); break;
        case 6: _t->onDeviceStatusReceived(); break;
        case 7: _t->updateDeviceStatus((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 8: _t->updateControlButtons(); break;
        case 9: _t->sendCommand((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->toggleAutoMode1(); break;
        case 11: _t->toggleAutoMode2(); break;
        case 12: _t->autoControlWarehouse1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->autoControlWarehouse2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
