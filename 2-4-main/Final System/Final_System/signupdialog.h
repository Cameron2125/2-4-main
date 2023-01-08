#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "dbControl/dbcontrol.h"

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief SignUpDialog the constructor for the sign up dialog
     * \param parent
     */
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();
    /*!
     * \brief load method to load gui from another window
     * \param dbc the database object passed along
     */
    void load(dbControl *dbc);

signals:
    /*!
     * \brief signUpClosed
     * the signal for when the sign up is closed
     * \param dbc
     * the database object passed
     */
    void signUpClosed(dbControl *dbc);

private slots:
    /*!
     * \brief on_submit_button_clicked
     * the signal for when the submit button has been clicked
     */
    void on_submit_button_clicked();
    /*!
     * \brief success
     * signal for if the account signed up sucessfully
     * \param username
     * the username of the account
     * \return
     */
    bool success(QString username);

private:
    Ui::SignUpDialog *ui;

    //databse used
    dbControl *db;
};

#endif // SIGNUPDIALOG_H
