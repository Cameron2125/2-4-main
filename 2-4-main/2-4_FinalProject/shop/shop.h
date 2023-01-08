#ifndef SHOP_H
#define SHOP_H

#include <QMainWindow>
#include <../dbControl/dbcontrol.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Shop; }
QT_END_NAMESPACE

class Shop : public QMainWindow
{
    Q_OBJECT

public:
    Shop(QWidget *parent = nullptr);
    ~Shop();
    void load(int i, dbControl *dbc);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();

private:
    Ui::Shop *ui;
    dbControl *db;
    int id;
};
#endif // SHOP_H
