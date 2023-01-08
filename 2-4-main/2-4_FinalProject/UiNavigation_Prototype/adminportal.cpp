#include "adminportal.h"
#include "ui_adminportal.h"

adminPortal::adminPortal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminPortal)
{
    ui->setupUi(this);
}

adminPortal::~adminPortal()
{
    delete ui;
}

void adminPortal::load(QString username, dbControl *dbc) {
    ui->welcome_label->setText("Welcome, " + username);
    db = dbc;


}

void adminPortal::on_setIncentive_button_clicked()
{
    setIncentPortal = new incentivePortal(this);

    QObject::connect(this, &adminPortal::toIncentivePortal,
                     setIncentPortal, &incentivePortal::load);
    emit toIncentivePortal(db);
    hide();
    setIncentPortal->show();
}

