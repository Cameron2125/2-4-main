#include "datagui.h"
#include "ui_datagui.h"

DataGui::DataGui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataGui)
{
    ui->setupUi(this);
    isUI = true;
    ui->comboBox->addItem("Age Distribution");
    ui->comboBox->addItem("Ethnicity Distribution");
    ui->comboBox->addItem("Education Distribution");


}
DataGui::DataGui(int i){


    isUI = false;


}
DataGui::~DataGui()
{
    if (isUI){
    delete ui;
    }

}


void DataGui::on_pushButton_2_clicked()
{
    //pull the user's selection for the type of graph and data to use
    QString selection = ui->comboBox->currentText();
    QString selection2 = ui->comboBox_2->currentText();
    std::vector<double> ageVal;
    std::vector<std::string> name;



    if (selection.size() < 2 || selection2.size() < 2 ){

        return;
    }


    //prepare the data for displaying using interest based on age
    if (selection.toStdString().compare("Interest Based On Age") == 0){
        double total = 0;

        for (int i = 0; i < 110; i++){



            total += getAverage(i,4,12, "Contacts");

            //pull the ages of every contact into several age groups
            if (i%10 == 0 & i != 0){

                ageVal.push_back(total/10.0);
                std::string entry = std::to_string(i-10) + "-" +std::to_string(i);
                name.push_back(entry);
                total = 0.0;

            }


        }
        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,ageVal,"Interest Based On Age");
        }
        else{
            this->createPie(name,ageVal,"Interest Based On Age");
        }

    }
    //prepare the data for displaying using interest based on organizer
    else if (selection.toStdString().compare("Interest Based On Organizer") == 0){


        //pull the names of the organizers
        name = db->getList(1,"Organizer");

        std::vector<std::string> ids = db->getList(0,"Organizer");

        for (int i =0; i < ids.size(); i++ ){

            if ( stoi(ids[i]) == 5){
             int x = 10;

            }
            double count = 0;
            double total = 0;
            //pull the contacts for each organizer and prepare the counts for the graph
            QString qstr = QString::fromStdString("Select * from Contacts WHERE VID =" + ids[i]);
            QSqlQuery qry = db->runQuery(qstr);

            while (qry.next()){

                total += qry.value(12).toInt();
                count++;


            }

            ageVal.push_back(total/count);



        }
        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,ageVal,"Interest Based On Organizer");
        }
        else{
            this->createPie(name,ageVal,"Interest Based On Organizer");
        }



    }
    //prepare the data for displaying using interest based on contact type
    else if (selection.toStdString().compare("Interest Based On Contact Type") == 0){

        std::vector<std::string> response = db->getList(12,1,1,"Contacts");

        double total = 0;
        int count = 0;


        //getting totals for groups assigned to peer contact
        for (int i =0; i < response.size(); i++){

            try {
                total+= stoi(response[i]);
                count++;
            } catch (...) {
            }


        }

        ageVal.push_back(total/count);
        response = db->getList(12,0,1,"Contacts");

        //count the number of Contacts who volunteered based on how they were contacted
        total = 0;
        count = 0;
        for (int i =0; i < response.size(); i++){

            try {
                total+= stoi(response[i]);
                count++;
            } catch (...) {
            }

        }

        if (count ==0){

            count =1;
        }
        ageVal.push_back(total/count);

        name.push_back("Peer to Peer Contact");
        name.push_back("Generic Contact");

        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,ageVal,"Interest Based On Contact Type");
        }

        else{
            this->createPie(name,ageVal,"Interest Based On Contact Type");
        }



    }
    //prepare the data for displaying using interest based on ethnicity
    else if (selection.toStdString().compare("Interest Based On Ethnicity") == 0){

        //pull the interest of every contact based on their ethnicity
        ageVal =  ethInterest();

        //prepare the labels for the chart for each ethnicity
        name.push_back("Black");
        name.push_back("White");
        name.push_back("Asian");
        name.push_back("Hispanic");
        name.push_back("Native American");
        name.push_back("Other");

        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,ageVal,"Interest Based On Ethnicity");
        }

        else{
            this->createPie(name,ageVal,"Interest Based On Ethnicity");
        }

    }
    //prepare the data for displaying using interest based on education
    else if (selection.toStdString().compare("Interest Based On Education") == 0){

        //pull the interest of every contact based on their level of education
        ageVal =  eduInterest();

        //prepare the labels for the chart for each level of education
        name.push_back("High School");
        name.push_back("College");
        name.push_back("Masters");
        name.push_back("Doctoral");
        name.push_back("Other");

        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,ageVal,"Interest Based On Education");
        }

        else{
            this->createPie(name,ageVal,"Interest Based On Education");
        }

    }
    //prepare the data for displaying based on the contact's ethnicity
    else if (selection.toStdString().compare("Ethnicity Distribution") == 0){

        //prepare the labels for the chart for each ethnicity
        name.push_back("Black");
        name.push_back("White");
        name.push_back("Asian");
        name.push_back("Hispanic");
        name.push_back("Native American");
        name.push_back("Other");

        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,ethDist(),"Ethnicity Distribution");
        }

        else{
            this->createPie(name,ethDist(),"Ethnicity Distribution");
        }

    }
    //prepare the data for displaying based on the contact's level of education
    else if (selection.toStdString().compare("Education Distribution") == 0){

        //prepare the labels for the chart for each level of education
        name.push_back("High School");
        name.push_back("College");
        name.push_back("Masters");
        name.push_back("Doctoral");
        name.push_back("Other");


        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,eduDist(),"Education Distribution");
        }

        else{
            this->createPie(name,eduDist(),"Education Distribution");
        }

    }
    //prepare the data for displaying based on the contact's age
    else if (selection.toStdString().compare("Age Distribution") == 0){

        double total = 0;
        //pull the age of every contact
        for (int i = 0; i < 110; i++){


            std::string run1= "SELECT * FROM Contacts WHERE Age = " + std::to_string(i);
            QSqlQuery qry = db->runQuery(QString::fromStdString(run1));

            int count = 0;
            while (qry.next()){


                count++;
            }

            total += count;
            if (i%10 == 0 & i != 0){

                ageVal.push_back(total);
                std::string entry = std::to_string(i-10) + "-" +std::to_string(i);
                name.push_back(entry);
                total = 0.0;

            }


        }
        //create a bar graph or pie chart based on the user's choice
        if (selection2.indexOf("ar G") > 0){
            this->createBar(name,ageVal,"Age Distribution");
        }
        else{
            this->createPie(name,ageVal,"Age Distribution");
        }

    }








}
double DataGui::getAverage(int id, int colum, int valcol, std::string table){
    //QApplication a;
    //DataGui w;
    //w.show();


    QSqlQuery qry;

    //get the average value from the chosen column from the given tables
     qry = db->runQuery(QString::fromStdString("select * from " + table));
    int total =0;
    int count = 0;
    while(qry.next()){

        if (qry.value(colum).toInt() == id){


            total += qry.value(valcol).toInt();
            count++;
        }


    }


    if (total  <1 & count <1){

        return 0.0;
    }
    return (double) total / (double) count;





}
void DataGui::createBar(std::vector<std::string> names,std::vector<double> data, std::string name){
    //prepare the bar graph using the QtCharts framework
    QBarSeries *series = new QBarSeries();
    QStringList categories;
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QBarSet *set0 = new QBarSet("");

    //add the names of the labels for the x axis
    for (int i = 0; i < names.size(); i ++){


        categories << QString::fromStdString(names[i]);


    }

    double top = 0;

    //determine the largest value for the y axis
    for (int i =0; i < data.size(); i ++){

        if (data[i] > top){

            top = data[i];
        }
        *set0 << data[i];


    }
    series->append(set0);

    //create the bar chart using the QtCharts framework
    QBarSeries tester(series);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(name));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,top);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    graphs.push_back(chartView);

    ui->horizontalLayout->addWidget(chartView);






}
void DataGui::createPie(std::vector<std::string> names,std::vector<double> data, std::string name){
    //ui->horizontalLayout.
    //prepare the pie chart using the QtCharts framework
    QPieSeries *series = new QPieSeries();

    //add the names of the labels for the data
    for (int i = 0; i < names.size(); i ++){


        series->append(QString::fromStdString(names[i]), data[i]);


    }
    //create the pie slices using the QtCharts framework and the given data
    for (int i =0 ; i < names.size(); i ++){


        QPieSlice *slice = series->slices().at(i);
        QString strng = QString::fromStdString(names[i] + "\n")
                + QString::number((slice->percentage()*100)) + "%";
            slice->setLabel(strng);
            slice->setExploded();
            slice->setLabelVisible();
            slice->setPen(QPen(Qt::black, 2));


    }
    series->setLabelsVisible();





    //![2]
//    QPieSlice *slice = series->slices().at(1);
//    slice->setExploded();
//    slice->setLabelVisible();
//    slice->setPen(QPen(Qt::darkGreen, 2));
//    slice->setBrush(Qt::green);
    //![2]

    //![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(name));
    chart->legend()->hide();
    //![3]

    //![4]
    QChartView *chartView = new QChartView(chart);

    chartView->setRenderHint(QPainter::Antialiasing);
    graphs.push_back(chartView);
    ui->horizontalLayout->addWidget(chartView);
}
void DataGui::createLine(std::vector<double> data1,std::vector<double> data2){




     QLineSeries *series = new QLineSeries();
     for (int i =0; i < data1.size(); i++){


          series->append(data1[i], data2[i]);

     }
     QChart *chart = new QChart();
       chart->legend()->hide();
       chart->addSeries(series);
       chart->createDefaultAxes();
       chart->setTitle("LINE CHART");
       QChartView *chartView = new QChartView(chart);

       graphs.push_back(chartView);
         chartView->setRenderHint(QPainter::Antialiasing);
          ui->horizontalLayout->addWidget(chartView);
}

