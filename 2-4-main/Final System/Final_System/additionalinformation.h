#ifndef ADDITIONALINFORMATION_H
#define ADDITIONALINFORMATION_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <QCloseEvent>
#include "./dbControl/dbcontrol.h"


QT_BEGIN_NAMESPACE
namespace Ui { class additionalInformation; }
QT_END_NAMESPACE

/**
 * @brief Allows organizer to add recruitment attempt
 */
class additionalInformation : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief additionalInformation
     * \param parent
     * This is the base constructor for the additional information widget.
     * This will setup the widget when called.
     */
    additionalInformation(QWidget *parent = nullptr);
    ~additionalInformation();


    /*!
     * \brief setContactGroups
     * \param newContact
     * This method separates the contacts between friend to friend
     * contacts and general contacts and assigns them to the right
     * display.
     */
    void setContactGroups();

    /*!
     * \brief load
     * \param id
     * \param t
     * This method loads the transfered data from the organizer
     * portal page.
     */
    void load(int id, dbControl *t);

    /*!
     * \brief validDate
     * \param day
     * \param month
     * \param year
     * \return if the date is valid
     * This method checks if the date entered is a correct date.
     */
    bool validDate(int day, int month, int year);

    QString getCID(QString name, QString VID);

    QString getAttempts(QString id);

private slots:
    /*!
     * \brief on_addAttemptBut_pressed
     * This method sends the volunteer recruiter to the add
     * recruitment attempt screen.
     */
    void on_addAttemptBut_pressed();

    /*!
     * \brief on_updateStatusBut_pressed
     * This method sends the volunteer recruiter to the update
     * volunteering status screen.
     */
    void on_updateStatusBut_pressed();

    /*!
     * \brief on_return1_pressed
     * This method sends the volunteer recruiter back to the main
     * screen from the recruitment attempt screen where they can
     * select another action.
     */
    void on_return1_pressed();

    /*!
     * \brief on_return2_pressed
     * This method sends the volunteer recruiter back to the main
     * screen from the volunteering status screen where they can
     * select another action.
     */
    void on_return2_pressed();

    /*!
     * \brief on_addAttemptBut_2_pressed
     * This method adds a recruitment attempt date to the selected
     * contact when pressed.
     */
    void on_addAttemptBut_2_pressed();

    /*!
     * \brief on_notActiveBut_pressed
     * This method sets the selected contact as a nonactive volunteer.
     */
    void on_notActiveBut_pressed();

    /*!
     * \brief on_activeBut_pressed
     * This method sets the selected contact as an active volunteer.
     */
    void on_activeBut_pressed();

    /*!
     * \brief on_allContacts_pressed
     * \param index
     * This method assigns the contact pressed into the update contact
     * from the table.
     */
    void on_allContacts_pressed(const QModelIndex &index);

    /*!
     * \brief on_ftofContacts_pressed
     * \param index
     * This method assigns the contact pressed from the friend to
     * friend contact table to the update contact.
     */
    void on_ftofContacts_pressed(const QModelIndex &index);

    /*!
     * \brief on_yesBox_pressed
     * Assigns the success int to 1 when yes is pressed.
     */
    void on_yesBox_pressed();

    /*!
     * \brief on_noBox_pressed
     * Assigns the success int to 0 when no is pressed.
     */
    void on_noBox_pressed();

    /*!
     * \brief on_notSureBox_pressed
     * Assigns the success int to 2 when not sure is pressed.
     */
    void on_notSureBox_pressed();

    /*!
     * \brief on_closeAddInfoBut_pressed
     * This returns the system to the organizer portal.
     */
    void on_closeAddInfoBut_pressed();

    /*!
     * \brief close
     * This is used to close the add info portal.
     */
    void close();

    /*!
     * \brief closeEvent
     * \param event
     * This closes the addinfo portal and saves all the data.
     */
    void closeEvent(QCloseEvent * event);

signals:
    /*!
     * \brief editClosed
     * \param vid
     * \param db
     * Used for closing add info.
     */
    void editClosed(int vid, dbControl *db);

private:
    Ui::additionalInformation *ui;

    //dbControl of system that is passed along to the portal
    dbControl *db;

    //the name of the contact that is being changed
    std::string update;

    //vector index of contact that is being change will become contact id
    int updateIndex;

    //Wether or not the attempt was a success
    int success;

    //length of the conversation
    int length;
    int tlength;

    //response from recruitment attempt
    QString response;
    QString additionalInfo;

    //Vid of organizer
    int VID;

};
#endif // ADDITIONALINFORMATION_H
