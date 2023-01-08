#include "bargraph.h"


BarGraph::BarGraph(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::BarGraph)
{
    ui->setupUi(this);
}

BarGraph::~BarGraph()
{
    delete ui;
}
