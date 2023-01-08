#ifndef ADMINPORTAL_H
#define ADMINPORTAL_H

#include <QDialog>
#include "incentiveportal.h"

namespace Ui {
class adminPortal;
}

class adminPortal : public QDialog
{
    Q_OBJECT

public:
    explicit adminPortal(QWidget *parent = nullptr);
    ~adminPortal();

    dbControl *db;

signals:
    void toIncentivePortal(dbControl *dbc);

public slots:
    void load(QString username, dbControl *dbc);

private slots:
    void on_setIncentive_button_clicked();

private:
    Ui::adminPortal *ui;
    incentivePortal * setIncentPortal;
};

#endif // ADMINPORTAL_H