void DataGui::on_pushButton_clicked()
{
    QString table = ui->comboBox_3->currentText();


    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/jana/untitled.csv",
                               tr("CSV files (*.csv)"));

    std::ofstream myfile;
    myfile.open (fileName.toStdString());






          QString run = QString::fromStdString("SELECT * from ") + table;
          QSqlQuery qry = db->runQuery(run);
          std::vector<std::string> labels;
          QSqlRecord record = qry.record();

          std::string label;

          for (int i = 0; i < record.count(); i ++){

              std::string tName = record.fieldName(i).toStdString();
              labels.push_back(tName);




                  label += tName + ",";




          }


          label = label + "\n";


           myfile << label;

          while (qry.next()){
              std::string inserter;

              for (int i = 0; i < labels.size(); i ++){



                  inserter = inserter + qry.value(i).toString().toStdString() + ",";


              }
              inserter = inserter + "\n";

              myfile << inserter;






          }



          myfile.close();






}
void DataGui::load(dbControl *db2){



    db = db2;
}


void DataGui::on_pushButton_3_clicked()
{


    for (int i = 0; i < graphs.size(); i ++){


        //ui->horizontalLayout->removeWidget(graphs[i]);

        graphs[i]->deleteLater();




    }

    graphs.clear();





}
std::vector<double> DataGui::ethInterest(){

    std::vector<double> data;


    QSqlQuery qry = db->runQuery("Select * from Contacts");
    double sum,sum1,sum2,sum3,sum4, sum5 = 0;
    int cnt,cnt1,cnt2,cnt3,cnt4,cnt5 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;
    sum5 =0;
    cnt = 0;
    cnt1 = 0;
    cnt2 = 0;
    cnt3 = 0;
    cnt4 = 0;
    cnt5 = 0;
    //black,white,asian,hispanic, americna indian, other

    while (qry.next()){
        std::string data = qry.value(7).toString().toStdString();
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (data.compare("black") == 0 ||data.compare("african american") == 0){
            sum += qry.value(12).toInt();
            cnt ++;


        }
        if (data.compare("white") == 0){
            sum1 += qry.value(12).toInt();
            cnt1 ++;


        }
        if (data.compare("asian") == 0){
            sum2 += qry.value(12).toInt();
            cnt2 ++;


        }
        if (data.compare("hispanic") == 0){
            sum3 += qry.value(12).toInt();
            cnt3 ++;

        }
        if (data.compare("native american") == 0){
            sum4 += qry.value(12).toInt();
            cnt4 ++;


        }
        else{

            sum5 += qry.value(12).toInt();
            cnt5 ++;


        }


    }

    if (cnt ==0){

        cnt =1;
    }
    if (cnt1 ==0){

        cnt1 =1;
    }
    if (cnt2 ==0){

        cnt2 =1;
    }
    if (cnt3 ==0){

        cnt3 =1;
    }
    if (cnt4 ==0){

        cnt4 =1;
    }
    if (cnt5 ==0){

        cnt5 =1;
    }
    data.push_back((sum/cnt));
    data.push_back((sum1/cnt1));
    data.push_back((sum2/cnt2));
    data.push_back((sum3/cnt3));
    data.push_back((sum4/cnt4));
    data.push_back((sum5/cnt5));

    return data;
}
std::vector<double> DataGui::eduInterest(){

    std::vector<double> data;


    QSqlQuery qry = db->runQuery("Select * from Contacts");
    double sum,sum1,sum2,sum3,sum4, sum5 = 0;
    int cnt,cnt1,cnt2,cnt3,cnt4,cnt5 = 0;
    sum = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;
    sum5 =0;
    cnt = 0;
    cnt1 = 0;
    cnt2 = 0;
    cnt3 = 0;
    cnt4 = 0;
    cnt5 = 0;



    while (qry.next()){
        std::string data = qry.value(8).toString().toStdString();
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (data.compare("high school") == 0){
            sum += qry.value(12).toInt();
            cnt ++;


        }
        else if (data.compare("college") == 0){
            sum1 += qry.value(12).toInt();
            cnt1 ++;


        }
        else if (data.compare("masters") == 0){
            sum2 += qry.value(12).toInt();
            cnt2 ++;


        }
        else if (data.compare("doctorate") == 0 || data.compare("doctoral") == 0 ){
            sum3 += qry.value(12).toInt();
            cnt3 ++;

        }
        else{

            sum4 += qry.value(12).toInt();
            cnt4 ++;


        }


    }
    if (cnt ==0){

        cnt =1;
    }
    if (cnt1 ==0){

        cnt1 =1;
    }
    if (cnt2 ==0){

        cnt2 =1;
    }
    if (cnt3 ==0){

        cnt3 =1;
    }
    if (cnt4 ==0){

        cnt4 =1;
    }
    data.push_back((sum/cnt));
    data.push_back((sum1/cnt1));
    data.push_back((sum2/cnt2));
    data.push_back((sum3/cnt3));
    data.push_back((sum4/cnt4));

    return data;



}
std::vector<double> DataGui::ethDist(){

    std::vector<double> data;


    QSqlQuery qry = db->runQuery("Select * from Contacts");




        int cnt,cnt1,cnt2,cnt3,cnt4,cnt5 = 0;
        cnt = 0;
        cnt1 = 0;
        cnt2 = 0;
        cnt3 = 0;
        cnt4 = 0;
        cnt5 = 0;
        //black,white,asian,hispanic, americna indian, other

        while (qry.next()){
            std::string data = qry.value(7).toString().toStdString();
            std::transform(data.begin(), data.end(), data.begin(),
                [](unsigned char c){ return std::tolower(c); });

            if (data.compare("black") == 0 ||data.compare("african american") == 0){

                cnt ++;


            }
            if (data.compare("asian") == 0){

                cnt1 ++;


            }
            if (data.compare("white") == 0){

                cnt2 ++;


            }
            if (data.compare("hispanic") == 0){

                cnt3 ++;

            }
            if (data.compare("native american") == 0){

                cnt4 ++;


            }
            else{


                cnt5 ++;


            }

}
            data.push_back(cnt);
            data.push_back(cnt1);
            data.push_back(cnt2);
            data.push_back(cnt3);
            data.push_back(cnt4);
            data.push_back(cnt5);

            return data;



}

