#include "dataretrieval.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataRetrieval w;
    w.show();
    return a.exec();

}
