TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt

QT += core
QT += sql

SOURCES += \
        main.cpp

LIBS += -pthread

SOURCES += ../../gtest/googletest/src/gtest-all.cc

INCLUDEPATH += ../../gtest \
 ../../gtest/googletest \
 ../../gtest/googletest/include \
 ../../gtest/googletest/include/gtest

HEADERS += ../DataAnalysisEngine/dataanalysis.h
SOURCES += ../DataAnalysisEngine/dataanalysis.cpp

HEADERS += ../contact.h
SOURCES += ../contact.cpp

HEADERS += ../dbControl/dbcontrol.h
SOURCES += ../dbControl/dbcontrol.cpp
