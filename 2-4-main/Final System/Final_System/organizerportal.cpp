#include "organizerportal.h"
#include "ui_organizerportal.h"


OrganizerPortal::OrganizerPortal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrganizerPortal)
{
    ui->setupUi(this);

}

OrganizerPortal::~OrganizerPortal()
{
    delete ui;
}

void OrganizerPortal::on_Scoreboard_clicked()
{
    //emittign signal to scoreboard and opening that window
    board = new ScoreBoard(this);

    QObject::connect(this, &OrganizerPortal::toOrganizerPortal,
                     board, &ScoreBoard::load);

    QObject::connect(board, &ScoreBoard::editClosed,
                     this, &OrganizerPortal::load);

    emit toOrganizerPortal(vids, db);

    board->show();

    board->load(vids, db);
}


void OrganizerPortal::on_ContactManager_clicked()
{
    //create the contact manager widget and connect to it
    manage = new contactman(this);

    QObject::connect(this, &OrganizerPortal::toContactManagerPortal,
                     manage, &contactman::load);

    QObject::connect(manage, &contactman::editClosed,
                     this, &OrganizerPortal::load);

    //emit user id and dbControl object to the widget
    emit toContactManagerPortal(vids, db);

    manage->show();

    manage->load(vids, db);

}


void OrganizerPortal::on_addinfo_clicked()
{
    //create the additional information widget and connect to it
    add = new additionalInformation(this);

    QObject::connect(this, &OrganizerPortal::toadditionalInformationPortal,
                     add, &additionalInformation::load);

    QObject::connect(add, &additionalInformation::editClosed,
                     this, &OrganizerPortal::load);

    //emit user id and dbControl object to the widget
    emit toadditionalInformationPortal(vids, db);

    add->show();

    add->load(vids, db);

}

void OrganizerPortal::load(int vid, dbControl *t) {

    //load the dbControl object and user id
    db = t;
    vids = vid;

    //obtain the point history for the user
    QSqlQuery qry;
    qry.prepare("select Point_Value from Point_History where VID = :vid");
    qry.bindValue(":vid", vid);
    if(!qry.exec()){
        QMessageBox::warning(this, "Database Error", qry.lastError().text());
    }
    int sum = 0;
    while(qry.next()){
        sum += qry.value(0).toInt();
    }

    //set the score of the user to the correct value based on history
    qry.prepare("update Organizer set Overall_Points = :score where VID = :vid");
    qry.bindValue(":score", sum);
    qry.bindValue(":vid", vid);

    if(!qry.exec()){
        QMessageBox::warning(this, "Database Error", qry.lastError().text());
    }

    //pull the score of the user to display
    qry.prepare("select Overall_Points from Organizer where VID = :vid");
    qry.bindValue(":vid", vid);

    if(!qry.exec()){
        QMessageBox::warning(this, "Database Error", qry.lastError().text());
    }
    int points = 0;
    while(qry.next()){
        points = qry.value(0).toInt();
    }

    //pull the name of the user to display
    qry.prepare("select Name from Organizer where VID = :vid");
    qry.bindValue(":vid", vid);

    if(!qry.exec()){
        QMessageBox::warning(this, "Database Error", qry.lastError().text());
    }
    QString name = "";
    while(qry.next()){
        name = qry.value(0).toString();
    }

    //display the score of the user in the UI
    ui->label->setText("Points " + QString::number(points));
    ui->label->setVisible(true);

    //display the correct badge
    this->rankDisplay(vid);
    try {
        this->shopBadges(vid);
    } catch (...) {
    }

    //display the name of the user in the UI
    this->setWindowTitle("Welcome " + name);
    this->friendToFriendContacts(vid);
}

void OrganizerPortal::rankDisplay(int id){

    //obtain the total point value of the user
    QString vid = QString::fromStdString(std::to_string(id));
    QString run = QString::fromStdString("Select * from Organizer WHERE VID =") + vid;

    QSqlQuery qry = db->runQuery(run);

    //display the correct badge based on the user's score
    while (qry.next()){
        if (qry.value(8).toInt() > 1000){

            ui->rankLabel->setStyleSheet("image: url(resources/badge7-removebg-preview.png)");
        }
        else if (qry.value(8).toInt() > 750){

            ui->rankLabel->setStyleSheet("image: url(resources/badge6-removebg-preview.png)");

        }
        else if (qry.value(8).toInt() > 500){

            ui->rankLabel->setStyleSheet("image: url(resources/badge5-removebg-preview.png)");

        }
        else if (qry.value(8).toInt() > 100){

            ui->rankLabel->setStyleSheet("image: url(resources/badge4-removebg-preview.png)");

        }
        else if (qry.value(8).toInt() > 50){

            ui->rankLabel->setStyleSheet("image: url(Cresources/badge3-removebg-preview.png)");

        }
        else if (qry.value(8).toInt() > 20){

            ui->rankLabel->setStyleSheet("image: url(resources/badge2-removebg-preview.png)");

        }
        else {

            ui->rankLabel->setStyleSheet("image: url(resources/badge1-removebg-preview.png)");

        }


    }


}

