#include <iostream>
#include <QApplication>
#include "gtest.h"
#include <QApplication>

using namespace std;

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
     QApplication a(argc, argv);
    return RUN_ALL_TESTS();

}
