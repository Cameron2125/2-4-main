#include "viewcontacts.h"
#include "ui_viewcontacts.h"

ViewContacts::ViewContacts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewContacts)
{
    ui->setupUi(this);
}

ViewContacts::~ViewContacts()
{
    delete ui;
}
