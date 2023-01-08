QT       += core gui
QT += core
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminportal.cpp \
    editdataptincentivedialog.cpp \
    edittaskincentivedialog.cpp \
    incentiveportal.cpp \
    main.cpp \
    researcherportal.cpp \
    uinavigation_prototype.cpp \
    ../dbControl/dbcontrol.cpp \
    volunteerrecruiterportal.cpp

HEADERS += \
    adminportal.h \
    editdataptincentivedialog.h \
    edittaskincentivedialog.h \
    incentiveportal.h \
    researcherportal.h \
    uinavigation_prototype.h \
    ../dbControl/dbcontrol.cpp \
    volunteerrecruiterportal.h

FORMS += \
    adminportal.ui \
    editdataptincentivedialog.ui \
    edittaskincentivedialog.ui \
    incentiveportal.ui \
    researcherportal.ui \
    uinavigation_prototype.ui \
    volunteerrecruiterportal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
