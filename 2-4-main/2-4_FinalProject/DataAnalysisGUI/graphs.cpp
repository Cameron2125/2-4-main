#include "graphs.h"
#include "ui_graphs.h"

Graphs::Graphs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Graphs)
{
    ui->setupUi(this);
}

Graphs::~Graphs()
{
    delete ui;
}
void Graphs::load(){
        QBarSet *set0 = new QBarSet("Jane");
        QBarSet *set1 = new QBarSet("John");
        QBarSet *set2 = new QBarSet("Axel");
        QBarSet *set3 = new QBarSet("Mary");
        QBarSet *set4 = new QBarSet("Samantha");


        *set0 << 1 << 2 << 3 << 4 << 5 << 6;


        QBarSeries *series = new QBarSeries();
            series->append(set0);
            series->append(set1);
            series->append(set2);
            series->append(set3);
            series->append(set4);


            QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("Simple barchart example");
                chart->setAnimationOptions(QChart::SeriesAnimations);



                QStringList categories;
                categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
                QBarCategoryAxis *axisX = new QBarCategoryAxis();
                axisX->append(categories);
                chart->addAxis(axisX, Qt::AlignBottom);
                series->attachAxis(axisX);

                QValueAxis *axisY = new QValueAxis();
                axisY->setRange(0,15);
                chart->addAxis(axisY, Qt::AlignLeft);
                series->attachAxis(axisY);

                chart->legend()->setVisible(true);
                chart->legend()->setAlignment(Qt::AlignBottom);


                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);

                QMainWindow window;
                window.setCentralWidget(chartView);
                window.resize(420, 300);
                window.show();

}
