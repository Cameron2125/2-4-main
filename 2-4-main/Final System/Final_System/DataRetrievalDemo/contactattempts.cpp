#include "contactattempts.h"
#include "ui_contactattempts.h"

ContactAttempts::ContactAttempts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactAttempts)
{
    ui->setupUi(this);
}

ContactAttempts::~ContactAttempts()
{
    delete ui;
}
void ContactAttempts::load(QString ids, dbControl dBases){

    QSqlQuery qry = dBases.runQuery("select * from Recruitment_Attempts");




    while (qry.next()){

        if (qry.value(0).toInt() == ids.toInt()){
    QString attempts;
    //load attempts with data from DB
    std::string contact;
    QSqlRecord record = qry.record();
    for (int i = 0; i < record.count(); i++){

     std::string adder = qry.value(i).toString().toStdString();



     //add similar if statment for VID to change number into volunteer name
        if (i == 12){

            if (qry.value(i).toInt() == 1){

                adder = "volunteered";
            }
            else if (qry.value(i).toInt() == 2){

                adder = "Interested in Volunteering";
            }
            else{

                adder = "not volunteered";
            }

        }
    if (i != record.count()-1){

    contact = contact + adder + ", ";

    }
    else {

        contact = contact + adder;
    }
    }

    attempts = QString::fromStdString(contact);
    ui->listWidget->addItem(attempts);
        }


    }





}
