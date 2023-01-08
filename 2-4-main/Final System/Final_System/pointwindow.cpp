#include "pointwindow.h"
#include "ui_pointwindow.h"

PointWindow::PointWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PointWindow)
{
    ui->setupUi(this);


    //display logo
    QPixmap logo(":/images/resources/Recruiter1.png");
    int w = ui->but100->width();
    int h = ui->but100->width();
    ui->pic100->setPixmap(logo.scaled(w, h, Qt::KeepAspectRatio));
    //display logo

    //display logo
    QPixmap logo2(":/images/resources/Recruiter2.png");
    ui->pic250->setPixmap(logo2.scaled(w, h, Qt::KeepAspectRatio));
    //display logo

    //display logo
    QPixmap logo3(":/images/resources/Recruiter3.png");
    ui->pic500->setPixmap(logo3.scaled(w, h, Qt::KeepAspectRatio));
    //display logo

    //display logo
    QPixmap logo4(":/images/resources/Recruiter4.png");
    ui->pic1000->setPixmap(logo4.scaled(w, h, Qt::KeepAspectRatio));
    //display logo
}

PointWindow::~PointWindow()
{
    delete ui;
}

void PointWindow::setProgressBars()
{
    ui->pro100->reset();
    ui->pro250->reset();
    ui->pro500->reset();
    ui->pro1000->reset();

    int points = 0;
    QSqlQuery q;
    q.prepare("select Overall_Points from Organizer where VID = :vid");
    q.bindValue(":vid", vid);

    if(!q.exec()){
        QMessageBox::warning(this, "Database Error", q.lastError().text());
    }
    if(q.next()){
        points = q.value(0).toInt();
        std::cout << points << std::endl;
    }

    if(points > 100){
        ui->pro100->setValue(100);
    }
    else{
        ui->pro100->setValue(points);
    }
    if(points > 250){
        ui->pro250->setValue(250);
    }
    else{
        ui->pro250->setValue(points);
    }
    if(points > 500){
        ui->pro500->setValue(500);
    }
    else{
        ui->pro500->setValue(points);
    }
    if(points > 1000){
        ui->pro1000->setValue(1000);
    }
    else{
        ui->pro1000->setValue(points);
    }
}


void PointWindow::load(int i, dbControl *dbc)
{
    vid = i;
    db = dbc;
    setProgressBars();
}

void PointWindow::on_returnPortalBut_pressed()
{
    emit editClosed(vid, db);

    hide();
}


void PointWindow::resizeEvent(QResizeEvent *event)
{

    //display logo
    QPixmap logo(":/images/resources/Recruiter1.png");
    int w = ui->but100->width();
    int h = ui->but100->width();
    ui->pic100->setPixmap(logo.scaled(w, h, Qt::KeepAspectRatio));
    //display logo

    //display logo
    QPixmap logo2(":/images/resources/Recruiter2.png");
    ui->pic250->setPixmap(logo2.scaled(w, h, Qt::KeepAspectRatio));
    //display logo

    //display logo
    QPixmap logo3(":/images/resources/Recruiter3.png");
    ui->pic500->setPixmap(logo3.scaled(w, h, Qt::KeepAspectRatio));
    //display logo

    //display logo
    QPixmap logo4(":/images/resources/Recruiter4.png");
    ui->pic1000->setPixmap(logo4.scaled(w, h, Qt::KeepAspectRatio));
    //display logo
}

