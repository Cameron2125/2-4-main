#ifndef EDITTASKINCENTIVEDIALOG_H
#define EDITTASKINCENTIVEDIALOG_H

#include <QDialog>
#include "../dbControl/dbcontrol.h"
#include "incentiveportal.h"

class incentivePortal;

namespace Ui {
class editTaskIncentiveDialog;
}

class editTaskIncentiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editTaskIncentiveDialog(QWidget *parent = nullptr);
    ~editTaskIncentiveDialog();

    dbControl *db;

    void insertDB(QString task, QString pointVal);

signals:
    void editClosed(dbControl *dbc);

public slots:
    void load(dbControl *dbc);

private slots:
    void on_submit_button_clicked();

private:
    Ui::editTaskIncentiveDialog *ui;
};

#endif // EDITTASKINCENTIVEDIALOG_H
