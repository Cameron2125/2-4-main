#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDialog>
#include<string>
#include<iostream>
#include <QtSql>
#include <../dbControl/dbcontrol.h>

namespace Ui {
class ScoreBoard;
}

class ScoreBoard : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreBoard(QWidget *parent = nullptr);
    ~ScoreBoard();
    void load(int id);

private:
    Ui::ScoreBoard *ui;
    dbControl *db;
};

#endif // SCOREBOARD_H
