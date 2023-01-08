#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.openDB("../../resources/sample_db.sqlite");
}

MainWindow::~MainWindow()
{
    delete ui;
    db.closeDB();
}


/////////////////////////////////////////////
/// Login
/////////////////////////////////////////////

void MainWindow::on_Login_But_pressed()
{
    if(validUser() == 1){

        ui->System->setCurrentIndex(1);  //go to organizer
    }
    else if(validUser() == 2){
        ui->System->setCurrentIndex(2); //go to researcher
    }
    else if(validUser() == 3){
        ui->System->setCurrentIndex(3); //go to admin
    }
    else{
        std::cerr << "Invalid User\n";
    }
}


int MainWindow::validUser() {
    QString usernameInput = ui->Username_Edit->text();
    QString passwordInput = ui->Password_Edit->text();
    QString getUser = "select * from Login where Username = '" + usernameInput + "';";
    QSqlQuery qry = db.runQuery(getUser);

    if (qry.next()) {
        QString password = qry.value(2).toString();
        int role = qry.value(3).toInt();
        int LID = qry.value(0).toInt();

        if (passwordInput != password) {
            QMessageBox::information(this, "Login", "Username/password invalid.");
            return NULL;
        }
        else {
            QSqlQuery q;
            if(role == 1){
               q.prepare("select VID from Organizer where LID = :LID");
               q.bindValue(":LID", LID);

               if(!q.exec()){
                   std::cout<< "LID to Name Query doesn't work" << std::endl;
               }
               if(q.next()){
                   userVID = q.value(0).toString();
               }
            }

            return role;
        }
    }
    else {
        QMessageBox::information(this, "Login", "Username/password invalid.");
        return NULL;
    }
}


/////////////////////////////////////////////
/// Organizer Portal
/////////////////////////////////////////////

void MainWindow::on_Enter_Contact_But_pressed()
{
    ui->System->setCurrentIndex(6);
    // Link Tables to View
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Contacts where VID = " + userVID);
    ui->Contact_Table->setModel(model);
}


void MainWindow::on_Log_Recruitment_Attempt_But_pressed()
{
    ui->System->setCurrentIndex(5); //go to recruitment attempt
    setContactGroups();
}


void MainWindow::on_Change_Vol_Stat_But_pressed()
{
    ui->System->setCurrentIndex(4); //go to volunteering status update
    setContactGroups();
}

void MainWindow::setContactGroups()
{
    QListWidget *ftofcontact_list = ui->FtoF_Contact_List;
    QListWidget *contact_list = ui -> Contact_List;
    QString getftofNames = "select Name from Contacts where Contact_Type = 1 and VID =" + userVID;
    QSqlQuery qry = db.runQuery(getftofNames);

    while (qry.next()) {
        QString name = qry.value(0).toString();
        new QListWidgetItem(name, ftofcontact_list);
    }

    QString getNames = "select Name from Contacts;";
    QSqlQuery qry2 = db.runQuery(getNames);

    while (qry2.next()) {
        QString name = qry2.value(0).toString();
        new QListWidgetItem(name, contact_list);
    }
}


/////////////////////////////////////////////
/// Admin Portal
/////////////////////////////////////////////

void MainWindow::on_Add_Incentive_But_pressed()
{
    ui->System->setCurrentIndex(9);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Incentives where Type = 0");
    ui->DP_Table->setModel(model);

    QSqlQueryModel *model2 = new QSqlQueryModel();
    model2->setQuery("SELECT * FROM Incentives where Type = 1");
    ui->TB_Table->setModel(model2);
}


void MainWindow::on_Contact_But_pressed()
{
    ui->System->setCurrentIndex(12);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Contacts");
    ui->DP_Table->setModel(model);
}


void MainWindow::on_Contact_Relation_But_2_pressed()
{

}


/////////////////////////////////////////////
/// Researcher Portal
/////////////////////////////////////////////

void MainWindow::on_View_Contact_But_pressed()
{
    ui->System->setCurrentIndex(12);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Contacts");
    ui->DP_Table->setModel(model);
}


void MainWindow::on_Data_Analysis_But_pressed()
{

}


void MainWindow::on_Contact_Relation_But_1_pressed()
{

}


