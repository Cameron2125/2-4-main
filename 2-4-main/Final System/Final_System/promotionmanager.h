#ifndef PROMOTIONMANAGER_H
#define PROMOTIONMANAGER_H

#include <QMainWindow>
#include "./dbControl/dbcontrol.h"

namespace Ui {
class PromotionManager;
}

class PromotionManager : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief PromotionManager constructor for Promotion Manager
     * \param parent the parent widget
     */
    explicit PromotionManager(QWidget *parent = nullptr);
    ~PromotionManager();

    QString user;

public slots:
    /*!
     * \brief load method to load class from another window
     * \param username the username of the user
     * \param dbc the database to be passed
     */
    void load(QString username, dbControl *dbc);

signals:
    /*!
     * \brief editClosed signal for closure of window
     * \param dbc the database to be passed
     */
    void editClosed(dbControl *dbc);
    /*!
     * \brief back signal for back button
     * \param username the username of user
     * \param dbc the database to be passed
     */
    void back(QString username, dbControl *dbc);

private slots:
    /*!
     * \brief on_submit_button_clicked the button to submit
     * promoted user
     */
    void on_submit_button_clicked();

    /*!
     * \brief on_back_button_clicked the back button
     */
    void on_back_button_clicked();

private:
    Ui::PromotionManager *ui;
    dbControl *db;

    /*!
     * \brief updateUserBox updates the list of users who can be promoted
     */
    void updateUserBox();
    /*!
     * \brief validPromotion Method to make sure promotion/demotion is allowed
     * \return true if it is a valid change false otherwise
     */
    bool validPromotion();
};

#endif // PROMOTIONMANAGER_H
