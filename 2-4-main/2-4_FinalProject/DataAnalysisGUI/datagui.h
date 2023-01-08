#ifndef DATAGUI_H
#define DATAGUI_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>
#include<string>
#include <iostream>
#include <fstream>
#include <QtSql>
#include <vector>
#include <../dbControl/dbcontrol.h>
#include<string.h>


QT_BEGIN_NAMESPACE
namespace Ui { class DataGui; }
QT_END_NAMESPACE

class DataGui : public QMainWindow
{
    Q_OBJECT

public:
    DataGui(QWidget *parent = nullptr);
    ~DataGui();
    double getAverage(int id, int colum,int valcol, std::string table);
    void createBar(std::vector<std::string> names, std::vector<double> data);
    void createPie(std::vector<std::string> names,std::vector<double> data);
    void createLine(std::vector<double> data1,std::vector<double> data2);
    void load(dbControl *db2);
    std::vector<double> ethInterest();
    std::vector<double> eduInterest();
    std::vector<double> ethDist();
    std::vector<double> eduDist();
    std::vector<double> ageDist();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DataGui *ui;
    dbControl *db;
    std::vector<QChartView*> graphs;
};
#endif // DATAGUI_H
