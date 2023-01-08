#include "volunteerrecruiterportal.h"
#include "ui_volunteerrecruiterportal.h"

volunteerRecruiterPortal::volunteerRecruiterPortal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::volunteerRecruiterPortal)
{
    ui->setupUi(this);
}

volunteerRecruiterPortal::~volunteerRecruiterPortal()
{
    delete ui;
}

void volunteerRecruiterPortal::load(QString username) {
    ui->welcome_label->setText("Welcome, " + username);
}
