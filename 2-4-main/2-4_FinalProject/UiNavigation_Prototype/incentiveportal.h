#ifndef INCENTIVEPORTAL_H
#define INCENTIVEPORTAL_H

#include <QDialog>
#include "../dbControl/dbcontrol.h"
#include "editdataptincentivedialog.h"
#include "edittaskincentivedialog.h"

class editDataPtIncentiveDialog;
class editTaskIncentiveDialog;
namespace Ui {
class incentivePortal;
}

class incentivePortal : public QDialog
{
    Q_OBJECT

public:
    explicit incentivePortal(QWidget *parent = nullptr);
    ~incentivePortal();

    dbControl *db;
    void showDataPointIncentives();
    void showTaskIncentives();
    void deactivatePage();
    void activatePage();

signals:
    void toDataPtEditMenu(dbControl *dbc);
    void toTaskEditMenu(dbControl *dbc);

public slots:
    void load(dbControl *dbc);

private slots:
    void on_removeDataPt_button_clicked();

    void on_removeTask_button_clicked();

    void on_addDataPt_button_clicked();

    void on_addTask_button_clicked();

private:
    Ui::incentivePortal *ui;
    editDataPtIncentiveDialog * editDPIncentive;
    editTaskIncentiveDialog * editTaskIncentive;
};

#endif // INCENTIVEPORTAL_H