/////////////////////////////////////////////
/// Change Volunteering Status
/////////////////////////////////////////////

void MainWindow::on_Set_Active_But_pressed()
{
    QSqlQuery q;
    QString updateName = QString::fromStdString(update);
    q.prepare("update Contacts set Contact_Status = 1 where Name = :name");
    q.bindValue(":name", updateName);
    if(!q.exec()){
        std::cout<< "Query doesn't work" << std::endl;
    }
    QString message = updateName + " has been updated.";
    QMessageBox::about(this, "Confirmation", message);
}


void MainWindow::on_Set_Not_Active_But_pressed()
{
    QSqlQuery q;
    QString updateName = QString::fromStdString(update);
    q.prepare("update Contacts set Contact_Status = 0 where Name = :name");
    q.bindValue(":name", updateName);
    if(!q.exec()){
        std::cout<< "Query doesn't work" << std::endl;
    }
    QString message = updateName + " has been updated.";
    QMessageBox::about(this, "Confirmation", message);
}


void MainWindow::on_Return_To_Portal_But_pressed()
{
    ui->System->setCurrentIndex(1); //Return to Organizer Portal
}

void MainWindow::on_Contact_List_itemPressed(QListWidgetItem *item)
{
    QString name = item->text();
    update = name.toStdString();
}


/////////////////////////////////////////////
/// Add Recruitment Attempt
/////////////////////////////////////////////

void MainWindow::on_Yes_Box_pressed()
{
    success = 1;
}


void MainWindow::on_No_Box_pressed()
{
    success = 0;
}


void MainWindow::on_Not_Sure_Box_pressed()
{
    success = 2;
}

void MainWindow::on_FtoF_Contact_List_itemPressed(QListWidgetItem *item)
{
    QString name = item->text();
    update = name.toStdString();
}


void MainWindow::on_Add_Rec_Attempt_But_pressed()
{
    //Get CID
    QString updateName = QString::fromStdString(update);
    QSqlQuery q1;
    q1.prepare("select CID from Contacts where Name = :name");
    q1.bindValue(":name", updateName);

    if(!q1.exec()){
        std::cerr << "Error with Contact_Number query" << std::endl;
    }
    int contNum = 0;
    if(q1.next()){
        contNum = q1.value(0).toInt();
    }
    std::cerr << update << std::endl;
    QString id = QString::number(contNum);

    //Get Attempts
    QSqlQuery q2;
    q2.prepare("select count(*) from Recruitment_Attempts where CID = :id");
    q2.bindValue(":id", id);
    if(!q2.exec()){
        std::cerr << "Error with #R_Attempts query" << std::endl;
    }
    int num_attempts = 0;
    if(q2.next()){
        num_attempts = q2.value(0).toInt();
    }
    std::cerr << num_attempts << std::endl;
    QString attempts = QString::number(num_attempts);

    //Set Date
    int dayDate = ui->Day_Spin->value();
    int monthDate = ui->Month_Spin->value();
    int yearDate = ui->Year_Spin->value();

    Date date;

    QString dateq;
    date.setDate(monthDate, dayDate, yearDate);

    //Only updates if date is valid
    if(date.validateDate(monthDate, dayDate, yearDate)){
        std::string dateString = std::to_string(dayDate) + std::to_string(monthDate) + std::to_string(yearDate);
        dateq = QString::fromStdString(dateString);
    }

    //Set Time
    int hours = ui->Hour_Spin->value();
    int mins = ui->Minute_Spin->value();

    int length = 60 * hours + mins;
    QString lengthq = QString::number(length);

    QString successq = QString::number(success);

    QString response = ui->Response_Text->toPlainText();

    QString additionalInfo = ui->Add_Info_Line->text();

    QSqlQuery q;
    q.prepare("insert into Recruitment_Attempts (CID, Attempt_Number, Date, Sucess, Length, Response, Form_of_Contact, Additional_Info)"
              " values(:cid, :anum, :date, :suc, :length, :res, :foc, :addi)");
    q.bindValue(":cid", id);
    q.bindValue(":anum", attempts);
    q.bindValue(":date", dateq);
    q.bindValue(":suc", successq);
    q.bindValue(":length", lengthq);
    q.bindValue(":res", response);
    q.bindValue(":foc", "not");
    q.bindValue(":addi", additionalInfo);

    if(!q.exec()){
        std::cout << q.executedQuery().toStdString() << std::endl;
        std::cout<< "Query doesn't work" << std::endl;
    }

}

