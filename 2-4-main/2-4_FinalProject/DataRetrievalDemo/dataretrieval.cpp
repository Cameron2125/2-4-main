#include "dataretrieval.h"
#include "ui_dataretrieval.h"


DataRetrieval::DataRetrieval(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataRetrieval)
{
    ui->setupUi(this);

    //dbControl dBase;
    //dBase.openDB();
    dBases = new dbControl;
    //1 int 3 string

    QSqlQuery qry = dBases->runQuery("select * from Contacts");

    std::vector<std::string> labels;
    std::vector<int> labelstypes;
    QSqlRecord record = qry.record();

    for (int i = 0; i < record.count(); i ++){

        std::string tName = record.fieldName(i).toStdString();
        std::transform(tName.begin(), tName.end(), tName.begin(),
            [](unsigned char c){ return std::tolower(c); });
        //std::cout << tName <<std::endl;
        labelstypes.push_back(record.field(i).typeID() );
        labels.push_back(tName);




    }

    types = labelstypes;


    while (qry.next() ) {
        std::string contact = "";
        for (int i = 0; i < record.count(); i++){

         std::string adder = qry.value(i).toString().toStdString();



         //add similar if statment for VID to change number into volunteer name
            if (i == 12){

                if (qry.value(i).toInt() == 1){

                    adder = "volunteered";
                }
                else if (qry.value(i).toInt() == 2){

                    adder = "Interested in Volunteering";
                }
                else{

                    adder = "not volunteered";
                }

            }
        if (i != labels.size()-1){

        contact = contact + adder + ", ";

        }
        else {

            contact = contact + adder;
        }

        }
        std::cout << contact << std::endl;
        ui->allContacts->addItem(QString::fromStdString(contact));

    }
    std::string total;
    for (int i = 0; i < labels.size(); i++){
        std::string add;
    if (i != labels.size()-1){
     add =labels.at(i) + ", ";
    }
    else{
     add = labels.at(i);

    }
    total = total + add;
    }
    lName = labels;
    ui->label_5->setText(QString::fromStdString(total));
    ui->label_6->setText(QString::fromStdString(total));



}
void DataRetrieval::on_submit_clicked(){

     ui->search->clear();
    QString feild = ui->feildName->text();
    QString keyword = ui->keyword->text();
    feild = feild.toLower();
    keyword = keyword.toLower();



    QSqlQuery qry;

    QString run = QString::fromStdString("SELECT * from Contacts");
    qry = dBases->runQuery(run);


    int colum = 0;
    int type = 0;

    for (int i = 0; i < lName.size(); i ++ ){

        if (feild.contains(QString::fromStdString(lName.at(i)))){
            colum = i;
            type = types.at(i);

        }




    }

//    if (feild.contains("contact number")){

//    }
//    if (feild.contains("vid")){
//       colum = 1;
//    }
//    if (feild.contains("contact status")){
//       colum = 2;
//    }
//    if (feild.contains("name")){
//       colum = 3;
//    }
//    if (feild.contains("age")){
//       colum = 4;
//    }

    if (type == 1){
    while (qry.next() ) {
        std::string contact = "";
        if (qry.value(colum).toInt() == keyword.toInt()){
            for (int i = 0; i < lName.size(); i++){
                std::string adder = qry.value(i).toString().toStdString();
                //add similar if statment for VID to change number into volunteer name
                   if (i == 12){

                       if (qry.value(i).toInt() == 1){

                           adder = "volunteered";
                       }
                       else{

                           adder = "not volunteered";
                       }

                   }
               if (i != lName.size() -1){
               contact = contact + adder + ", ";
               }
               else {

                   contact = contact + adder;
               }
            }

            ui->search->addItem(QString::fromStdString(contact));

        }



    }
    }
    else if (type == 3){
        while (qry.next() ) {
            std::string contact = "";
            std::string print = qry.value(colum).toString().toStdString();

            std::cout << print << std::endl;
            std::cout << keyword.toStdString() << std::endl;
            if (qry.value(colum).toString().toLower().contains(keyword)){
                for (int i = 0; i < lName.size(); i++){
                contact = contact + qry.value(i).toString().toStdString();
                }

                ui->search->addItem(QString::fromStdString(contact));

            }



        }



    }





}
DataRetrieval::~DataRetrieval()
{
    this->dBases->closeDB();
    delete ui;
}


void DataRetrieval::on_search_itemDoubleClicked(QListWidgetItem *item)
{


    QString ids = item->text();

    QObject::connect(this, &DataRetrieval::toContactAttempt,
                     CA, &ContactAttempts::load);

    emit toContactAttempt(ids, *dBases);
    hide();
    CA->show();







}



