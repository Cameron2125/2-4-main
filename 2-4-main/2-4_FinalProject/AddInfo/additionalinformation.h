#ifndef ADDITIONALINFORMATION_H
#define ADDITIONALINFORMATION_H

#include <QMainWindow>
#include <QListWidget>
#include <vector>
#include "../contact.h"
#include "../date.h"
#include "../dbControl/dbcontrol.h"


QT_BEGIN_NAMESPACE
namespace Ui { class additionalInformation; }
QT_END_NAMESPACE

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
     * \brief on_ftofContacts_itemPressed
     * \param item
     * This method marks the selected contact as the update contact
     * when the contact is selected from the friend to friend contact
     * list.
     */
    void on_ftofContacts_itemPressed(QListWidgetItem *item);

    /*!
     * \brief on_allContacts_itemPressed
     * \param item
     * This method marks the selected contact as the update contact
     * when the contact is selected from the entire contact list.
     */
    void on_allContacts_itemPressed(QListWidgetItem *item);

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

    void on_yesBox_pressed();

    void on_noBox_pressed();

    void on_notSureBox_pressed();

private:
    Ui::additionalInformation *ui;

    dbControl db;

    //array of contacts, will come from db
    std::vector<Contact> newContacts;
    //the contact that is being changed
    std::string update;
    //vector index of contact that is being change will become contact id
    int updateIndex;

    std::string recDate;
    int success;
    int length;
    int tlength;
    QString response;
    QString additionalInfo;


};
#endif // ADDITIONALINFORMATION_H
