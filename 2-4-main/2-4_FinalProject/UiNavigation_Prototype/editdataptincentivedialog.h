#ifndef EDITDATAPTINCENTIVEDIALOG_H
#define EDITDATAPTINCENTIVEDIALOG_H

#include <QDialog>
#include "../dbControl/dbcontrol.h"
#include "incentiveportal.h"

class incentivePortal;

namespace Ui {
class editDataPtIncentiveDialog;
}

class editDataPtIncentiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDataPtIncentiveDialog(QWidget *parent = nullptr);
    ~editDataPtIncentiveDialog();

    dbControl *db;

    void insertDB(QString dataPt, QString pointVal);

signals:
    void editClosed(dbControl *dbc);

public slots:
    void load(dbControl *dbc);

private slots:
    void on_submit_button_clicked();

private:
    Ui::editDataPtIncentiveDialog *ui;
};

#endif // EDITDATAPTINCENTIVEDIALOG_H
