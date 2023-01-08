#include "additionalinformation.h"
#include "ui_additionalinformation.h"

////////////////////////////////////////////////////////
/// Constructors & Destructors
////////////////////////////////////////////////////////
additionalInformation::additionalInformation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::additionalInformation)
{
    ui->setupUi(this);
}

additionalInformation::~additionalInformation()
{
    delete ui;
}


////////////////////////////////////////////////////////
/// Screen Change
////////////////////////////////////////////////////////
void additionalInformation::on_addAttemptBut_pressed()
{
    //changes stack widget
    ui->stackedWidget->setCurrentIndex(1);
    setContactGroups();
}

void additionalInformation::on_updateStatusBut_pressed()
{
    //changes the stack widgest
    ui->stackedWidget->setCurrentIndex(2);
    setContactGroups();
}

void additionalInformation::on_return1_pressed()
{
    //return to the original stack widget
    ui->stackedWidget->setCurrentIndex(0);
}

void additionalInformation::on_return2_pressed()
{
    //return to the original stack widget
    ui->stackedWidget->setCurrentIndex(0);
}


////////////////////////////////////////////////////////
/// List Widget Control
////////////////////////////////////////////////////////
void additionalInformation::setContactGroups()
{
    //pull the information on Contacts in group 1 with the user's VID from the Contacts table
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT Name, Age, Location FROM Contacts where VID = " +
                    QString::number(VID) + " and Contact_Type = 1");
    //display said Contacts
    ui->ftofContacts->setModel(model);

    //pull the information on Contacts with the user's VID from the Contacts table
    QSqlQueryModel *model2 = new QSqlQueryModel();
    model2->setQuery("SELECT Name, Age, Location FROM Contacts where VID = "
                     + QString::number(VID));
    //display said contacts
    ui->allContacts->setModel(model2);
}

////////////////////////////////////////////////////////
/// Update Contacts
////////////////////////////////////////////////////////
void additionalInformation::on_addAttemptBut_2_pressed()
{
    //pull the Contact's information from the UI
    QString vid = QString::number(VID);
    QString updateName = QString::fromStdString(update);

    QString id = getCID(updateName, vid);

    QString attempts = getAttempts(id);

    //Set Date
    int dayDate = ui->day->value();
    int monthDate = ui->month->value();
    int yearDate = ui->year->value();

    // Date date;

    if(validDate(dayDate, monthDate, yearDate) == false){
        QMessageBox::warning(this, "Wrong Date",
                             "There is an error with the date! "
                             "Please fix it and resubmit.");
        return;
    }
    QString dateq = QString::number(dayDate) + QString::number(monthDate)
            + QString::number(yearDate);

    //Set Time
    int hours = ui->hrSpin->value();
    int mins = ui->minSpin->value();

    int length = 60 * hours + mins;
    QString lengthq = QString::number(length);

    //pull the information on the recruitment attempt from the UI
    QString successq = QString::number(success);

    QString response = ui->resText->toPlainText();

    QString additionalInfo = ui->addInfoLine->text();

    QString foc = ui->FOC_Combo->currentText();

    //insert the data on the recruitment attempt into the Recruitment_Attempts table
    QSqlQuery q;
    q.prepare("insert into Recruitment_Attempts (CID, Attempt_Number, Date, "
              "Sucess, Length, Response, Form_of_Contact, Additional_Info)"
              " values(:cid, :anum, :date, :suc, :length, :res, :foc, :addi)");
    q.bindValue(":cid", id);
    q.bindValue(":anum", attempts);
    q.bindValue(":date", dateq);
    q.bindValue(":suc", successq);
    q.bindValue(":length", lengthq);
    q.bindValue(":res", response);
    q.bindValue(":foc", foc);
    q.bindValue(":addi", additionalInfo);

    if(!q.exec()){
        QMessageBox::warning(this, "Database Error", q.lastError().text());
    }
    else {
        QMessageBox::information(this, "Contact Added",
                                 "Recruitment attempt was added successfully!");
    }

    // current date and time on the current system
    time_t now = time(0);

    // convert now to string form
    std::string date_time = ctime(&now);

    //update the points history of the user
    QSqlQuery qpoints;
    qpoints.prepare("insert into Point_History "
                    "(HID, VID, Point_Origin, Point_Value, Date) values "
                    "(:hid, :vid, :po, 10, :date)");
    qpoints.bindValue(":hid", QString::number(db->getMaxValue
                                              ("HID", "Point_History")+1));
    qpoints.bindValue(":vid", QString::number(VID));
    qpoints.bindValue(":po", "Recruitment Attempt");
    qpoints.bindValue(":date", QString::fromStdString(date_time));

    if(!qpoints.exec()){
        QMessageBox::warning(this, "Database Error",
                             qpoints.lastError().text());
    }
    else{
        QMessageBox::information(this, "Score",
                                 "You added a recruitment "
                                 "attempt and scored 10 points!");
    }

    //reset the UI elements
    ui->resText->clear();
    ui->addInfo->clear();
    ui->hrSpin->setValue(0);
    ui->minSpin->setValue(0);
    ui->day->setValue(1);
    ui->month->setValue(1);
    ui->year->setValue(2020);

}

