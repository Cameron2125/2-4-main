#ifndef CONTACTMAN_H
#define CONTACTMAN_H

#include <QMainWindow>
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


namespace Ui {
class contactman;
}

/**
 * @brief the contact manager component for organizers
 */
class contactman : public QMainWindow
{
    Q_OBJECT

public:
    /** constructor */
    explicit contactman(QWidget *parent = nullptr);
    ~contactman();

    /**
     * @brief load: receive data from previous page
     * @param vid
     * @param db
     */
    void load(int vid, dbControl *db);
    // Fixed adjustable contact type integer
    int contact_type = 0;

private slots:
    /**
     * @brief on_button_importcsv_clicked: open file system to import from csv
     */
    void on_button_importcsv_clicked();

    /**
     * @brief on_button_addnew_clicked: open dialog to add new contact
     */
    void on_button_addnew_clicked();

    /**
     * @brief on_button_edit_clicked: edit contact
     */
    void on_button_edit_clicked();

    /**
     * @brief closeEvent: close component
     * @param event
     */
    void closeEvent(QCloseEvent *event);

    /**
     * @brief on_button_remove_pressed: remove contact by id
     */
    void on_button_remove_pressed();

    /**
     * @brief on_tableView_pressed
     * @param index
     */
    void on_tableView_pressed(const QModelIndex &index);

    /**
     * @brief on_button_save_pressed: save changes and assign points
     */
    void on_button_save_pressed();

    /**
     * @brief on_button_cancel_pressed: cancel changes
     */
    void on_button_cancel_pressed();

signals:
    /**
     * @brief editClosed: signal to close component
     * @param vid
     * @param db
     */
    void editClosed(int vid, dbControl *db);

private:
    dbControl *d;

    /**
     * @brief populateTableView: populate tableview component with
     * contact data from database
     * @param vid
     */
    void populateTableView(int vid);

    // vid
    int current_vid;

    /**
     * @brief linkEditableTableView: configure settings for table view
     * @param vid
     */
    void linkEditableTableView(int vid);

    QSqlTableModel *tableModel;

    /**
     * @brief save database changes
     */
    void SaveChanges();

    // points scored using ContactManager
    int score = 0;
    // flag to indicate pending changes
    bool pendingChanges = false;

    bool save = false;

    QString cidContactDataChange;
    Ui::contactman *ui;
};

#endif // CONTACTMAN_H
