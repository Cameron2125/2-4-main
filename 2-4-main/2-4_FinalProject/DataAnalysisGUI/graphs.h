#ifndef GRAPHS_H
#define GRAPHS_H

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


namespace Ui {
class Graphs;
}

class Graphs : public QMainWindow
{
    Q_OBJECT

public:
    explicit Graphs(QWidget *parent = nullptr);
    ~Graphs();
    void load();

private:
    Ui::Graphs *ui;
};

#endif // GRAPHS_H
