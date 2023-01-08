TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    ../contact.h \
    ../date.h \

SOURCES += \
    main.cpp \
    ../../gtest/googletest/src/gtest-all.cc \
    ../contact.cpp \
    ../date.cpp

INCLUDEPATH += ../../gtest \
 ../../gtest/googletest \
 ../../gtest/googletest/include \
 ../../gtest/googletest/include/gtest


