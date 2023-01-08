#ifndef ORGANIZERPORTAL_H
#define ORGANIZERPORTAL_H

#include <QMainWindow>
#include <vector>
#include "dbControl/dbcontrol.h"
#include "scoreboard.h"
#include "additionalinformation.h"
#include "contactman.h"
#include "shop.h"
#include "incentiveviewer.h"


namespace Ui {
class OrganizerPortal;
}

class OrganizerPortal : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief OrganizerPortal The constructor for Organizer portal
     * \param parent the paraent widget
     */
    explicit OrganizerPortal(QWidget *parent = nullptr);
    ~OrganizerPortal();
    /*!
     * \brief load laods the current class from another window
     * \param vid the ID of the Organizer
     * \param t the database to be passed
     */
    void load(int vid, dbControl *t);
    /*!
     * \brief splitString splits the list of strings according to a delimiter
     * \param list the string list
     * \param seperator the delimiter
     * \return
     * vector of indivual strings without the delimiter
     */
    std::vector<std::string>  splitString(std::string list, std::string seperator);
    /*!
     * \brief rankDisplay displays the rank badge according to score
     * \param id id of the user
     */
    void rankDisplay(int id);
    /*!
     * \brief shopBadges displays the user's purchased badges
     * \param id the id of the user
     */
    void shopBadges(int id);
    /*!
     * \brief friendToFriendContacts displays list of contacts needed
     * to be contacted
     * \param id the id of the user
     */
    void friendToFriendContacts(int id);
    /*!
     * \brief clearLayout clears the display of contact names
     */
    void clearLayout();


private slots:
    void on_Scoreboard_clicked();

    void on_ContactManager_clicked();

    void on_addinfo_clicked();

    void on_seeIncent_pressed();

    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);

signals:
    void toOrganizerPortal(int i,dbControl *dbc);
    void toadditionalInformationPortal(int i,dbControl *dbc);
    void toContactManagerPortal(int i, dbControl *dbc);
    void toShop( int i, dbControl *dbc);


    void toincentiveViewer(int i, dbControl *dbc);



private:
    Ui::OrganizerPortal *ui;
    dbControl *db;
    ScoreBoard *board;
    additionalInformation *add;
    contactman *manage;
    IncentiveViewer *incent;
    Shop *shop;
    std::vector<QLabel*> badges;
    int vids;
    std::vector<QLabel*> ftfclabels;



};

#endif // ORGANIZERPORTAL_H
