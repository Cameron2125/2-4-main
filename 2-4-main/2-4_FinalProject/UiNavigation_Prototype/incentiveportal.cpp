#include "incentiveportal.h"
#include "ui_incentiveportal.h"

incentivePortal::incentivePortal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::incentivePortal)
{
    ui->setupUi(this);
}


incentivePortal::~incentivePortal()
{
    delete ui;
}

void incentivePortal::activatePage() {

}

void incentivePortal::deactivatePage() {

}

void incentivePortal::load(dbControl *dbc) {
    db = dbc;
    showDataPointIncentives();
    showTaskIncentives();
}

void incentivePortal::showDataPointIncentives() {
    QListWidget *dataPt_list = ui->dataPt_list;
    dataPt_list->clear();

    QString getIncentives = "select * from datapt_incentive;";
    QSqlQuery qry = db->runQuery(getIncentives);

    while (qry.next()) {
        QString dataPtInfo = qry.value(0).toString() + "," + qry.value(1).toString();
        new QListWidgetItem(dataPtInfo, dataPt_list);
    }
}

void incentivePortal::showTaskIncentives() {
    QListWidget *task_list = ui->task_list;
    task_list->clear();

    QString getIncentives = "select * from task_incentive;";
    QSqlQuery qry = db->runQuery(getIncentives);

    while (qry.next()) {
        QString taskInfo = qry.value(0).toString() + "," + qry.value(1).toString();
        new QListWidgetItem(taskInfo, task_list);
    }
}

void incentivePortal::on_removeDataPt_button_clicked()
{
    QListWidget *dataPt_list = ui->dataPt_list;
    QList<QListWidgetItem *> selectedList = dataPt_list->selectedItems();
    for (int i = 0; i < selectedList.size(); i++) {
        QString selected = selectedList[i]->text();
        QStringList items = selected.split(QLatin1Char(','));
        QString dataPt = items.at(0);

        QString remove = "delete from datapt_incentive where dataPt = '" + dataPt + "';";
        db->runQuery(remove);
    }
    load(db);
}


void incentivePortal::on_removeTask_button_clicked()
{
    QListWidget *task_list = ui->task_list;
    QList<QListWidgetItem *> selectedList = task_list->selectedItems();
    for (int i = 0; i < selectedList.size(); i++) {
        QString selected = selectedList[i]->text();
        QStringList items = selected.split(QLatin1Char(','));
        QString task = items.at(0);

        QString remove = "delete from task_incentive where task = '" + task + "';";
        db->runQuery(remove);
    }
    load(db);
}


void incentivePortal::on_addDataPt_button_clicked()
{
    editDPIncentive = new editDataPtIncentiveDialog(this);
    deactivatePage();

    QObject::connect(this, &incentivePortal::toDataPtEditMenu,
                     editDPIncentive, &editDataPtIncentiveDialog::load);

    QObject::connect(editDPIncentive, &editDataPtIncentiveDialog::editClosed,
                     this, &incentivePortal::load);

    emit toDataPtEditMenu(db);
}


void incentivePortal::on_addTask_button_clicked()
{
    editTaskIncentive = new editTaskIncentiveDialog(this);
    deactivatePage();

    QObject::connect(this, &incentivePortal::toTaskEditMenu,
                     editTaskIncentive, &editTaskIncentiveDialog::load);

    QObject::connect(editTaskIncentive, &editTaskIncentiveDialog::editClosed,
                     this, &incentivePortal::load);

    emit toTaskEditMenu(db);
}

