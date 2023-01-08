#include "login.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    //create the QApplication object
    QApplication a(argc, argv);
    //create and show the Login widget
    Login w;
    w.show();
    //set the icon for the window
    QIcon icon (":/images/resources/CS3M_logo.png");
    a.setWindowIcon(icon);
    return a.exec();
}
