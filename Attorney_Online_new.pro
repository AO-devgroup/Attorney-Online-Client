#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T21:27:43
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = logo.ico

TARGET = Attorney_Online_new
TEMPLATE = app


SOURCES += \
    main.cpp \
    config_handler.cpp \
    lobby.cpp \
    error_handler.cpp \
    courtroom.cpp \
    character_handler.cpp \
    charicon.cpp \
    datatypes.cpp \
    network_handler.cpp \
    globals.cpp \
    charselect.cpp \
    emotes.cpp \
    emoteicon.cpp \
    file_handler.cpp

HEADERS  += \
    main.h \
    config_handler.h \
    lobby.h \
    error_handler.h \
    courtroom.h \
    character_handler.h \
    charicon.h \
    datatypes.h \
    network_handler.h \
    globals.h \
    charselect.h \
    emotes.h \
    emoteicon.h \
    file_handler.h

FORMS    += \
    lobby.ui \
    courtroom.ui

RESOURCES += \
    resources.qrc
