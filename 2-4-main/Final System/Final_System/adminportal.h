#ifndef ADMINPORTAL_H
#define ADMINPORTAL_H

#include <QMainWindow>
#include "./dbControl/dbcontrol.h"
#include "incentivemanager.h"
#include "contactviewer.h"
#include "promotionmanager.h"

namespace Ui {
class AdminPortal;
}

/**
 * @brief Admin page displaying possible admin actions
 */
class AdminPortal : public QMainWindow
{
    Q_OBJECT

public:
    /** constructor */
    explicit AdminPortal(QWidget *parent = nullptr);
    ~AdminPortal();

    dbControl *db;
    QString user;

signals:
    /**
     * @brief toIncentivesManager: signal to send user to incentive manager
     * and pass data along
     * @param username
     * @param dbc
     */
    void toIncentivesManager(QString username, dbControl *dbc);

    /**
     * @brief toContactViewer: signal to send user to incentive manager
     * and pass data along
     * @param username
     * @param dbc
     */
    void toContactViewer(QString username, dbControl *dbc);

    /**
     * @brief toPromotionManager: signal to send user to promotion manager
     * and pass data alogn
     * @param username
     * @param dbc
     */
    void toPromotionManager(QString username, dbControl *dbc);

public slots:
    /**
     * @brief load: get data from previous page
     * @param username
     * @param dbc
     */
    void load(QString username, dbControl *dbc);

private slots:
    /**
     * @brief on_incentives_button_clicked: send user to incentive manager
     */
    void on_incentives_button_clicked();

    /**
     * @brief on_viewContacts_button_clicked: send user to contact viewer
     */
    void on_viewContacts_button_clicked();

    /**
     * @brief on_promote_button_clicked: send user to promotion page
     */
    void on_promote_button_clicked();

private:
    Ui::AdminPortal *ui;
    IncentiveManager * incManager;
    ContactViewer * cv;
    PromotionManager * promo;
};

#endif // ADMINPORTAL_H