void MainWindow::on_Return_To_Portal_But_2_pressed()
{
    ui->System->setCurrentIndex(1); //Return to Organizer Portal
}

/////////////////////////////////////////////
/// Input Contacts
/////////////////////////////////////////////

void MainWindow::on_Input_Contacts_Man_But_pressed()
{
    ui->System->setCurrentIndex(7); //go to add input man
}

void MainWindow::on_Input_Contacts_csv_But_pressed()
{
    // Prompt user to choose file, record string
    QString fileDirectory =
    QFileDialog::getOpenFileName(this, "Choose file to import", "directoryToOpen",
        "CSV files (*.csv);;Text files (*.txt)");

    // Return if file is not csv
    if (fileDirectory.endsWith(".csv") == false)
    {
        QMessageBox::warning(this, "Error", "File must be a CSV file");
        return;
    }

    // Link Tables to View
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Contacts");
    ui->Contact_Table->setModel(model);

    // Import File
    QFile contactFile(fileDirectory);
    // Attempt to read, error message if not successful
    if (!contactFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Contact File Read Error", contactFile.errorString());
        return;
    }

    // Read each line of the csv and insert into database
    QTextStream in(&contactFile);

    // Store an array of indexes for each coloumn referring to the actual index in the file
    int indexArray[15];
    // Initialize the array to -1
    for (int i = 0; i < 15; i++)
    {
        indexArray[i] = -1;
    }
    // First read line 1
    QString line = in.readLine();
    // Split line into a QStringList, using a csv format
    QStringList lineList = line.split(",");
    // Escape quotes
    lineList.replaceInStrings("\"", "");

    // If lineList has less than 5 elements, error message and return
    if (lineList.size() < 15)
    {
        QMessageBox::warning(this, "Error", "File format is incorrect");
        return;
    }

    // Find the index of each column
    for (int i = 0; i < lineList.size(); i++)
    {
        // If the column is VID, store the index in indexArray[0]
        if (lineList[i] == "VID")
        {
            indexArray[0] = i;
        }
        // If the column is Contact_Type, store the index in indexArray[1]
        else if (lineList[i] == "Contact_Type")
        {
            indexArray[1] = i;
        }
        // If the column is CID, store the index in indexArray[2]
        else if (lineList[i] == "CID")
        {
            indexArray[2] = i;
        }
        // If the column is Name, store the index in indexArray[3]
        else if (lineList[i] == "Name")
        {
            indexArray[3] = i;
        }
        // If the column is Age, store the index in indexArray[4]
        else if (lineList[i] == "Age")
        {
            indexArray[4] = i;
        }
        // If the column is Location, store the index in indexArray[5]
        else if (lineList[i] == "Location")
        {
            indexArray[5] = i;
        }
        // If the column is Gender, store the index in indexArray[6]
        else if (lineList[i] == "Gender")
        {
            indexArray[6] = i;
        }
        // If the column is Ethnicity, store the index in indexArray[7]
        else if (lineList[i] == "Ethnicity")
        {
            indexArray[7] = i;
        }
        // If the column is Education, store the index in indexArray[8]
        else if (lineList[i] == "Education")
        {
            indexArray[8] = i;
        }
        // If the column is Occupation, store the index in indexArray[9]
        else if (lineList[i] == "Occupation")
        {
            indexArray[9] = i;
        }
        // If the column is Email, store the index in indexArray[10]
        else if (lineList[i] == "Email")
        {
            indexArray[10] = i;
        }
        // If the column is Phone_Num, store the index in indexArray[11]
        else if (lineList[i] == "Phone_Number")
        {
            indexArray[11] = i;
        }
        // If the column is Contact_Stat, store the index in indexArray[12]
        else if (lineList[i] == "Contact_Status")
        {
            indexArray[12] = i;
        }
        // If the column is Add_Info, store the index in indexArray[13]
        else if (lineList[i] == "Additional_Info")
        {
            indexArray[13] = i;
        }
        // If the column is AID, store the index in indexArray[14]
        else if (lineList[i] == "AID")
        {
            indexArray[14] = i;
        }
    }

    // If any of the indexes are -1, error message and return
    for (int i = 0; i < 15; i++)
    {
        if (indexArray[i] == -1)
        {
            // Identify the missing column
            QString missingColumn;
            if (i == 0)
            {
                missingColumn = "VID";
            }
            else if (i == 1)
            {
                missingColumn = "Contact_Type";
            }
            else if (i == 2)
            {
                missingColumn = "CID";
            }
            else if (i == 3)
            {
                missingColumn = "Name";
            }
            else if (i == 4)
            {
                missingColumn = "Age";
            }
            else if (i == 5)
            {
                missingColumn = "Location";
            }
            else if (i == 6)
            {
                missingColumn = "Gender";
            }
            else if (i == 7)
            {
                missingColumn = "Ethnicity";
            }
            else if (i == 8)
            {
                missingColumn = "Education";
            }
            else if (i == 9)
            {
                missingColumn = "Occupation";
            }
            else if (i == 10)
            {
                missingColumn = "Email";
            }
            else if (i == 11)
            {
                missingColumn = "Phone_Number";
            }
            else if (i == 12)
            {
                missingColumn = "Contact_Status";
            }
            else if (i == 13)
            {
                missingColumn = "Additional_Info";
            }
            else if (i == 14)
            {
                missingColumn = "AID";
            }
            QMessageBox::warning(this, "Error Importing", "File does not contain the required column: " + missingColumn);
            return;
        }
    }

    // Start the timer for operation time reporting
    QElapsedTimer timer;
    timer.start();

    // Variable to store the number of lines read
    int lineCount = 1;
    // Read data using the indexes
    while (!in.atEnd()) {
        lineCount++;
        QString line = in.readLine();
        QStringList fields = line.split(",");
        // Escape quotes
        fields.replaceInStrings("\"", "");
        // Insert into database
        QSqlQuery query;
        query.prepare("INSERT INTO Contacts "
                      "(VID, Contact_Type, CID, Name, Age, Location, Gender, "
                      "Ethnicity, Education, Occupation, Email, Phone_Number, "
                      "Contact_Status, Additional_Info, AID) VALUES "
                      "(:VID, :Contact_Type, :CID, :Name, :Age, :Location, :Gender, "
                      ":Ethnicity, :Education, :Occupation, :Email, :Phone_Number, "
                      ":Contact_Status, :Additional_Info, :AID)");
        // Find the entry using the indexArray and add to query
        query.bindValue(":VID", fields[indexArray[0]]);
        query.bindValue(":Contact_Type", fields[indexArray[1]]);
        query.bindValue(":CID", fields[indexArray[2]]);
        query.bindValue(":Name", fields[indexArray[3]]);
        query.bindValue(":Age", fields[indexArray[4]]);
        query.bindValue(":Location", fields[indexArray[5]]);
        query.bindValue(":Gender", fields[indexArray[6]]);
        query.bindValue(":Ethnicity", fields[indexArray[7]]);
        query.bindValue(":Education", fields[indexArray[8]]);
        query.bindValue(":Occupation", fields[indexArray[9]]);
        query.bindValue(":Email", fields[indexArray[10]]);
        query.bindValue(":Phone_Number", fields[indexArray[11]]);
        query.bindValue(":Contact_Status", fields[indexArray[12]]);
        query.bindValue(":Additional_Info", fields[indexArray[13]]);
        query.bindValue(":AID", fields[indexArray[14]]);

        // Failure Message if not successful
        if(!query.exec()) {
            QMessageBox::warning(this, "Database Error", query.lastError().text());
            return;
        }
    }

    // Update the table
    model->setQuery("SELECT * FROM Contacts");
    ui->Contact_Table->setModel(model);

    // Record the timer output into QString
    QString elapsedTime = QString::number(timer.elapsed());
    // Concat the time to the status label, as well as the number of lines read
    ui->Time_to_Input_Lab->setText("Successfully imported " + QString::number(lineCount) + " contacts. Time taken: " + elapsedTime + " ms." );
    ui->Time_to_Input_Lab->setVisible(true);
}


