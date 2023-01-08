#include "dataretrieval.h"
#include "ui_dataretrieval.h"


DataRetrieval::DataRetrieval(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataRetrieval)
{
    ui->setupUi(this);

    QSqlQuery qry = dBases->runQuery("select * from Contacts");

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from Contacts");
    ui->allContacts->setModel(model);
}

void DataRetrieval::on_submit_clicked(){

     //ui->search->clear();
    QString feild = ui->feildName->text();
    QString keyword = ui->keyword->text();
    //feild = feild.toLower();
    //keyword = keyword.toLower();



    QSqlQuery qry;

    QString run = "select * from Contacts where " + feild + " = " + keyword;
    qry = dBases->runQuery(run);

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from Contacts"+ feild + " = " + keyword);
    ui->search->setModel(model);
}


DataRetrieval::~DataRetrieval()
{
    delete ui;
}

void DataRetrieval::load(dbControl *db){
    dBases = db;
}

