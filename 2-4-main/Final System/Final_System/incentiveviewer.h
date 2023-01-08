
#ifndef INCENTIVEVIEWER_H
#define INCENTIVEVIEWER_H

#include <QMainWindow>
#include "./dbControl/dbcontrol.h"

namespace Ui {
class IncentiveViewer;
}

class IncentiveViewer : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief IncentiveViewer Constructor for incentive View
     * \param parent Parent Widget
     */
    explicit IncentiveViewer(QWidget *parent = nullptr);
    ~IncentiveViewer();
    /*!
     * \brief load loads the current class from another window
     * \param i the id of the user
     * \param dbc the database to be passed
     */
    void load(int i, dbControl *dbc);

private slots:
    /*!
     * \brief on_returnBut_pressed backbutton that returns to home portal
     */
    void on_returnBut_pressed();

signals:
    /*!
     * \brief editClosed signal for when window is closed
     * \param i the id of the user
     * \param db the database to be passed
     */
    void editClosed(int i, dbControl *db);

private:
    Ui::IncentiveViewer *ui;
    //class db
    dbControl *db;
    //id of user
    int vid;
};

#endif // INCENTIVEVIEWER_H

