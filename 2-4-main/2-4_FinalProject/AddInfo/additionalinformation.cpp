#include "additionalinformation.h"
#include "ui_additionalinformation.h"

#include <QMessageBox>
#include <string>

////////////////////////////////////////////////////////
/// Constructors & Destructors
////////////////////////////////////////////////////////
additionalInformation::additionalInformation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::additionalInformation)
{
    ui->setupUi(this);
    db.openDB();
    tlength = db.getTableLength("Recruitment_Attempts");
    std::cout << tlength << std::endl;
}

additionalInformation::~additionalInformation()
{
    delete ui;
    db.closeDB();
}


////////////////////////////////////////////////////////
/// Screen Change
////////////////////////////////////////////////////////
void additionalInformation::on_addAttemptBut_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);  //changes stack widget
}

void additionalInformation::on_updateStatusBut_pressed()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void additionalInformation::on_return1_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void additionalInformation::on_return2_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}


////////////////////////////////////////////////////////
/// List Widget Control
////////////////////////////////////////////////////////
void additionalInformation::setContactGroups()
{
    QListWidget *ftofcontact_list = ui->ftofContacts;
    QListWidget *contact_list = ui -> allContacts;
    QString getftofNames = "select Name from Contacts where Contact_Type = 1;";
    QSqlQuery qry = db.runQuery(getftofNames);

    while (qry.next()) {
        QString name = qry.value(0).toString();
        new QListWidgetItem(name, ftofcontact_list);
    }

    QString getNames = "select Name from Contacts;";
    QSqlQuery qry2 = db.runQuery(getNames);

    while (qry2.next()) {
        QString name = qry2.value(0).toString();
        new QListWidgetItem(name, contact_list);
    }
}

void additionalInformation::on_ftofContacts_itemPressed(QListWidgetItem *item)
{
    QString name = item->text();
    update = name.toStdString();
}

void additionalInformation::on_allContacts_itemPressed(QListWidgetItem *item)
{
    QString name = item->text();
    update = name.toStdString();
}


////////////////////////////////////////////////////////
/// Update Contacts
////////////////////////////////////////////////////////
void additionalInformation::on_addAttemptBut_2_pressed()
{
    QString updateName = QString::fromStdString(update);

    int dayDate = ui->day->value();
    int monthDate = ui->month->value();
    int yearDate = ui->year->value();

    int hours = ui->hrSpin->value();
    int mins = ui->minSpin->value();

    length = 60 * hours + mins;
    QString lengthq = QString::number(length);

    response = ui->resText->toPlainText();

    additionalInfo = ui->addInfoLine->text();

    tlength++;
    QString id = QString::number(tlength);

    QString successq = QString::number(success);

    Date date;

    QString dateq;
    date.setDate(monthDate, dayDate, yearDate);

    //Only updates if date is valid
    if(date.validateDate(monthDate, dayDate, yearDate)){
        std::string dateString = std::to_string(dayDate) + std::to_string(monthDate) + std::to_string(yearDate);
        dateq = QString::fromStdString(dateString);
    }

    QSqlQuery q;
    q.prepare("insert into Recruitment_Attempts (Contact_Number, Recruitment_Attempt, Date, Success, Length, Response, Additional_Info)"
              "values(:number, :attempt, :dates, :success, :length, :response, :addinfo)");
    q.bindValue(":number", id);
    q.bindValue(":attempt", updateName);
    q.bindValue(":dates", dateq);
    q.bindValue(":success", successq);
    q.bindValue(":length", lengthq);
    q.bindValue(":response", response);
    q.bindValue(":addifo", additionalInfo);

    if(!q.exec()){
        std::cout<< "Query doesn't work" << std::endl;
    }

}

void additionalInformation::on_notActiveBut_pressed()
{
    QSqlQuery q;
    QString updateName = QString::fromStdString(update);
    q.prepare("update Contacts set Contact_Status = 0 where Name = :name");
    q.bindValue(":name", updateName);
    if(!q.exec()){
        std::cout<< "Query doesn't work" << std::endl;
    }
    QString message = updateName + " has been updated.";
    QMessageBox::about(this, "Confirmation", message);
}

void additionalInformation::on_activeBut_pressed()
{
    QSqlQuery q;
    QString updateName = QString::fromStdString(update);
    q.prepare("update Contacts set Contact_Status = 1 where Name = :name");
    q.bindValue(":name", updateName);
    if(!q.exec()){
        std::cout<< "Query doesn't work" << std::endl;
    }
    QString message = updateName + " has been updated.";
    QMessageBox::about(this, "Confirmation", message);
}


void additionalInformation::on_yesBox_pressed()
{
    success = 1;
}


void additionalInformation::on_noBox_pressed()
{
    success = 0;
}


void additionalInformation::on_notSureBox_pressed()
{
    success = 2;
}