void MainWindow::on_Return_To_Portal_But_3_pressed()
{
    ui->System->setCurrentIndex(1); //Return to Organizer Portal
}

void MainWindow::on_Add_Contact_But_pressed()
{
    QString name = ui->Name_Line->text();
    QString age = ui->Age_Spin->text();
    QString location = ui->Location_Line->text();
    QString gender = ui->Gender_Line->text();
    QString ethnicity = ui->Ethnicity_Line->text();
    QString education = ui->Education_Line->text();
    QString occupation = ui->Occupation_Line->text();
    QString email = ui->Email_Line->text();
    QString phone = ui->Phone_Num_Line->text();
    QString add = ui->Add_Info_Line_2->text();

    int length = db.getMaxValue("CID", "Contacts");
    length++;
    QString cid = QString::number(length);


    QSqlQuery query;
    query.prepare("INSERT INTO Contacts "
                  "(VID, Contact_Type, CID, Name, Age, Location, Gender, "
                  "Ethnicity, Education, Occupation, Email, Phone_Number, "
                  "Contact_Status, Additional_Info, AID) VALUES "
                  "(:VID, :Contact_Type, :CID, :Name, :Age, :Location, :Gender, "
                  ":Ethnicity, :Education, :Occupation, :Email, :Phone_Number, "
                  ":Contact_Status, :Additional_Info, :AID)");
    // Find the entry using the indexArray and add to query
    query.bindValue(":VID", userVID);
    query.bindValue(":Contact_Type", "0");
    query.bindValue(":CID", cid);
    query.bindValue(":Name", name);
    query.bindValue(":Age", age);
    query.bindValue(":Location", location);
    query.bindValue(":Gender", gender);
    query.bindValue(":Ethnicity", ethnicity);
    query.bindValue(":Education", education);
    query.bindValue(":Occupation", occupation);
    query.bindValue(":Email", email);
    query.bindValue(":Phone_Number", phone);
    query.bindValue(":Contact_Status", "0");
    query.bindValue(":Additional_Info", add);
    query.bindValue(":AID", "0");

    if(!query.exec()) {
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }
}