void OrganizerPortal::friendToFriendContacts(int id){
    QFont serifFontBold("Arial", 15, QFont::Bold);
    QFont serifFont("Arial", 12);

    //pull the friend to friend contacts the user still needs to recruit
    QString vid = QString::fromStdString(std::to_string(id));
    QLabel *title = new QLabel;
    ftfclabels.push_back(title);
    QString run = QString::fromStdString("Select Name from Contacts WHERE VID =") + vid + QString::fromStdString(" and Contact_Type = 1");
    QSqlQuery qry = db->runQuery(run);

    //display these contacts in the UI
    QString add = "";
    while(qry.next()){
        add += qry.value(0).toString() + "\n";
    }
    ui->textEdit->setText(add);

}

void OrganizerPortal::clearLayout(){
    //clear the labels for the friend to friend contacts
    while(!ftfclabels.empty()){
        QLabel *r = ftfclabels.back();
        ftfclabels.pop_back();
    }

}
void OrganizerPortal::shopBadges(int id){

    //pull the data on the current user
    QString vid = QString::fromStdString(std::to_string(id));
    QString run = QString::fromStdString("Select * from Organizer WHERE VID =") + vid;

    QSqlQuery qry = db->runQuery(run);

    while (qry.next()){
        //pull the ids of every badge the user has bought
        std::vector<std::string> shop = splitString(qry.value(10).toString().toStdString(),",");

        int difference =  shop.size() - badges.size();

        //display all of the shop badges the user has bought based on their ids
        for (int i = badges.size(); i < shop.size(); i++ ){
            if (stoi(shop[i]) == 1){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop1.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 2){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop2.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 3){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop3.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 4){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop4.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 5){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop5.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 6){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop6.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 7){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop7.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 8){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop8.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 9){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop9.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 10){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop10.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 11){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop11.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 12){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop12.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 13){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop13.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 14){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop14.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 15){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop15.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else if (stoi(shop[i]) == 16){

                QLabel *add = new QLabel;
                add->setStyleSheet("image: url(resources/shop16.PNG)");

                badges.push_back(add);

                ui->gridLayout_2->addWidget(add);
            }
            else{

            }
        }
    }
}


void OrganizerPortal::on_seeIncent_pressed()
{
    //create a new incentive viewer widget and connect to it
    incent = new IncentiveViewer(this);

    QObject::connect(this, &OrganizerPortal::toincentiveViewer,
                     incent, &IncentiveViewer::load);

    QObject::connect(incent, &IncentiveViewer::editClosed,
                     this, &OrganizerPortal::load);

    //emit user id and dbControl object to the widget
    emit toincentiveViewer(vids, db);

    incent->show();

    incent->load(vids, db);
}

std::vector<std::string>  OrganizerPortal::splitString(std::string list, std::string seperator){

    //split the given string based on a chosen separator
    std::vector<std::string> words;
    int begining = 0;
    int endIndex = list.find(seperator);

    while (endIndex != -1) {
        words.push_back(list.substr(begining, endIndex - begining));
        begining = endIndex + seperator.size();
        endIndex = list.find(seperator, begining);
    }
    words.push_back(list.substr(begining, endIndex - begining));
    return words;
}

void OrganizerPortal::on_pushButton_clicked()
{
    //create a new shop widget and connect to it
    shop = new Shop(this);

    QObject::connect(this, &OrganizerPortal::toShop,
                     shop, &Shop::load);

    QObject::connect(shop, &Shop::editClosed,
                     this, &OrganizerPortal::load);

    //emit user id and dbControl object to the widget
    emit toOrganizerPortal(vids, db);

    shop->show();

    shop->load(vids, db);
}


void OrganizerPortal::closeEvent (QCloseEvent *event)
{
    close();
}