std::vector<double> DataGui::eduDist(){
    std::vector<double> data;


    QSqlQuery qry = db->runQuery("Select * from Contacts");
    int cnt,cnt1,cnt2,cnt3,cnt4,cnt5 = 0;

    cnt = 0;
    cnt1 = 0;
    cnt2 = 0;
    cnt3 = 0;
    cnt4 = 0;
    cnt5 = 0;



    while (qry.next()){
        std::string data = qry.value(8).toString().toStdString();
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (data.compare("high school") == 0){

            cnt ++;


        }
        else if (data.compare("college") == 0){

            cnt1 ++;


        }
        else if (data.compare("masters") == 0){

            cnt2 ++;


        }
        else if (data.compare("doctorate") == 0 || data.compare("doctoral") == 0 ){

            cnt3 ++;

        }
        else{


            cnt4 ++;


        }


    }
    if (cnt ==0){

        cnt =1;
    }
    if (cnt1 ==0){

        cnt1 =1;
    }
    if (cnt2 ==0){

        cnt2 =1;
    }
    if (cnt3 ==0){

        cnt3 =1;
    }
    if (cnt4 ==0){

        cnt4 =1;
    }
    data.push_back((cnt));
    data.push_back((cnt1));
    data.push_back((cnt2));
    data.push_back((cnt3));
    data.push_back((cnt4));

    return data;





}


