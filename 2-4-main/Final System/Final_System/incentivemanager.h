#ifndef INCENTIVEMANAGER_H
#define INCENTIVEMANAGER_H

#include <QMainWindow>
#include "./dbControl/dbcontrol.h"
#include "dpincentiveedit.h"
#include "edittaskincentivedialog.h"

namespace Ui {
class IncentiveManager;
}

/**
 * @brief menu for admin to manage existing incentives in system
 */
class IncentiveManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit IncentiveManager(QWidget *parent = nullptr);
    ~IncentiveManager();

    dbControl *db;
    QString user;

    /**
     * @brief showDataPointIncentives: get dp incentives from db and display them
     */
    void showDataPointIncentives();

    /**
     * @brief showTaskIncentives: get task incentives from db and display them
     */
    void showTaskIncentives();

public slots:
    /**
     * @brief load: receive data from adminportal
     * @param username
     * @param dbc
     */
    void load(QString username, dbControl *dbc);

signals:
    /**
     * @brief toDataPtEditMenu: signal to go to data point incentive
     * edit menu
     * @param username
     * @param dbc
     */
    void toDataPtEditMenu(QString username, dbControl *dbc);

    /**
     * @brief toTaskEditMenu: signal to go to task incentive edit menu
     * @param username
     * @param dbc
     */
    void toTaskEditMenu(QString username, dbControl *dbc);

    /**
     * @brief back: signal to go back to admin portal
     * @param user
     * @param dbc
     */
    void back(QString user, dbControl *dbc);

private slots:
    /**
     * @brief on_removeDataPt_button_clicked: remove selected data point incent
     */
    void on_removeDataPt_button_clicked();

    /**
     * @brief on_addDataPt_button_clicked: open dialog to add new data point incent
     */
    void on_addDataPt_button_clicked();

    /**
     * @brief on_removeTask_button_clicked: remove selected task incent
     */
    void on_removeTask_button_clicked();

    /**
     * @brief on_addTask_button_clicked: open dialog to add new task incent
     */
    void on_addTask_button_clicked();

    /**
     * @brief on_back_button_clicked: emit signal to go back to admin portal
     */
    void on_back_button_clicked();

private:
    Ui::IncentiveManager *ui;
    DPIncentiveEdit * dpInc;
    TaskIncentiveEdit * taskInc;

    //AdminPortal * adm;
};

#endif // INCENTIVEMANAGER_H