void MainWindow::on_Return_to_Add_Contact_But_pressed()
{
    ui->System->setCurrentIndex(6); //Return to Organizer Portal
    // Link Tables to View
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Contacts");
    ui->Contact_Table->setModel(model);
}



void MainWindow::on_Contact_Table_pressed(const QModelIndex &index)
{
    contactDataChange = index.data().toString();
    cidContactDataChange = index.siblingAtColumn(2).data().toString();
    if(index.column() == 0){
        typeData = "VID";
    }
    else if(index.column() == 1){
        typeData = "Contact_Type";
    }
    else if(index.column() == 2){
        typeData = "CID";
    }
    else if(index.column() == 3){
        typeData = "Name";
    }
    else if(index.column() == 4){
        typeData = "Age";
    }
    else if(index.column() == 5){
        typeData = "Location";
    }
    else if(index.column() == 6){
        typeData = "Gender";
    }
    else if(index.column() == 7){
        typeData = "Ethnicity";
    }
    else if(index.column() == 8){
        typeData = "Education";
    }
    else if(index.column() == 9){
        typeData = "Occupation";
    }
    else if(index.column() == 10){
        typeData = "Email";
    }
    else if(index.column() == 11){
        typeData = "Phone_Number";
    }
    else if(index.column() == 12){
        typeData = "Contact_Status";
    }
    else if(index.column() == 13){
        typeData = "Additional_Info";
    }
    else if(index.column() == 14){
        typeData = "AID";
    }
}


void MainWindow::on_Edit_Data_But_pressed()
{
    QString newData = ui->New_Data_Line->text();
    QSqlQuery query;
    query.prepare("update Contacts "
                  "set " + typeData + " = :value "
                  "where CID = :cid");
    query.bindValue(":value", newData);
    query.bindValue(":cid", cidContactDataChange);

    if(!query.exec()){
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }

    ui->Current_Data_Line->clear();
    ui->New_Data_Line->clear();
    ui->System->setCurrentIndex(6); //go to edit data portal
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Contacts");
    ui->Contact_Table->setModel(model);
}


void MainWindow::on_Edit_Contact_But_pressed()
{
    ui->System->setCurrentIndex(8); //go to edit data portal
    ui->Current_Data_Line->insert(contactDataChange);
}


