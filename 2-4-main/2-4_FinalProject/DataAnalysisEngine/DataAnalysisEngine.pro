TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt

QT += core
QT += sql

SOURCES += \
        dataanalysis.cpp \
        main.cpp \
        ../contact.cpp \
        ../dbControl/dbcontrol.cpp

HEADERS += \
    dataanalysis.h \
    ../contact.h \
    ../dbControl/dbcontrol.h
