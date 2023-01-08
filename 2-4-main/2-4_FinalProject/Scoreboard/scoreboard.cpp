#include "scoreboard.h"
#include "ui_scoreboard.h"

ScoreBoard::ScoreBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);
    dbControl test;
    db = &test;
    db->openDB();



    QSqlQuery qry = test.runQuery("select * from Organizer order by Overall_Points  desc limit 5");


    int counter = 0;
    while (qry.next()){

        if (counter == 0){

            ui->textEdit_13->setText(qry.value(1).toString());
            ui->textEdit_9->setText(qry.value(8).toString());
        }
        else if(counter == 1){

            ui->textEdit_12->setText(qry.value(1).toString());
            ui->textEdit_8->setText(qry.value(8).toString());
        }
        else if(counter == 2){

            ui->textEdit_11->setText(qry.value(1).toString());
            ui->textEdit_7->setText(qry.value(8).toString());
        }
        else if(counter == 3){

            ui->textEdit_4->setText(qry.value(1).toString());
            ui->textEdit_6->setText(qry.value(8).toString());
        }
        else if(counter == 4){

            ui->textEdit_10->setText(qry.value(1).toString());
            ui->textEdit_3->setText(qry.value(8).toString());
        }




        counter ++;
    }


//    std::string your = "PLACE" + test.


//            NAME:

//            SCORE:

//            POINTS:

//            RANK:

//            CLOSEST COLLEAGUE:

//"
//    ui->textEdit_18->setText()








}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}
void ScoreBoard::load(int id){

    //
    int score = stoi(db->getField(8,id,"Organizer"));
    int rank = 0;
    int highestLow;
    std::string name;
    QSqlQuery qry = db->runQuery("select * from Organizer");

    while (qry.next()){

        if (qry.value(8).toInt() > score){

            rank++;
        }
        if (qry.value(8).toInt() < score && qry.value(8).toInt() > highestLow){

            name = qry.value(1).toInt();
            highestLow = qry.value(8).toInt();
        }



    }



       std::string your = " NAME:"  + db->getField(1,id,"Oraganizer") + "/n" + "POINTS" + std::to_string(score) + "PLACE: " + std::to_string(rank) +

             "CLOSEST COLLEAGUE: " + name;


        ui->textEdit_18->setText(QString::fromStdString(your) );

        qry = db->runQuery("select * from Organizer order by Overall_Points  desc limit 5");


        int counter = 0;
        while (qry.next()){

            if (counter == 0){

                ui->textEdit_13->setText(qry.value(1).toString());
                ui->textEdit_9->setText(qry.value(8).toString());
            }
            else if(counter == 1){

                ui->textEdit_12->setText(qry.value(1).toString());
                ui->textEdit_8->setText(qry.value(8).toString());
            }
            else if(counter == 2){

                ui->textEdit_11->setText(qry.value(1).toString());
                ui->textEdit_7->setText(qry.value(8).toString());
            }
            else if(counter == 3){

                ui->textEdit_4->setText(qry.value(1).toString());
                ui->textEdit_6->setText(qry.value(8).toString());
            }
            else if(counter == 4){

                ui->textEdit_10->setText(qry.value(1).toString());
                ui->textEdit_3->setText(qry.value(8).toString());
            }




            counter ++;
        }



}
