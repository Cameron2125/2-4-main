#include "dpincentiveedit.h"
#include "ui_dpincentiveedit.h"

DPIncentiveEdit::DPIncentiveEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DPIncentiveEdit)
{
    ui->setupUi(this);
    show();
}

DPIncentiveEdit::~DPIncentiveEdit()
{
    delete ui;
}

void DPIncentiveEdit::load(QString username, dbControl *dbc) {
    //load the user's username and the dbControl object
    user = username;
    db = dbc;
}

void DPIncentiveEdit::on_submit_button_clicked()
{
    //pull the data point to be adjusted and the given point value from the UI elements
    QString dataPt = ui->dp_combo->currentText();
    QString pointVal = QString::number(ui->pointSpin->value());
    //prepare the query to insert the updated point value into the Incentives table
    QSqlQuery qry;
    qry.prepare("insert into Incentives (IID, Data_Name, Points, Type) values(:id, :name, :pointValue, :type)");
    qry.bindValue(":id", QString::number(db->getMaxValue("IID", "Incentives")+1));
    qry.bindValue(":name", dataPt);
    qry.bindValue(":type", "1");
    qry.bindValue(":pointValue", pointVal);

    if(!qry.exec()){
        QMessageBox::warning(this, "Database Error", qry.lastError().text());
    }

    emit editClosed(user, db);

    hide();
}

