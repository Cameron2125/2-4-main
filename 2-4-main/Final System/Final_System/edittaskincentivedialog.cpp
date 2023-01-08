#include "edittaskincentivedialog.h"
#include "ui_edittaskincentivedialog.h"

TaskIncentiveEdit::TaskIncentiveEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskIncentiveEdit)
{
    ui->setupUi(this);
    show();
}

TaskIncentiveEdit::~TaskIncentiveEdit()
{
    delete ui;
}

void TaskIncentiveEdit::load(QString username, dbControl *dbc) {
    //load the user's username and the dbControl object
    user = username;
    db = dbc;
}

void TaskIncentiveEdit::insertDB(QString task, QString pointVal) {
    //prepare the query for inserting the new task incentive into the Incentives table
    QSqlQuery qry;
    //generate a unique id for the new incentive
    int newId = db->getMaxValue("IID", "Incentives")+1;
    qry.prepare("insert into Incentives values(:id, :name, :points, 0)");
    qry.bindValue(":id", newId);
    qry.bindValue(":name", task);
    qry.bindValue(":points", pointVal);
    qry.exec();
}


void TaskIncentiveEdit::on_submit_button_clicked()
{
    //insert the new task incentive into the database when the submit button is clicked
    QString task = ui->task_edit->text();
    QString pointVal = ui->point_edit->text();
    insertDB(task, pointVal);
    emit editClosed(user, db);

    hide();
}

