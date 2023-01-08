#include <iostream>
#include <QApplication>
#include <scoreboard.h>
#include "QString"
#include <QMainWindow>
#include <QObject>
#include <qlistwidget.h>
//#include <../dbControl/dbcontrol.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScoreBoard w;
    w.show();
    return a.exec();
}
