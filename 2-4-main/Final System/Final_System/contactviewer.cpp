#include "contactviewer.h"
#include "ui_contactviewer.h"

ContactViewer::ContactViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactViewer)
{
    ui->setupUi(this);
}

ContactViewer::~ContactViewer()
{
    delete ui;
}

void ContactViewer::load(QString username, dbControl *dbc) {
    user = username;
    db = dbc;
    populateTableView();
}

/**
 * @brief populateTableView: select all from contacts table
 * and display the results of the query in table
 * view
 */
void ContactViewer::populateTableView() {
    //get all contacts and put them in our tableview
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM CONTACTS");
    qry.exec();

    model->setQuery(qry);
    ui->allContacts_view->setModel(model);
}

//retrieve contacts with specified field
void ContactViewer::on_search_button_clicked()
{
    //field is the data field to get
    QString field = ui->data_edit->text();
    //keyword is the specific word
    QString keyword = ui->keyword_edit->text();

    //prepare query (note the use of the LIKE operator)
    QSqlQuery qry;
    qry.prepare(QString("SELECT * FROM Contacts WHERE %1 LIKE :key").arg(field));
    qry.bindValue(":key", ("%" + keyword + "%"));
    qry.exec();

    //update table
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(qry);
    ui->results_list->setModel(model);
}


void ContactViewer::on_back_button_clicked()
{
    emit back(user, db);
    hide();
}

