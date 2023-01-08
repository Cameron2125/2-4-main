#ifndef DPINCENTIVEEDIT_H
#define DPINCENTIVEEDIT_H

#include <QDialog>
#include <QMessageBox>
#include "./dbControl/dbcontrol.h"

namespace Ui {
class DPIncentiveEdit;
}

/**
 * @brief opens from incentivemanager. allows admin to
 * edit data point incentive
 */
class DPIncentiveEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DPIncentiveEdit(QWidget *parent = nullptr);
    ~DPIncentiveEdit();

    QString user;


signals:
    /**
     * @brief editClosed: signal saying that edit has been closed
     * and to return to incentivemanager
     * @param user
     * @param dbc
     */
    void editClosed(QString user, dbControl *dbc);

public slots:
    /**
     * @brief load: receive data from incentivemanager
     * @param username
     * @param dbc
     */
    void load(QString username, dbControl *dbc);

private slots:
    /**
     * @brief on_submit_button_clicked: submit changes
     */
    void on_submit_button_clicked();

private:
    Ui::DPIncentiveEdit *ui;
    dbControl *db;
};

#endif // DPINCENTIVEEDIT_H
