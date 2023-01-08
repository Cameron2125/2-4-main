TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        scoreboard.cpp \
        ../dbControl/dbcontrol.cpp

HEADERS += \
    scoreboard.h \
    ../dbControl/dbcontrol.h

QT += widgets
QT += sql

FORMS += \
    scoreboard.ui

RESOURCES += \
    pictures.qrc

DISTFILES += \
    ../../resources/Capture.PNG \
    ../../resources/leaderboard.PNG \
    ../../resources/textbg.PNG
