#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableView>
#include <QSqlQueryModel>
#include <QFile>
#include <QDebug>
#include <QElapsedTimer>
#include <../dbControl/dbcontrol.h>

QT_BEGIN_NAMESPACE
namespace Ui { class ContactManager; }
QT_END_NAMESPACE

class ContactManager : public QDialog
{
    Q_OBJECT

public:
    ContactManager(QWidget *parent = nullptr);
    ~ContactManager();
    void load(dbControl *db, int vid);
    void load(int vid);
    // Database
    QSqlDatabase db;
    // Open DB
    bool openDB(){
        db = QSqlDatabase::addDatabase("QSQLITE", "ContactManager_connection");
        db.setDatabaseName(dbPath);

        if(!db.open())
        {
            qDebug()<<"Error opening database" << db.lastError();
            return false;
        }else{
            qDebug()<<"Connection Established.";
            return true;
        }
    }
    // Close DB
    void closeDB(){
        db.close();
    }
    // Check DB
    bool checkDB(QString path);

private slots:
    void on_button_importcsv_clicked();

    void on_button_addnew_clicked();

private:
    Ui::ContactManager *ui;
    QString dbPath; // Database Path
    // Populates table view
    void populateTableView(int vid);
    // vid
    int current_vid;
    void linkEditableTableView(int vid);
    QSqlTableModel *tableModel;
};
#endif // CONTACTMANAGER_H
