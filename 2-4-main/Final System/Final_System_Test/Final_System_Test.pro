TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt
QT += charts
QT += core
QT += sql
QT +=  widgets

SOURCES += main.cpp \
    additionalinformation_test.cpp \
    dataanalysisengine_test.cpp \
    dbcontrol_test.cpp \
    ../Final_System/datagui.cpp \
    dataanalysisTest.cpp

LIBS += -pthread

SOURCES += ../Final_System/gtest/googletest/src/gtest-all.cc

INCLUDEPATH += ../Final_System/gtest \
               ../Final_System/gtest/googletest \
               ../Final_System/gtest/googletest/include \
               ../Final_System/gtest/googletest/include/gtest

SOURCES += ../Final_System/DataAnalysisEngine/dataanalysis.cpp
HEADERS += ../Final_System/DataAnalysisEngine/dataanalysis.h \
    ../Final_System/datagui.h

SOURCES += ../Final_System/dbControl/dbcontrol.cpp
HEADERS += ../Final_System/dbControl/dbcontrol.h

FORMS += \
    ../Final_System/datagui.ui
SOURCES += ../Final_System/additionalInformation.cpp
HEADERS += ../Final_System/additionalInformation.h
FORMS += ../Final_System/additionalInformation.ui
