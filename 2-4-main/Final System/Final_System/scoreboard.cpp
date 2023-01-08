#include "scoreboard.h"
#include "ui_scoreboard.h"

ScoreBoard::ScoreBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);

}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}
void ScoreBoard::load(int id, dbControl *t){

    //loading in the class variables
    vid = id;
    db = t;

    QSqlQuery qry = db->runQuery("select * from Organizer order by Overall_Points  desc limit 5");

    int counter = 0;

    //setting the top 5 display
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

    //getting the score of organizer
    int score = stoi(db->getField(8,id,"Organizer"));
    int rank = 1;
    int highestLow;
    std::string name;
     qry = db->runQuery("select * from Organizer");

     //determining the rank and cloester compeititor
    while (qry.next()){

        if (qry.value(8).toInt() > score){

            rank++;
        }
        if (qry.value(8).toInt() < score && qry.value(8).toInt() > highestLow){

            name = qry.value(1).toString().toStdString();
            highestLow = qry.value(8).toInt();
        }



    }

        //setting the side screen info
       std::string names = db->getFeild(1,id,0,"Oragnaizer");
       std::string names2 = db->getField(1,id,"Organizer");
       std::string your = " NAME:"  + names2 + "\n" +  "POINTS: " + std::to_string(score) + "\n" +  "PLACE: " + std::to_string(rank) +

            + "\n" +  "CLOSEST COLLEAGUE: " + name;


        ui->textEdit_18->setText(QString::fromStdString(your) );





}

void ScoreBoard::on_pushButton_clicked()
{
    emit editClosed(vid, db);

    hide();
}

