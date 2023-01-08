#include "addcontactmanual.h"
#include "ui_addcontactmanual.h"

addContactManual::addContactManual(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addContactManual)
{
    ui->setupUi(this);
}

addContactManual::~addContactManual()
{
    delete ui;
}

void addContactManual::on_Add_Contact_But_pressed()
{
    //pull the Contact's information from the UI elements
    QString name = ui->Name_Line->text();
    QString age = ui->Age_Spin->text();
    QString location = ui->Location_Line->text();
    QString gender = ui->Gender_Line->text();
    QString ethnicity = ui->Ethnicity_Line->text();
    QString education = ui->Education_Line->text();
    QString occupation = ui->Occupation_Line->text();
    QString email = ui->Email_Line->text();
    QString phone = ui->Phone_Num_Line->text();
    QString add = ui->Add_Info_Line->text();

    //generate a unique CID for the Contact based on the length of the Contacts table
    int length = db->getMaxValue("CID", "Contacts");
    length++;
    QString cid = QString::number(length);


    //prepare the query to enter the Contact into the Contacts table
    QSqlQuery query;
    query.prepare("INSERT INTO Contacts "
                  "(VID, Contact_Type, CID, Name, Age, Location, Gender, "
                  "Ethnicity, Education, Occupation, Email, Phone_Number, "
                  "Contact_Status, Additional_Info, AID) VALUES "
                  "(:VID, :Contact_Type, :CID, :Name, :Age, :Location, :Gender, "
                  ":Ethnicity, :Education, :Occupation, :Email, :Phone_Number, "
                  ":Contact_Status, :Additional_Info, :AID)");
    // Find the entry using the indexArray and add to query
    query.bindValue(":VID", vid);
    query.bindValue(":Contact_Type", "0");
    query.bindValue(":CID", cid);
    query.bindValue(":Name", name);
    query.bindValue(":Age", age);
    query.bindValue(":Location", location);
    query.bindValue(":Gender", gender);
    query.bindValue(":Ethnicity", ethnicity);
    query.bindValue(":Education", education);
    query.bindValue(":Occupation", occupation);
    query.bindValue(":Email", email);
    query.bindValue(":Phone_Number", phone);
    query.bindValue(":Contact_Status", "0");
    query.bindValue(":Additional_Info", add);
    query.bindValue(":AID", "0");

    if(!query.exec()) {
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }
    else{
        QMessageBox::information(this, "Contact Added", name + " was added successfully!");
    }

    //clear the values present in the UI
    ui->Name_Line->clear();
    ui->Age_Spin->setValue(0);
    ui->Location_Line->clear();
    ui->Gender_Line->clear();
    ui->Ethnicity_Line->clear();
    ui->Education_Line->clear();
    ui->Occupation_Line->clear();
    ui->Email_Line->clear();
    ui->Phone_Num_Line->clear();
    ui->Add_Info_Line->clear();
}

void addContactManual::load(dbControl *dbc, int vidc){
    //load the UI element with the given dbControl object and VID
    db = dbc;
    vid = vidc;
}

