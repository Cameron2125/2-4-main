#include "researcherportal.h"
#include "ui_researcherportal.h"

ResearcherPortal::ResearcherPortal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResearcherPortal)
{
    ui->setupUi(this);
}

ResearcherPortal::~ResearcherPortal()
{
    delete ui;
}

void ResearcherPortal::load(QString username, dbControl *dbcc) {
    //load the user's username and the dbControl object
    user = username;
    //display the user's name
    ui->welcome_label->setText("Welcome, " + username);
    db = dbcc;
}

void ResearcherPortal::on_viewContactButton_pressed()
{
    //create a new contact viewer widget and connect to it
    cv = new ContactViewer(this);

    QObject::connect(this, &ResearcherPortal::toCV,
                     cv, &ContactViewer::load);

    //emit the user's username and the dbControl object to the widget
    emit toCV(user, db);
    cv->show();

    cv->load(user, db);
}


void ResearcherPortal::on_dataAnalysisButton_pressed()
{
    //create a new data gui widget and connect to it
    dr = new DataGui(this);

    QObject::connect(this, &ResearcherPortal::toDR,
                     dr, &DataGui::load);

    //emit the user's username and the dbControl object to the widget
    emit toDR(db);
    dr->show();

    dr->load(db);
}
