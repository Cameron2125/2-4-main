#include "shop.h"
#include "ui_shop.h"

Shop::Shop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Shop)
{
    ui->setupUi(this);
    UI = true;
}

Shop::~Shop()
{
    if (UI){
    delete ui;
    }
}
Shop::Shop(int i)
{
    UI = false;
}
void Shop::on_pushButton_clicked()
{

    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 400);

    //if allowed then db is updated
    if ( score > 400){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -400, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",1" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);


        //image loaded into screen
        purchased(":/images/resources/shop1.PNG");
    }
}

void Shop::on_pushButton_2_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;


    notEnoughPoints(score, 250);

    if ( score > 250){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -250, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",2" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);
        purchased(":/images/resources/shop2.PNG");
    }
}

void Shop::on_pushButton_3_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;


    notEnoughPoints(score, 500);
    if ( score > 500){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -500, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",3" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);
        purchased(":/images/resources/shop3.PNG");

    }
}
void Shop::on_pushButton_4_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;


    notEnoughPoints(score, 800);
    if ( score > 800){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -800, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",4" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);
        purchased(":/images/resources/shop4.PNG");
    }
}

void Shop::on_pushButton_5_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;


    notEnoughPoints(score, 1500);

    if ( score > 1500){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -1500, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",5" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);
        purchased(":/images/resources/shop5.PNG");
    }
}

void Shop::on_pushButton_6_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 1500);
    if ( score > 1500){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -1500, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",6" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop6.PNG");

    }
}

void Shop::on_pushButton_7_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 200);
    if ( score > 200){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -200, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",7" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop7.PNG");

    }
}

void Shop::on_pushButton_8_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History") +1;

    notEnoughPoints(score, 300);
    if ( score > 300){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -300, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",8" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop8.PNG");

    }
}

void Shop::on_pushButton_9_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 1000);
    if ( score > 1000){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -1000, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",9" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop9.PNG");

    }
}

void Shop::on_pushButton_10_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 350);
    if ( score > 350){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -350, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",10" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);
        purchased(":/images/resources/shop10.PNG");
    }
}

void Shop::on_pushButton_11_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 1000);
    if ( score > 1000){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -1000, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",11" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop11.PNG");

    }
}

void Shop::on_pushButton_12_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 500);
    if ( score > 500){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -500, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",12" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop12.PNG");

    }
}

void Shop::on_pushButton_13_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 800);
    if ( score > 800){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -800, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);
        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",13" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop13.PNG");

    }
}

void Shop::on_pushButton_14_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 750);
    if ( score > 750){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -750, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",14" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        purchased(":/images/resources/shop14.PNG");

    }
}

void Shop::on_pushButton_15_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 700);
    if ( score > 700){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -700, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",15" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);
        purchased(":/images/resources/shop15.PNG");

    }
}

void Shop::on_pushButton_16_clicked()
{
    int score = stoi(db->getField(8,id,"Organizer"));
    int hid = db->getMaxValue("HID", "Point_History")+1;

    notEnoughPoints(score, 150);
    if ( score > 150){

        // current date and time on the current system
        time_t now = time(0);

        // convert now to string form
        std::string date_time = ctime(&now);

        std::string qstr = "insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values "
                           "(" + std::to_string(hid) + ", " + std::to_string(id) + ", 'shop', -150, '" + date_time + "')";
        QString run = QString::fromStdString(qstr);

        db->runQuery(run);

        qstr = "UPDATE Organizer SET Shop = '"  + db->getField(10,id,"Organizer")+ ",16" + "'" + " WHERE VID = " + std::to_string(id);
        run = QString::fromStdString(qstr);

        db->runQuery(run);

        //purchased(":/images/resources/shop16.PNG");

    }
}

void Shop::load(int i, dbControl *dbc)
{
    id = i;
    db = dbc;
}

void Shop::load2(QString pic)
{

}

void Shop::closeEvent (QCloseEvent *event)
{
    emit editClosed(id,  db);

    hide();
}

void Shop::notEnoughPoints(int points, int price){
    if(points < price){
        QMessageBox::about(this, "OH NO", "You do not have enough points to purchase this badge");
    }
}

void Shop::purchased(QString pic){
    pb = new PurchasedBadge(this);

    QObject::connect(this, &Shop::toPurchasedBadge,
                     pb, &PurchasedBadge::load);

    QObject::connect(pb, &PurchasedBadge::editClosed,
                     this, &Shop::load2);

    emit toPurchasedBadge(pic);

    pb->show();

    pb->load(pic);

}
