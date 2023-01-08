#include "contactmanager.h"
#include <../dbControl/dbcontrol.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ContactManager w;

    qDebug() << "App path : " << qApp->applicationDirPath();

    // Create a dbControl
    dbControl* db = new dbControl();
    w.load(db, 5);

    // Launches dialog
    w.exec();

    return a.exec();
}
