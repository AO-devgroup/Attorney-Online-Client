/****************************************************************************
** Meta object code from reading C++ file 'lobby.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lobby.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lobby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Lobby_t {
    QByteArrayData data[19];
    char stringdata0[358];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Lobby_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Lobby_t qt_meta_stringdata_Lobby = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Lobby"
QT_MOC_LITERAL(1, 6, 16), // "handle_ms_packet"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 20), // "handle_server_packet"
QT_MOC_LITERAL(4, 45, 25), // "ms_connection_established"
QT_MOC_LITERAL(5, 71, 20), // "ms_failed_to_connect"
QT_MOC_LITERAL(6, 92, 19), // "server_disconnected"
QT_MOC_LITERAL(7, 112, 18), // "on_refresh_pressed"
QT_MOC_LITERAL(8, 131, 19), // "on_refresh_released"
QT_MOC_LITERAL(9, 151, 19), // "on_addtofav_pressed"
QT_MOC_LITERAL(10, 171, 20), // "on_addtofav_released"
QT_MOC_LITERAL(11, 192, 18), // "on_connect_pressed"
QT_MOC_LITERAL(12, 211, 19), // "on_connect_released"
QT_MOC_LITERAL(13, 231, 24), // "on_publicservers_clicked"
QT_MOC_LITERAL(14, 256, 20), // "on_favorites_clicked"
QT_MOC_LITERAL(15, 277, 28), // "on_chatmessage_returnPressed"
QT_MOC_LITERAL(16, 306, 21), // "on_serverlist_clicked"
QT_MOC_LITERAL(17, 328, 5), // "index"
QT_MOC_LITERAL(18, 334, 23) // "on_favoritelist_clicked"

    },
    "Lobby\0handle_ms_packet\0\0handle_server_packet\0"
    "ms_connection_established\0"
    "ms_failed_to_connect\0server_disconnected\0"
    "on_refresh_pressed\0on_refresh_released\0"
    "on_addtofav_pressed\0on_addtofav_released\0"
    "on_connect_pressed\0on_connect_released\0"
    "on_publicservers_clicked\0on_favorites_clicked\0"
    "on_chatmessage_returnPressed\0"
    "on_serverlist_clicked\0index\0"
    "on_favoritelist_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Lobby[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    1,  108,    2, 0x08 /* Private */,
      18,    1,  111,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   17,
    QMetaType::Void, QMetaType::QModelIndex,   17,

       0        // eod
};

void Lobby::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Lobby *_t = static_cast<Lobby *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handle_ms_packet(); break;
        case 1: _t->handle_server_packet(); break;
        case 2: _t->ms_connection_established(); break;
        case 3: _t->ms_failed_to_connect(); break;
        case 4: _t->server_disconnected(); break;
        case 5: _t->on_refresh_pressed(); break;
        case 6: _t->on_refresh_released(); break;
        case 7: _t->on_addtofav_pressed(); break;
        case 8: _t->on_addtofav_released(); break;
        case 9: _t->on_connect_pressed(); break;
        case 10: _t->on_connect_released(); break;
        case 11: _t->on_publicservers_clicked(); break;
        case 12: _t->on_favorites_clicked(); break;
        case 13: _t->on_chatmessage_returnPressed(); break;
        case 14: _t->on_serverlist_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 15: _t->on_favoritelist_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Lobby::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Lobby.data,
      qt_meta_data_Lobby,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Lobby::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Lobby::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Lobby.stringdata0))
        return static_cast<void*>(const_cast< Lobby*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Lobby::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
