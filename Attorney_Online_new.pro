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
    networking.cpp \
    character_handler.cpp \
    charicon.cpp

HEADERS  += \
    main.h \
    config_handler.h \
    lobby.h \
    error_handler.h \
    courtroom.h \
    networking.h \
    character_handler.h \
    charicon.h

FORMS    += \
    lobby.ui \
    courtroom.ui

RESOURCES += \
    resources.qrc
