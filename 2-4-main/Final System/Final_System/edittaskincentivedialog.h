#ifndef EDITTASKINCENTIVEDIALOG_H
#define EDITTASKINCENTIVEDIALOG_H

#include <QDialog>
#include "./dbControl/dbcontrol.h"

class incentivePortal;

namespace Ui {
class TaskIncentiveEdit;
}

class TaskIncentiveEdit : public QDialog
{
    Q_OBJECT

/**
* @brief opens from incentivemanager. allows admin to
* edit data point incentive
*/
public:
    explicit TaskIncentiveEdit(QWidget *parent = nullptr);
    ~TaskIncentiveEdit();

    dbControl *db;
    QString user;

    /**
     * @brief insertDB: insert task incentive into database
     * @param task
     * @param pointVal
     */
    void insertDB(QString task, QString pointVal);

signals:
    /**
     * @brief editClosed: signal that edit should close and return
     * to incentivemanager
     * @param username
     * @param dbc
     */
    void editClosed(QString username, dbControl *dbc);

public slots:
    /**
     * @brief load: receive data from incentivemanager
     * @param username
     * @param dbc
     */
    void load(QString username, dbControl *dbc);

private slots:
    /**
     * @brief on_submit_button_clicked: submit new task incentive
     */
    void on_submit_button_clicked();

private:
    Ui::TaskIncentiveEdit *ui;
};

#endif // TaskIncentiveEdit_H
