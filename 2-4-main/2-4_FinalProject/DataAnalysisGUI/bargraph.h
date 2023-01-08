#ifndef BARGRAPH_H
#define BARGRAPH_H

#include <QScrollArea>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui {
class BarGraph;
}
QT_END_NAMESPACE

class BarGraph : public QScrollArea
{
    Q_OBJECT

public:
    explicit BarGraph(QWidget *parent = nullptr);
    ~BarGraph();

private:
    Ui::BarGraph *ui;
};

#endif // BARGRAPH_H
