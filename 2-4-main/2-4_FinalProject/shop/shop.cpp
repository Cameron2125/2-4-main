#include "shop.h"
#include "ui_shop.h"

Shop::Shop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Shop)
{
    ui->setupUi(this);
}

Shop::~Shop()
{
    delete ui;
}


void Shop::on_pushButton_clicked()
{

    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",1" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }




}


void Shop::on_pushButton_2_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",2" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_3_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",3" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_4_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",4" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_5_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",5" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_6_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",6" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_7_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",7" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_8_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",8" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_9_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",9" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_10_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",10" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_11_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",11" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_12_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",12" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_13_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",13" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_14_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",14" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_15_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",15" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::on_pushButton_16_clicked()
{
    int score = stoi(db->getField(10,id,"Organizer"));

    if ( score > 100){

        int newScore = score - 100;
        std::string qstr = "UPDATE Organizer SET Overall_Points = " + std::to_string(newScore) + " WHERE VID = " + std::to_string(id);
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = " + db->getField(10,id,"Organizer") + ",6" + " WHERE VID = " + std::to_string(id);
         run = QString::fromStdString(qstr);

        db->runQuery(run);


    }
}
void Shop::load(int i, dbControl *dbc)
{
    id = i;
    db = dbc;
}
