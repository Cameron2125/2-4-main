#ifndef ADDCONTACTMANUAL_H
#define ADDCONTACTMANUAL_H

#include <QMainWindow>
#include <QListWidget>
#include <vector>
#include <QMessageBox>
#include "./dbControl/dbcontrol.h"

namespace Ui {
class addContactManual;
}

class addContactManual : public QMainWindow
{
    Q_OBJECT

public:
    /** constructor */
    explicit addContactManual(QWidget *parent = nullptr);
    ~addContactManual();

    /**
     * @brief load: receive data from other page
     * @param dbc
     * @param vid
     */
    void load(dbControl *dbc, int vid);

private slots:
    /**
     * @brief on_Add_Contact_But_pressed: submit added contact(s)
     */
    void on_Add_Contact_But_pressed();

private:
    Ui::addContactManual *ui;

    dbControl *db;
    int vid;

};

#endif // ADDCONTACTMANUAL_H