void MainWindow::on_Delete_Contact_But_pressed()
{
    QSqlQuery query;
    query.prepare("delete from Contacts "
                  "where CID = :cid");
    query.bindValue(":cid", cidContactDataChange);

    if(!query.exec()){
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Contacts");
    ui->Contact_Table->setModel(model);
}


/////////////////////////////////////////////
/// Input Incentives
/////////////////////////////////////////////

void MainWindow::on_Return_To_Portal_But_4_pressed()
{
    ui->System->setCurrentIndex(3);
}


void MainWindow::on_DP_Table_pressed(const QModelIndex &index)
{
    contactDataChange = index.data().toString();
    cidContactDataChange = index.siblingAtColumn(0).data().toString();
    if(index.column() == 0){
        typeData = "IID";
    }
    else if(index.column() == 1){
        typeData = "Data_Name";
    }
    else if(index.column() == 2){
        typeData = "Points";
    }
}


void MainWindow::on_TB_Table_pressed(const QModelIndex &index)
{
    contactDataChange = index.data().toString();
    cidContactDataChange = index.siblingAtColumn(0).data().toString();
    if(index.column() == 0){
        typeData = "IID";
    }
    else if(index.column() == 1){
        typeData = "Data_Name";
    }
    else if(index.column() == 2){
        typeData = "Points";
    }
}

void MainWindow::on_Remove_TB_Inc_But_pressed()
{
    QSqlQuery query;
    query.prepare("delete from Incentives "
                  "where IID = :iid");
    query.bindValue(":iid", cidContactDataChange);

    if(!query.exec()){
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Incentives where Type = 1");
    ui->TB_Table->setModel(model);
}

void MainWindow::on_Remove_DP_Inc_But_pressed()
{
    QSqlQuery query;
    query.prepare("delete from Incentives "
                  "where IID = :iid");
    query.bindValue(":iid", cidContactDataChange);

    if(!query.exec()){
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Incentives where Type = 0");
    ui->DP_Table->setModel(model);
}

void MainWindow::on_Add_DP_Inc_But_2_pressed()
{
    QString DPType = ui->Data_Points_Combo->itemText(ui->Data_Points_Combo->currentIndex());
    QString points = QString::number(ui->Points_Spin->value());
    QString IID = QString::number(db.getMaxValue("IID", "Incentives") + 1);

    QSqlQuery query;
    query.prepare("INSERT INTO Incentives "
                  "(IID, Data_Name, Points, Type) VALUES "
                  "(:IID, :Data_Name, :Points, :Type)");
    // Find the entry using the indexArray and add to query
    query.bindValue(":IID", IID);
    query.bindValue(":Data_Name", DPType);
    query.bindValue(":Points", points);
    query.bindValue(":Type", "0");

    if(!query.exec()){
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }

    ui->System->setCurrentIndex(9);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Incentives where Type = 0");
    ui->DP_Table->setModel(model);
}

void MainWindow::on_Add_TB_Incentive_But_pressed()
{
    QString DPType = ui->Task_Name_Line->text();
    QString points = QString::number(ui->Points_Spin_2->value());
    QString IID = QString::number(db.getMaxValue("IID", "Incentives")+1);

    QSqlQuery query;
    query.prepare("INSERT INTO Incentives "
                  "(IID, Data_Name, Points, Type) VALUES "
                  "(:IID, :Data_Name, :Points, :Type)");
    // Find the entry using the indexArray and add to query
    query.bindValue(":IID", IID);
    query.bindValue(":Data_Name", DPType);
    query.bindValue(":Points", points);
    query.bindValue(":Type", "1");

    if(!query.exec()){
        QMessageBox::warning(this, "Database Error", query.lastError().text());
        return;
    }

    ui->System->setCurrentIndex(9);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Incentives where Type = 1");
    ui->TB_Table->setModel(model);
}


void MainWindow::on_Add_TB_Inc_But_pressed()
{
    ui->System->setCurrentIndex(11);
}


void MainWindow::on_Add_DP_Inc_But_pressed()
{
    ui->System->setCurrentIndex(10);
}

/////////////////////////////////////////////
/// See Contacts
/////////////////////////////////////////////

void MainWindow::on_Return_To_Portal_But_5_pressed()
{
    ui->System->setCurrentIndex(3);
}

