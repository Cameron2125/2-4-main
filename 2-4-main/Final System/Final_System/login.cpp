#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //display logo
    QPixmap logo(":/images/resources/CS3M_logo.png");
    int w = ui->companyLogo->width();
    int h = ui->companyLogo->height();
    ui->companyLogo->setPixmap(logo.scaled(w, h));
    //display logo
}

Login::~Login()
{
    delete ui;
}

void Login::load(dbControl *dbc) {
    db = dbc;
}

void Login::on_login_button_clicked()
{
    //if valid user, get the user's role
    QString role = validUser();
    //get username
    QString user = ui->username_edit->text();

    //if admin, send to admin portal
    if (role == QString::fromStdString("Admin")) {
        admPortal = new AdminPortal(this);

        QObject::connect(this, &Login::toAdminPortal,
                         admPortal, &AdminPortal::load);

        emit toAdminPortal(user, db);
        hide();
        admPortal->show();

    }
    //if organizer, send to organizer portal
    else if (role == QString::fromStdString("Organizer")) {

        //gets the users LID so it can be used to find the vid
        QSqlQuery q;
        q.prepare("select LID from Login where Username = :user");
        q.bindValue(":user", user);
        if(!q.exec()){
            QMessageBox::warning(this, "LID", "Could not get user LID.");
        }
        int lid = 0;
        if(q.next()){
            lid = q.value(0).toInt();
        }

        q.prepare("select VID from Organizer where LID = :lid");
        q.bindValue(":lid", lid);
        if(!q.exec()){
            QMessageBox::warning(this, "VID", "Could not get user VID.");
        }
        int vid = 0;
        if(q.next()){
            vid = q.value(0).toInt();
        }

        QSqlQuery qry2;
        qry2.prepare("select Date from Point_History where VID = :vid");
        qry2.bindValue(":vid", vid);

        if(!qry2.exec()){
            QMessageBox::warning(this, "Database Error", qry2.lastError().text());
        }

        std::string day1 = "";

        while(qry2.next()){
            day1 = qry2.value(0).toString().toStdString();
        }

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        if(day1 != date_time){
            QMessageBox::information(this, "Welcome Back!", "Try scoring some more points by completing incentives!");
            QMessageBox::information(this, "New Incentives", "Make sure to look for NEW incentives daily!!");
        }

        orgPortal = new OrganizerPortal(this);

        QObject::connect(this, &Login::toOrganizerPortal,
                         orgPortal, &OrganizerPortal::load);

        // NEED TO FIND ID ASSOICATED WITH USERNAMEs
        emit toOrganizerPortal(vid, db);

        close();
        //orgPortal->load(vid, db);
        orgPortal->show();
    }
    else if (role == QString::fromStdString("Researcher")) {
        resPortal = new ResearcherPortal(this);

        QObject::connect(this, &Login::toResearcherPortal,
                         resPortal, &ResearcherPortal::load);
        emit toResearcherPortal(user, db);
        hide();
        resPortal->show();
    }
    else {

    }
}

QString Login::validUser() {
    QString usernameInput = ui->username_edit->text();
    QString passwordInput = ui->password_edit->text();

    //query database for login info of user
    QSqlQuery qry;
    qry.prepare("select * from Login where Username = :name");
    qry.bindValue(":name", usernameInput);
    qry.exec();

    //if query returns something
    if (qry.next()) {
        //get actual login password and compare w user input
        QString password = qry.value(2).toString();
        QString role = qry.value(3).toString();

        if (passwordInput != password) {
            QMessageBox::information(this, "Login", "Username/password invalid.");
            return NULL;
        }
        //return the role of the user so they can go to proper portal
        else {
            //store login Id in database control for later use
            db->loginId = qry.value(0).toInt();
            return role;
        }
    }
    else {
        QMessageBox::information(this, "Login", "Username/password invalid.");
        return NULL;
    }
}



/**
 * @brief signUpMessage: this is called when an account gets made
 */
void Login::signUpMessage() {
    QMessageBox::information(this, "Sign Up", "You have successfully made an account.");
}

void Login::on_signUp_button_clicked()
{
    //create a new SignUpDialog widget and connect to it
    signUp = new SignUpDialog(this);

    QObject::connect(this, &Login::toSignUp,
                     signUp, &SignUpDialog::load);

    QObject::connect(signUp, &SignUpDialog::signUpClosed,
                     this, &Login::load);

    //emit the dbControl object to the widget
    emit toSignUp(db);
}


