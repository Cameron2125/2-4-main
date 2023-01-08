#include "editdataptincentivedialog.h"
#include "ui_editdataptincentivedialog.h"

editDataPtIncentiveDialog::editDataPtIncentiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDataPtIncentiveDialog)
{
    ui->setupUi(this);
    show();
}

editDataPtIncentiveDialog::~editDataPtIncentiveDialog()
{
    delete ui;
}

void editDataPtIncentiveDialog::load(dbControl *dbc) {
    db = dbc;
}

void editDataPtIncentiveDialog::insertDB(QString dataPt, QString pointVal) {
    QString insertIncentive = "insert into datapt_incentive values ('" + dataPt + "'," + pointVal + ");";
    QSqlQuery qry = db->runQuery(insertIncentive);
}


void editDataPtIncentiveDialog::on_submit_button_clicked()
{
    QString dataPt = ui->dataPt_combo->currentText();
    QString pointVal = ui->point_edit->text();
    insertDB(dataPt, pointVal);
    emit editClosed(db);

    hide();
}

