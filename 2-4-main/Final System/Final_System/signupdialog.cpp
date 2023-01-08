#include "signupdialog.h"
#include "ui_signupdialog.h"

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    show();
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::load(dbControl *dbc) {
    db = dbc;
}

/**
 * @brief on_submit_button_clicked: this should
 * 1.) validate all fields filled out properly
 * 2.) write new login info to db (both login table and organizer table)
 */
void SignUpDialog::on_submit_button_clicked()
{
    QString fName = ui->fName_edit->text();
    QString lName = ui->lName_edit->text();
    QString email = ui->email_edit->text();
    QString uName = ui->uName_edit->text();
    QString pWord = ui->pword_edit->text();
    QString confirm = ui->confirm_edit->text();

    //ensure every field has some text
    if (fName != "" && lName != "" && email != "" && uName != "" && pWord != "" && confirm != ""
            && pWord == confirm) {
        QSqlQuery qry;

        int newId = db->getMaxValue("vid", "Organizer") + 1;
        //update login table with new user
        qry.prepare("insert into Login values(:id, :uName, :pWord, :role, :email)");
        qry.bindValue(":id", newId);
        qry.bindValue(":uName", uName);
        qry.bindValue(":pWord", pWord);
        //note that new users are Organizer by default
        qry.bindValue(":role", "Organizer");
        qry.bindValue(":email", email);
        qry.exec();

        //update organizer table with new user
        QString fullName = fName + " " + lName;
        //schema: vid name age location gender ethnicity education occupation points lid
        qry.prepare("insert into Organizer values(:vid, :name, null, null, null, null, null, null, 0, :lid, '0')");
        qry.bindValue(":vid", newId);
        qry.bindValue(":name", fullName);
        qry.bindValue(":lid", newId);
        if(!qry.exec()) {
            QMessageBox::warning(this, "Database Error", qry.lastError().text());
        }
        emit signUpClosed(db);
        hide();

        if (success(uName)) {
            QMessageBox::information(this, "Sign Up", "Account successfully created.");
        }
        else {
            QMessageBox::information(this, "Sign Up", "Account creation failed. Your username may already be taken.");
        }
    }
    else {
        QMessageBox::information(this, "Sign Up", "Make sure passwords match, and all fields are filled out.");
    }
}

bool SignUpDialog::success(QString username) {
    QSqlQuery qry;
    qry.prepare("select * from Login where Username = :user");
    qry.bindValue(":user", username);
    qry.exec();

    if (qry.next()) {
        return true;
    }
    return false;
}

