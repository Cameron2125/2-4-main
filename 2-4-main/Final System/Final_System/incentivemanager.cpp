#include "incentivemanager.h"
#include "ui_incentivemanager.h"

IncentiveManager::IncentiveManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IncentiveManager)
{
    ui->setupUi(this);
}

void IncentiveManager::load(QString username, dbControl *dbc) {
    user = username;
    db = dbc;
    showDataPointIncentives();
    showTaskIncentives();
}

IncentiveManager::~IncentiveManager()
{
    delete ui;
}

void IncentiveManager::showDataPointIncentives() {
    //initialize list contents
    QListWidget *dp_list = ui->dataPt_list;
    dp_list->clear();

    //get all dp incentives
    QString getIncentives = "select * from Incentives where Type = 1";
    QSqlQuery qry = db->runQuery(getIncentives);

    //iterate through and add each incentive into list from db
    while (qry.next()) {
        QString dataPtInfo = qry.value(1).toString() + "," + qry.value(2).toString();
        new QListWidgetItem(dataPtInfo, dp_list);
    }
}

void IncentiveManager::showTaskIncentives() {
    //initialize task list
    QListWidget *task_list = ui->task_list;
    task_list->clear();

    //grab incentives from db
    QString getIncentives = "select * from Incentives where Type = 0";
    QSqlQuery qry = db->runQuery(getIncentives);

    //iterate through and add to list from db
    while (qry.next()) {
        QString taskInfo = qry.value(1).toString() + "," + qry.value(2).toString();
        new QListWidgetItem(taskInfo, task_list);
    }
}


void IncentiveManager::on_removeDataPt_button_clicked()
{
    //get selected items to remove
    QListWidget *dp_list = ui->dataPt_list;
    QList<QListWidgetItem *> selectedList = dp_list->selectedItems();

    //iterate through list of selected items in list
    for (int i = 0; i < selectedList.size(); i++) {
        //get task incentive
        QString selected = selectedList[i]->text();

        //get all text before the comma (so we just get the incentive's name)
        QStringList items = selected.split(QLatin1Char(','));
        QString dataPt = items.at(0);

        //delete from db
        QSqlQuery qry;
        qry.prepare("delete from Incentives where Data_Name = :dp");
        qry.bindValue(":dp", dataPt);
        qry.exec();
    }
    //reinitialize
    load(user, db);
}


void IncentiveManager::on_addDataPt_button_clicked()
{
    //create a new DPIncentiveEdit widget and connect to it
    dpInc = new DPIncentiveEdit(this);

    QObject::connect(this, &IncentiveManager::toDataPtEditMenu,
                     dpInc, &DPIncentiveEdit::load);

    QObject::connect(dpInc, &DPIncentiveEdit::editClosed,
                     this, &IncentiveManager::load);

    //emit the user's username and the dbControl object
    emit toDataPtEditMenu(user, db);

}


void IncentiveManager::on_removeTask_button_clicked()
{
    //remove the selected task incentives from the database
    QListWidget *task_list = ui->task_list;
    QList<QListWidgetItem *> selectedList = task_list->selectedItems();
    for (int i = 0; i < selectedList.size(); i++) {
        QString selected = selectedList[i]->text();
        QStringList items = selected.split(QLatin1Char(','));
        QString task = items.at(0);

        //delete from db
        QSqlQuery qry;
        qry.prepare("delete from Incentives where Data_Name = :t");
        qry.bindValue(":t", task);
        if(!qry.exec()){

        }
    }
    load(user, db);
}


void IncentiveManager::on_addTask_button_clicked()
{
    //create a new TaskIncentiveEdit widget and connect to it
    taskInc = new TaskIncentiveEdit(this);

    QObject::connect(this, &IncentiveManager::toTaskEditMenu,
                     taskInc, &TaskIncentiveEdit::load);

    QObject::connect(taskInc, &TaskIncentiveEdit::editClosed,
                     this, &IncentiveManager::load);

    //emit the user's username and the dbControl object
    emit toTaskEditMenu(user, db);
}


void IncentiveManager::on_back_button_clicked()
{
    //emit the user's username and the dbControl object, then hide the UI
    emit back(user, db);
    hide();
}

