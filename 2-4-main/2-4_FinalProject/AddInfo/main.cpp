#include "additionalinformation.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    additionalInformation w;
    w.show();

    return a.exec();
}
