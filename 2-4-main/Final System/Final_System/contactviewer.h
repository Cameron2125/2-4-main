#ifndef CONTACTVIEWER_H
#define CONTACTVIEWER_H

#include <QMainWindow>
#include "dbControl/dbcontrol.h"

namespace Ui {
class ContactViewer;
}

/**
 * @brief UI component used by researcher and admin to
 * view all contacts in the system and who they belong to
 */
class ContactViewer : public QMainWindow
{
    Q_OBJECT

public:
    /** constructor */
    explicit ContactViewer(QWidget *parent = nullptr);
    ~ContactViewer();

    dbControl * db;
    QString user;

    /**
     * @brief populateTableView: get all contacts from database
     * and add them to table view
     */
    void populateTableView();

signals:
    /**
     * @brief back: signal emitted when back button is pressed
     * that sends user to previous pages
     * @param username
     * @param dbc
     */
    void back(QString username, dbControl *dbc);

public slots:
    /**
     * @brief load: receive data from previous page
     * @param username
     * @param dbc
     */
    void load(QString username, dbControl *dbc);

private slots:
    /**
     * @brief on_search_button_clicked: begin search for contact w/ keyword
     */
    void on_search_button_clicked();

    /**
     * @brief on_back_button_clicked: go back
     */
    void on_back_button_clicked();

private:
    Ui::ContactViewer *ui;
};

#endif // CONTACTVIEWER_H
