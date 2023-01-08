#include "edittaskincentivedialog.h"
#include "ui_edittaskincentivedialog.h"

editTaskIncentiveDialog::editTaskIncentiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editTaskIncentiveDialog)
{
    ui->setupUi(this);
    show();
}

editTaskIncentiveDialog::~editTaskIncentiveDialog()
{
    delete ui;
}

void editTaskIncentiveDialog::load(dbControl *dbc) {
    db = dbc;
}

void editTaskIncentiveDialog::insertDB(QString task, QString pointVal) {
    QString insertIncentive = "insert into task_incentive values ('" + task + "'," + pointVal + ");";
    QSqlQuery qry = db->runQuery(insertIncentive);
}


void editTaskIncentiveDialog::on_submit_button_clicked()
{
    QString task = ui->task_edit->text();
    QString pointVal = ui->point_edit->text();
    insertDB(task, pointVal);
    emit editClosed(db);

    hide();
}

