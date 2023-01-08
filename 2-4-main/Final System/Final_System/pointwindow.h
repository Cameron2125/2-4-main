#ifndef POINTWINDOW_H
#define POINTWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include "./dbControl/dbcontrol.h"

namespace Ui {
class PointWindow;
}

class PointWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PointWindow(QWidget *parent = nullptr);
    ~PointWindow();
    void setProgressBars();
    void load(int id, dbControl *t);

signals:
    void editClosed(int vid, dbControl *db);

private slots:
    void on_returnPortalBut_pressed();

    void resizeEvent(QResizeEvent *);

private:
    Ui::PointWindow *ui;
    int vid;
    dbControl *db;
};

#endif // POINTWINDOW_H
