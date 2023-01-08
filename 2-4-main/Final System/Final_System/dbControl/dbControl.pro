TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT += core
QT += sql

SOURCES += \
        dbcontrol.cpp \
        main.cpp

HEADERS += \
    dbcontrol.h
