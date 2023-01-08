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
#include "dbControl/dbcontrol.h"
#include<string.h>


QT_BEGIN_NAMESPACE
namespace Ui { class DataGui; }
QT_END_NAMESPACE


/**
 * @brief class responsible for all data displays in system
 */
class DataGui : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief DataGui
     * \param parent the parent widget
     * constructor for data gui for regulat construction
     */
    DataGui(QWidget *parent = nullptr);
    /*!
     * \brief DataGui
     * Constructor for unit testing
     * \param i random param value does not matter
     */
    DataGui(int i);
    ~DataGui();
    /*!
     * \brief getAverage
     * Methods that returns a average for the integer value
     * colummn given when the id matches
     * \param id
     * Integer id for mtaching value
     * \param colum
     * The column that you want to check the id with
     * \param valcol
     * The column for the value
     * \param table
     * the name of the table
     * \return
     */
    double getAverage(int id, int colum,int valcol, std::string table);
    /*!
     * \brief createBar
     * creates a bar chart
     * \param names
     * the name of the bars
     * \param data
     * the data for the bars
     * \param name
     * the title of the graph
     */
    void createBar(std::vector<std::string> names, std::vector<double> data, std::string name);
    /*!
     * \brief createPie
     * creates a pie chart
     * \param names
     * the names of the pie slices
     * \param data
     * the data for pie slices
     * \param name
     * the title of the graph
     */
    void createPie(std::vector<std::string> names,std::vector<double> data, std::string name);
    /*!
     * \brief createLine
     * creates a line chart
     * \param data1
     * data of first time
     * \param data2
     * data of second line
     */
    void createLine(std::vector<double> data1,std::vector<double> data2);
    /*!
     * \brief load
     * loads the window from another window
     * \param db2
     * the database used
     */
    void load(dbControl *db2);
    /*!
     * \brief ethInterest
     * returns the average interest for each ethnicity
     * \return
     */
    std::vector<double> ethInterest();
    /*!
     * \brief eduInterest
     * returns the average interest for each type of education
     * \return
     */
    std::vector<double> eduInterest();
    /*!
     * \brief ethDist
     * returns vectors of the number of contacts that are of a certain ethnicity
     * \return
     * returns vectors of the number of contacts that are of a certain ethnicity
     */
    std::vector<double> ethDist();
    /*!
     * \brief eduDist
     * returns vectors of the number of contacts that are of a certain education
     * \return
     * returns vectors of the number of contacts that are of a certain education
     */
    std::vector<double> eduDist();
    /*!
     * \brief ageDist
     * returns vectors of the number of contacts that are of a certain age
     * \return
     * returns vectors of the number of contacts that are of a certain age
     */
    std::vector<double> ageDist();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    //boolean value used to correct deconstructor for unit testing
    bool isUI;
    Ui::DataGui *ui;
    //daatbase object
    dbControl *db;
    //vector a graphs used for clearing graphs on screen
    std::vector<QChartView*> graphs;
};
#endif // DATAGUI_H
