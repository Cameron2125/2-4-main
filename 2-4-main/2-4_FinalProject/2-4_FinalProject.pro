TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        contact.cpp \
        date.cpp \
        main.cpp

HEADERS += \
    contact.h \
    date.h \

TEMPLATE = subdirs
SUBDIRS += \
    AddInfo \
    ContactGroupAssign_Prototype \
        ContactGroupAssign_Prototype \
    ContactManager \
    Contact_Test \
    DataAnalysisEngine \
    DataAnalysisGUI \
    DataAnalysisEngine_Test \
        DataRetrievalDemo \
    Date_Test \
    Project \
    Scoreboard \
        UiNavigation_Prototype \
        dbControl \
    dbControl_Test \
    shop
