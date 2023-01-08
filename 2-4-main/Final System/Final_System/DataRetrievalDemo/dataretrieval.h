#ifndef DATARETRIEVAL_H
#define DATARETRIEVAL_H
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "QString"
#include <QMainWindow>
#include <QObject>
//#include "contactattempts.h"
#include "../dbControl/dbcontrol.h"
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DataRetrieval; }
QT_END_NAMESPACE

class DataRetrieval : public QMainWindow
{
    Q_OBJECT

public:
    DataRetrieval(QWidget *parent = nullptr);
    ~DataRetrieval();
    void load(dbControl *db);

private slots:
    //std::adminPortal *admin;
    void on_submit_clicked();
    //void on_search_itemDoubleClicked(QListWidgetItem *item);


signals:
    void toContactAttempt(QString id,dbControl db);

private:
    dbControl *dBases;
    std::vector<std::string> lName;
    //ContactAttempts *CA;
    Ui::DataRetrieval *ui;
};
#endif // DATARETRIEVAL_H
