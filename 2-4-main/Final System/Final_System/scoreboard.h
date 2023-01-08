#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDialog>
#include<string>
#include<iostream>
#include <QtSql>
#include "./dbControl/dbcontrol.h"


namespace Ui {
class ScoreBoard;
}

class ScoreBoard : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief ScoreBoard
     * constructor for scoreboard
     * \param parent
     * the parent widget
     */
    explicit ScoreBoard(QWidget *parent = nullptr);
    ~ScoreBoard();
    /*!
     * \brief load
     * loads the scoreboard in from another window
     * \param id
     * the id of the user
     * \param t
     * the database to be used
     */
    void load(int id, dbControl *t);

private slots:
    void on_pushButton_clicked();

signals:
    void editClosed(int vid, dbControl *db);

private:
    Ui::ScoreBoard *ui;
    dbControl *db;
    int vid;
};

#endif // SCOREBOARD_H
