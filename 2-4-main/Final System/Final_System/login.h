#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QtSql>
#include <vector>
#include "adminportal.h"
#include "researcherportal.h"
#include "organizerportal.h"
#include "signupdialog.h"

//this path may change once final version becomes canon
#include "./dbControl/dbcontrol.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Login the login constructor
     * \param parent the parent widget
     */
    Login(QWidget *parent = nullptr);
    ~Login();

    //pulls from database to authenticate login
     dbControl *db = new dbControl("./resources/project_db.sqlite");
     /*!
      * \brief load loads the class from another window
      * \param dbc database object to be passed
      */
     void load(dbControl *dbc);
private slots:
     /*!
     * \brief on_login_button_clicked the login button that triggers
     * tests to see if credentials are valid
     */
    void on_login_button_clicked();

    /*!
     * \brief on_signUp_button_clicked sends user to signup screen
     */
    void on_signUp_button_clicked();

signals:
    //signal to send user to admin portal
    /*!
     * \brief toAdminPortal signal to send user to admin portal
     * \param username the username of the user
     * \param dbcc the database to be passed
     */
    void toAdminPortal(QString username, dbControl *dbcc);
    //signal to send user to researcher portal
    /*!
     * \brief toResearcherPortal signal to send user to researcher portal
     * \param username the username of the user
     * \param dbcc the database to be passed
     */
    void toResearcherPortal(QString username, dbControl *dbcc);
    //signal to send user to organizer portal
    /*!
     * \brief toOrganizerPortal signal to send user to organizer portal
     * \param username the username of the user
     * \param dbcc the database to be passed
     */
    void toOrganizerPortal(int i,dbControl *dbcc );




    //signal to send user to sign up
    /*!
     * \brief toSignUp signal to send user to sign up
     * \param dbcc the database to be passed
     */
    void toSignUp(dbControl *dbcc);

private:
    Ui::Login *ui;
    AdminPortal * admPortal;
    ResearcherPortal * resPortal;
    OrganizerPortal * orgPortal;
    SignUpDialog * signUp;

    /*!
     * \brief validUser checks that the user is in db and correct password
     * \return returns their roll if valid and NULL if not
     */
    QString validUser();
    /*!
     * \brief signUpMessage shows the signup messages
     */
    void signUpMessage();
};

#endif // LOGIN_H