void additionalInformation::on_notActiveBut_pressed()
{
    //update the Contact to not be actively volunteering in the database
    QSqlQuery q;
    QString updateName = QString::fromStdString(update);
    q.prepare("update Contacts set Contact_Status = 0 where Name = :name");
    q.bindValue(":name", updateName);
    if(!q.exec()){
        std::cerr<< "Query doesn't work" << std::endl;
    }
    QString message = updateName + " has been updated.";
    QMessageBox::about(this, "Confirmation", message);
}

void additionalInformation::on_activeBut_pressed()
{
    //update the Contact to be actively volunteering in the database
    QSqlQuery q;
    QString updateName = QString::fromStdString(update);
    q.prepare("update Contacts set Contact_Status = 1 where Name = :name");
    q.bindValue(":name", updateName);
    if(!q.exec()){
        std::cerr<< "Query doesn't work" << std::endl;
    }
    QString message = updateName + " has been updated.";
    QMessageBox::about(this, "Confirmation", message);
}

void additionalInformation::on_yesBox_pressed()
{
    //set success value to 1 (contact volunteered)
    success = 1;
}


void additionalInformation::on_noBox_pressed()
{
    //set success value to 0 (contact did not volunteer)
    success = 0;
}


void additionalInformation::on_notSureBox_pressed()
{
    //set success value to 2 (unsure if contact volunteered)
    success = 2;
}

void additionalInformation::on_allContacts_pressed(const QModelIndex &index)
{
    //update the name of the Contact
    QString name = index.data().toString();
    update = name.toStdString();
}


void additionalInformation::on_ftofContacts_pressed(const QModelIndex &index)
{
    //pull the name of the Contact
    QString name = index.data().toString();
    update = name.toStdString();
}

bool additionalInformation::validDate(int d, int m, int y){
    // Handle February month
    // with leap year
    if (m == 2)
    {
        if (((y % 4 == 0) &&
             (y % 100 != 0)) ||
             (y % 400 == 0))
            return (d <= 29);
        else
            return (d <= 28);
    }

    // Months of April, June,
    // Sept and Nov must have
    // number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 ||
            m == 9 || m == 11)
        return (d <= 30);
    else if (m <= 12) return (d <= 31);

    return false;
}

////////////////////////////////////////////////////////
/// Opening and Closing Portal
////////////////////////////////////////////////////////

void additionalInformation::load(int id, dbControl *t)
{
    //load the dbControl object and the user's id
    db = t;
    VID = id;
}

void additionalInformation::on_closeAddInfoBut_pressed()
{
    //emit the user's id and the dbControl object
    emit editClosed(VID, db);

    hide();
}

void additionalInformation::close()
{
    //emit the user's id and dbControl object
    emit editClosed(VID, db);
}

void additionalInformation::closeEvent (QCloseEvent *event)
{
    //emit the user's id and dbControl object
    emit editClosed(VID,  db);

    //hide the UI
    hide();
}

////////////////////////////////////////////////////////
/// Opening and Closing Portal
////////////////////////////////////////////////////////

QString additionalInformation::getCID(QString name, QString id){
    //Get CID
    QSqlQuery q1;
    q1.prepare("select CID from Contacts where Name = :name and VID = :vid");
    q1.bindValue(":name", name);
    q1.bindValue(":vid", id);

    if(!q1.exec()){
        QMessageBox::warning(this, "Database Error", q1.lastError().text());
    }
    int contNum = 0;
    if(q1.next()){
        contNum = q1.value(0).toInt();
    }

    return QString::number(contNum);
}

QString additionalInformation::getAttempts(QString id){
    //Get Attempts
    QSqlQuery q2;
    q2.prepare("select count(*) from Recruitment_Attempts where CID = :id");
    q2.bindValue(":id", id);
    if(!q2.exec()){
        QMessageBox::warning(this, "Database Error", q2.lastError().text());
    }
    int num_attempts = 0;
    if(q2.next()){
        num_attempts = q2.value(0).toInt() + 1;
    }
    return QString::number(num_attempts);
}
