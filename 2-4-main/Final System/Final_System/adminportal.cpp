#include "adminportal.h"
#include "ui_adminportal.h"

AdminPortal::AdminPortal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPortal)
{
    ui->setupUi(this);
}

AdminPortal::~AdminPortal()
{
    delete ui;
}

void AdminPortal::load(QString username, dbControl *dbc) {
    user = username;
    //edit welcome label
    ui->welcome_label->setText("Welcome, " + username);
    //pass dbcontrol to this page
    db = dbc;
}

//send to incentives portal
void AdminPortal::on_incentives_button_clicked()
{
    incManager = new IncentiveManager(this);

    QObject::connect(this, &AdminPortal::toIncentivesManager,
                     incManager, &IncentiveManager::load);
    emit toIncentivesManager(user, db);
    hide();
    incManager->show();

    //when back button gets hit, show the admin portal again
    QObject::connect(incManager, &IncentiveManager::back,
                     this, &AdminPortal::show);
}

//send user to view contacts portal
void AdminPortal::on_viewContacts_button_clicked()
{
    cv = new ContactViewer(this);
    QObject::connect(this, &AdminPortal::toContactViewer,
                     cv, &ContactViewer::load);
    emit toContactViewer(user, db);
    hide();
    cv->show();

    //when back button on CV gets hit, show the admin portal again
    QObject::connect(cv, &ContactViewer::back,
                     this, &AdminPortal::show);
}

//send user to promotion portal
void AdminPortal::on_promote_button_clicked()
{
    promo = new PromotionManager(this);
    QObject::connect(this, &AdminPortal::toPromotionManager,
                     promo, &PromotionManager::load);
    emit toPromotionManager(user, db);
    hide();

    //when back button gets hit, show the admin portal again
    QObject::connect(promo, &PromotionManager::back,
                     this, &AdminPortal::show);
}

