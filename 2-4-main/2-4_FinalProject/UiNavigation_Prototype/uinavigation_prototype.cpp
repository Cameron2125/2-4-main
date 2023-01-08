#include "uinavigation_prototype.h"
#include "ui_uinavigation_prototype.h"

UiNavigation_Prototype::UiNavigation_Prototype(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UiNavigation_Prototype)
{
    ui->setupUi(this);

    //display logo
    QPixmap logo(":/images/companyLogo.png");
    int w = ui->companyLogo->width();
    int h = ui->companyLogo->height();
    ui->companyLogo->setPixmap(logo.scaled(w, h));
    //display logo
}

UiNavigation_Prototype::~UiNavigation_Prototype()
{
    delete ui;
}


void UiNavigation_Prototype::on_login_button_clicked()
{
    QString role = validUser();
    QString user = ui->username_edit->text();

    if (role == QString::fromStdString("Admin")) {
        admPortal = new adminPortal(this);

        QObject::connect(this, &UiNavigation_Prototype::toAdminPortal,
                         admPortal, &adminPortal::load);

        emit toAdminPortal(user, db);
        hide();
        admPortal->show();
    }
    else if (role == QString::fromStdString("Recruiter")) {
        vrPortal = new volunteerRecruiterPortal(this);

        QObject::connect(this, &UiNavigation_Prototype::toVolunteerRecruiterPortal,
                         vrPortal, &volunteerRecruiterPortal::load);

        emit toVolunteerRecruiterPortal(user);
        hide();
        vrPortal->show();
    }
    else if (role == QString::fromStdString("Researcher")) {
        resPortal = new researcherPortal(this);

        QObject::connect(this, &UiNavigation_Prototype::toResearcherPortal,
                         resPortal, &researcherPortal::load);
        emit toResearcherPortal(user);
        hide();
        resPortal->show();
    }
    else {

    }
}

QString UiNavigation_Prototype::validUser() {
    QString usernameInput = ui->username_edit->text();
    QString passwordInput = ui->password_edit->text();
    QString getUser = "select * from login where username = '" + usernameInput + "';";
    QSqlQuery qry = db->runQuery(getUser);

    if (qry.next()) {
        QString password = qry.value(1).toString();
        QString role = qry.value(2).toString();

        if (passwordInput != password) {
            QMessageBox::information(this, "Login", "Username/password invalid.");
            return NULL;
        }
        else {
            return role;
        }
    }
    else {
        QMessageBox::information(this, "Login", "Username/password invalid.");
        return NULL;
    }
}
