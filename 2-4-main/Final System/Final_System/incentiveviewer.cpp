
#include "incentiveviewer.h"
#include "ui_incentiveviewer.h"

IncentiveViewer::IncentiveViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IncentiveViewer)
{
    ui->setupUi(this);
}

IncentiveViewer::~IncentiveViewer()
{
    delete ui;
}

void IncentiveViewer::on_returnBut_pressed()
{
    emit editClosed(vid, db);

    hide();
}

void IncentiveViewer::load(int i, dbControl *dbc)
{
    vid = i;
    db = dbc;

    //prepare query (note the use of the LIKE operator)
    QSqlQuery qry;
    qry.prepare(QString("SELECT Data_Name, Points FROM Incentives"));
    qry.exec();

    //update table
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(qry);
    ui->incentView->setModel(model);
}
