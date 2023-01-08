#ifndef CONTACTATTEMPTS_H
#define CONTACTATTEMPTS_H

#include <QDialog>
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "QString"
#include <QMainWindow>
#include <QObject>

#include <qlistwidget.h>
#include <../dbControl/dbcontrol.h>

namespace Ui {
class ContactAttempts;
}

class ContactAttempts : public QDialog
{
    Q_OBJECT

public:
    explicit ContactAttempts(QWidget *parent = nullptr);
    void load(QString ids,dbControl dBases);
    ~ContactAttempts();

private:
    Ui::ContactAttempts *ui;
};

#endif // CONTACTATTEMPTS_H
