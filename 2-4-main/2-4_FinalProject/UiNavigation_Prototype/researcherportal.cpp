#include "researcherportal.h"
#include "ui_researcherportal.h"

researcherPortal::researcherPortal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::researcherPortal)
{
    ui->setupUi(this);
}

researcherPortal::~researcherPortal()
{
    delete ui;
}

void researcherPortal::load(QString username) {
    ui->welcome_label->setText("Welcome, " + username);
}

