#include "uinavigation_prototype.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UiNavigation_Prototype w;
    w.show();
    return a.exec();
}
