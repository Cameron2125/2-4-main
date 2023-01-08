#include "purchasedbadge.h"
#include "ui_purchasedbadge.h"

PurchasedBadge::PurchasedBadge(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PurchasedBadge)
{
    ui->setupUi(this);
}

PurchasedBadge::~PurchasedBadge()
{
    delete ui;
}

void PurchasedBadge::closeEvent (QCloseEvent *event)
{
    emit editClosed(pic);

    hide();
}

void PurchasedBadge::load(QString pic2)
{
    //set the image for the given badge
    pic = pic2;
    QPixmap logo(pic);
    int w = ui->badge->width();
    int h = ui->badge->height();
    ui->badge->setPixmap(logo.scaled(w, h));
}
