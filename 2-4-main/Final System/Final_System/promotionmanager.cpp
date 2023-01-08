#include "promotionmanager.h"
#include "ui_promotionmanager.h"

PromotionManager::PromotionManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PromotionManager)
{
    ui->setupUi(this);
    show();
}

PromotionManager::~PromotionManager()
{
    delete ui;
}

void PromotionManager::load(QString username, dbControl *dbc) {
    user = username;
    db = dbc;
    updateUserBox();
}

/**
 * @brief updateUserBox: when a user's role is
 * updated, process this update in database
 * and UI
 */
void PromotionManager::updateUserBox() {
    //get the id of the person who islogged in
    int id = db->loginId;
    QSqlQuery qry;

    //select every user EXCEPT the guy logged in (so that, say, an admin can't
    //demote himself to organizer or something crazy like that haha)
    qry.prepare("select * from Login where LID not in (:loginId)");
    qry.bindValue(":loginId", id);
    qry.exec();

    QStringList users;
    //iterate through query and add to combo box
    while (qry.next()) {
        QString user = qry.value(1).toString();
        QString role = qry.value(3).toString();
        QString entry = user + "," + role;

        users << entry;
    }
    //add list of users to user combo box as options for promotion
    QComboBox * combo = ui->user_box;
    combo->clear();
    combo->insertItems(0, users);
}

//validate and process update submission
void PromotionManager::on_submit_button_clicked()
{
    //get name & role of user to be promoted
    QString userAndRole = ui->user_box->currentText();
    QStringList items = userAndRole.split(QLatin1Char(','));
    QString user = items.at(0);
    QString role = items.at(1);

    //role to change user to
    QString newRole = ui->role_box->currentText();

    //login ID of user
    QString lID = db->getLIDFromUserName(user);

    //store user ID as variable
    QString id;

    //if user is actually getting promoted, proceed
    if (validPromotion()) {
        QSqlQuery qry;

        //delete user from their old table
        if (role == "Organizer") {
            qry.prepare("delete from Organizer where LID = :id");
            //get id before deletion
            id = db->getRIDFromLID(lID, "Organizer");
        }
        else if (role == "Researcher") {
            qry.prepare("delete from Researcher where LID = :id");
            id = db->getRIDFromLID(lID, "Researcher");
        }
        else if (role == "Admin") {
            qry.prepare("delete from Admin where LID = :id");
            id = db->getRIDFromLID(lID, "Admin");
        }
        qry.bindValue(":id", lID);
        qry.exec();

        //update role in login
        qry.prepare("update Login set role = :newRole where LID = :id");
        qry.bindValue(":newRole", newRole);
        qry.bindValue(":id", lID);
        qry.exec();

        //add user to their new table
        if (newRole == "Researcher") {
            qry.prepare("insert into Researcher values(:rid, :lid)");
            qry.bindValue(":rid", id);
            qry.bindValue(":lid", lID);
        }
        else if (newRole == "Admin") {
            qry.prepare("insert into Admin values(:rid, :lid)");
            qry.bindValue(":rid", id);
            qry.bindValue(":lid", lID);
        }
        qry.exec();
    }
    else {
        //show warning message
    }
    //reload user box
    updateUserBox();
}

bool PromotionManager::validPromotion() {
    //get name & role of user to be promoted
    QString userAndRole = ui->user_box->currentText();
    QStringList items = userAndRole.split(QLatin1Char(','));
    QString role = items.at(1);

    QString newRole = ui->role_box->currentText();
    if (role != newRole) {
        //don't allow demotion of admin/researcher to organizer
        if (newRole == "Organizer") {
            return false;
        }
        return true;
    }

    else {
        return false;
    }
}


void PromotionManager::on_back_button_clicked()
{
    emit back(user, db);
    hide();
}

