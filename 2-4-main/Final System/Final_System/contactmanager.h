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
#include <QCloseEvent>
#include "./dbControl/dbcontrol.h"
#include "contactedit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ContactManager; }
QT_END_NAMESPACE

/**
 * @brief the contact manager component for organizers
 */
class ContactManager : public QDialog
{
    Q_OBJECT

public:
    ContactManager(QWidget *parent = nullptr);
    ~ContactManager();

    /**
     * @brief load: receive data from organizer portal
     * @param db
     * @param vid
     */
    void load(dbControl *db, int vid);

    /**
     * @brief load: receieve user id from organizer portal
     * @param vid
     */
    void load(int vid);

    // Fixed adjustable contact type integer
    int contact_type = 0;
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
    /**
     * @brief on_button_importcsv_clicked: open file system to import
     * contacts from csv
     */
    void on_button_importcsv_clicked();

    /**
     * @brief on_button_addnew_clicked: add new contact
     */
    void on_button_addnew_clicked();

    /**
     * @brief on_button_edit_clicked: edit contact
     */
    void on_button_edit_clicked();

    /**
     * @brief on_buttonBox_accepted: contact accepted
     */
    void on_buttonBox_accepted();

    /**
     * @brief on_buttonBox_rejected: contact data rejected. do nothing
     */
    void on_buttonBox_rejected();
    void closeEvent(QCloseEvent *event);

signals:
    /**
     * @brief editClosed: signal to close edit
     * @param db
     * @param vid
     */
    void editClosed(dbControl *db, int vid);

private:
    Ui::ContactManager *ui;
    dbControl *d;
    QString dbPath; // Database Path
    /**
     * @brief populateTableView: Populates table view with contacts from db
     */
    void populateTableView(int vid);

    // vid
    int current_vid;
    /**
     * @brief linkEditableTableView: Configure settings for table view
     * @param vid
     */
    void linkEditableTableView(int vid);

    /**
     * @brief SaveChanges: Function to save database changes
     */
    void SaveChanges();

    QSqlTableModel *tableModel;
    // points scored using ContactManager
    int score;
    // flag to indicate pending changes
    bool pendingChanges = false;

    bool save = false;

};
#endif // CONTACTMANAGER_H
