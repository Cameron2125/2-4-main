QT += core gui
QT += sql
QT += charts

QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcontactmanual.cpp \
    adminportal.cpp \
    contactedit.cpp \
    contactman.cpp \
    contactviewer.cpp \
    dbControl/dbcontrol.cpp \
    dpincentiveedit.cpp \
    DataRetrievalDemo/dataretrieval.cpp \
    edittaskincentivedialog.cpp \
    incentivemanager.cpp \
    incentiveviewer.cpp \
    login.cpp \
    main.cpp \
    organizerportal.cpp \
    promotionmanager.cpp \
    contactmanager.cpp \
    purchasedbadge.cpp \
    scoreboard.cpp \
    additionalinformation.cpp \
    signupdialog.cpp \
    viewcontacts.cpp \
    researcherportal.cpp \
    datagui.cpp \
    shop.cpp \
    DataAnalysisEngine/dataanalysis.cpp


#INCLUDEPATH += \
#    gtest \
#    gtest/googletest \
#    gtest/googletest/include \
#    gtest/googletest/include/gtest

HEADERS += \
    addcontactmanual.h \
    adminportal.h \
    contactedit.h \
    contactman.h \
    contactviewer.h \
    dbControl/dbcontrol.h \
    dpincentiveedit.h \
    DataRetrievalDemo/dataretrieval.h \
    edittaskincentivedialog.h \
    incentivemanager.h \
    incentiveviewer.h \
    login.h \
    organizerportal.h \
    promotionmanager.h \
    purchasedbadge.h \
    researcherportal.h \
    contactmanager.h \
    scoreboard.h \
    additionalinformation.h \
    signupdialog.h \
    viewcontacts.h \
    researcherportal.h \
    datagui.h \
    shop.h \
    DataAnalysisEngine/dataanalysis.h

FORMS += \
    addcontactmanual.ui \
    adminportal.ui \
    contactedit.ui \
    contactman.ui \
    contactviewer.ui \
    dpincentiveedit.ui \
    edittaskincentivedialog.ui \
    incentivemanager.ui \
    incentiveviewer.ui \
    login.ui \
    organizerportal.ui \
    promotionmanager.ui \
    purchasedbadge.ui \
    researcherportal.ui \
    scoreboard.ui \
    contactmanager.ui \
    additionalinformation.ui \
    viewcontacts.ui \
    DataRetrievalDemo/dataretrieval.ui \
    signupdialog.ui \
    shop.ui \
    datagui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

SUBDIRS += \
    dbControl/dbControl.pro \
    DataRetrievalDemo/DataRetrievalDemo.pro

#DISTFILES += \
#    ../../../../Downloads/badge1-removebg-preview.png \
#    ../../../../Downloads/badge2-removebg-preview.png \
#    ../../../../Downloads/badge3-removebg-preview.png \
#    ../../../../Downloads/badge4-removebg-preview.png \
#    ../../../../Downloads/badge5-removebg-preview.png \
#    ../../../../Downloads/badge6-removebg-preview.png \
#    ../../../../Downloads/badge7-removebg-preview.png
#gtest/googletest/src/gtest-all.cc \
