#include "contactmanager.h"
#include "ui_contactmanager.h"

/**
 * @brief Construct a new Contact Manager:: Contact Manager object
 * 
 * @param parent 
 */
ContactManager::ContactManager(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ContactManager)
{
    ui->setupUi(this);


    // Initialize the label_status by clearing it and setting not visible
    ui->label_status->clear();
    ui->label_status->setVisible(false);

    // Set the dbPath initially (this path required from running within .app)
    dbPath = "../../../../../resources/sample_db.sqlite";
}

/**
 * @brief Destroy the Contact Manager:: Contact Manager object
 * 
 */
ContactManager::~ContactManager()
{
    delete ui;
}

/**
 * @brief Load, overrides dbPath using dbControl
 *
 * @param db
 * @param vid
 */
void ContactManager::load(dbControl *db, int vid){
    dbPath = QString::fromStdString(db->dataBasePath);
    this->current_vid = vid;
    load(vid);
    d = db;
}

/**
 * @brief Load, overrides dbPath using dbControl
 *
 * @param vid
 */
void ContactManager::load(int vid)
{
    // Check DB path exists
    if (!checkDB(dbPath)) {
        QMessageBox::warning(this, "Error", "Database path not found.");
        this -> close();
    }
    // Load Database
    if (!openDB()) {
        QMessageBox::warning(this, "Error", "Database cannot be opened.");
        this -> close();
    }
    // Check that the "Contacts" table exists
    QSqlQuery queryCheck(db);
    queryCheck.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Contacts';");
    // If not exist, error message
    if (queryCheck.next() == false)
    {
        QMessageBox::warning(this, "Error", "Contacts table does not exist");
        this -> close();
    }
    // Populate the table view
    linkEditableTableView(vid);
    populateTableView(vid);
}

/**
 * @brief Checks DB
 *
 * @param path
 * @return true
 * @return false
 */
bool ContactManager::checkDB(QString path) {
    QFileInfo check_file(path);
    // check path is an existing file, and not a directory
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Function that populates the tableView with the data from the database
 *
 * @param vid
 */
void ContactManager::populateTableView(int vid)
{
    // Create a query model
    QSqlQueryModel *model = new QSqlQueryModel();

    // Set the query
    QSqlQuery query(db);
    //query.prepare("SELECT * FROM Contacts WHERE VID = (vid) VALUES (:vid)");
    query.prepare("SELECT * FROM Contacts WHERE VID =" + QString::number(vid));
    query.bindValue(":vid", vid);
    query.exec();

    // Set the model
    model->setQuery(query);

    // Set the tableView to the model
    ui->tableView->setModel(model);
}

/**
 * @brief Links the tableView to the database as editable
 *
 * @param vid
 */
void ContactManager::linkEditableTableView(int vid) {
    // New model
    tableModel = new QSqlTableModel(0, db);
    tableModel->setTable("Contacts");
    tableModel->setFilter("VID =" + QString::number(vid));
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    ui->tableView->setModel(tableModel);
}

/**
 * @brief Import CSV Button Clicked
 * 
 */
void ContactManager::on_button_importcsv_clicked()
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
    model->setQuery("SELECT * FROM Contacts where VID = " + QString::fromStdString(std::to_string(current_vid)));
    ui->tableView->setModel(model);

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
    int indexArray[11];
    // Initialize the array to -1
    for (int i = 0; i < 11; i++)
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
    if (lineList.size() < 11)
    {
        QMessageBox::warning(this, "Error", "File format is incorrect");
        return;
    }

    // Find the index of each column
    for (int i = 0; i < lineList.size(); i++)
    {
        //        // If the column is VID, store the index in indexArray[0]
        //        if (lineList[i] == "VID")
        //        {
        //            indexArray[0] = i;
        //        }
        //        // If the column is Contact_Type, store the index in indexArray[1]
        //        else if (lineList[i] == "Contact_Type")
        //        {
        //            indexArray[1] = i;
        //        }
        //        // If the column is CID, store the index in indexArray[2]
        //        else if (lineList[i] == "CID")
        //        {
        //            indexArray[2] = i;
        //        }
        // If the column is Name, store the index in indexArray[3]
        if (lineList[i] == "Name")
        {
            indexArray[0] = i;
        }
        // If the column is Age, store the index in indexArray[4]
        else if (lineList[i] == "Age")
        {
            indexArray[1] = i;
        }
        // If the column is Location, store the index in indexArray[5]
        else if (lineList[i] == "Location")
        {
            indexArray[2] = i;
        }
        // If the column is Gender, store the index in indexArray[6]
        else if (lineList[i] == "Gender")
        {
            indexArray[3] = i;
        }
        // If the column is Ethnicity, store the index in indexArray[7]
        else if (lineList[i] == "Ethnicity")
        {
            indexArray[4] = i;
        }
        // If the column is Education, store the index in indexArray[8]
        else if (lineList[i] == "Education")
        {
            indexArray[5] = i;
        }
        // If the column is Occupation, store the index in indexArray[9]
        else if (lineList[i] == "Occupation")
        {
            indexArray[6] = i;
        }
        // If the column is Email, store the index in indexArray[10]
        else if (lineList[i] == "Email")
        {
            indexArray[7] = i;
        }
        // If the column is Phone_Num, store the index in indexArray[11]
        else if (lineList[i] == "Phone_Number")
        {
            indexArray[8] = i;
        }
        // If the column is Contact_Stat, store the index in indexArray[12]
        else if (lineList[i] == "Contact_Status")
        {
            indexArray[9] = i;
        }
        // If the column is Add_Info, store the index in indexArray[13]
        else if (lineList[i] == "Additional_Info")
        {
            indexArray[10] = i;
        }
        //        // If the column is AID, store the index in indexArray[14]
        //        else if (lineList[i] == "AID")
        //        {
        //            indexArray[12] = i;
        //        }
    }

    // If any of the indexes are -1, error message and return
    for (int i = 0; i < 11; i++)
    {
        if (indexArray[i] == -1)
        {
            // Identify the missing column
            QString missingColumn;
            //            if (i == 0)
            //            {
            //                missingColumn = "VID";
            //            }
            //            else if (i == 1)
            //            {
            //                missingColumn = "Contact_Type";
            //            }
            //            else if (i == 2)
            //            {
            //                missingColumn = "CID";
            //            }
            if (i == 0)
            {
                missingColumn = "Name";
            }
            else if (i == 1)
            {
                missingColumn = "Age";
            }
            else if (i == 2)
            {
                missingColumn = "Location";
            }
            else if (i == 3)
            {
                missingColumn = "Gender";
            }
            else if (i == 4)
            {
                missingColumn = "Ethnicity";
            }
            else if (i == 5)
            {
                missingColumn = "Education";
            }
            else if (i == 6)
            {
                missingColumn = "Occupation";
            }
            else if (i == 7)
            {
                missingColumn = "Email";
            }
            else if (i == 8)
            {
                missingColumn = "Phone_Number";
            }
            else if (i == 9)
            {
                missingColumn = "Contact_Status";
            }
            else if (i == 10)
            {
                missingColumn = "Additional_Info";
            }
            //            else if (i == 14)
            //            {
            //                missingColumn = "AID";
            //            }
            QMessageBox::warning(this, "Error Importing", "File does not contain the required column: " + missingColumn);
            return;
        }
    }

    // Start the timer for operation time reporting
    QElapsedTimer timer;
    timer.start();

    // Variable to store the number of lines read
    int lineCount = 1;

    // Number of Contacts added
    int addedContacts = 0;

    //Points Scored
    int scoreAdded = 0;
    int incentPoints = 0;

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
                      "Contact_Status, Additional_Info) VALUES "
                      "(:VID, :Contact_Type, :CID, :Name, :Age, :Location, :Gender, "
                      ":Ethnicity, :Education, :Occupation, :Email, :Phone_Number, "
                      ":Contact_Status, :Additional_Info)");
        // Find the entry using the indexArray and add to query
        query.bindValue(":VID", QString::number(current_vid));
        query.bindValue(":Contact_Type", QString::number(rand()%2));
        query.bindValue(":CID", QString::number(d->getMaxValue("CID", "Contacts")+1));
        query.bindValue(":Name", fields[indexArray[0]]);
        query.bindValue(":Age", fields[indexArray[1]]);
        query.bindValue(":Location", fields[indexArray[2]]);
        query.bindValue(":Gender", fields[indexArray[3]]);
        query.bindValue(":Ethnicity", fields[indexArray[4]]);
        query.bindValue(":Education", fields[indexArray[5]]);
        query.bindValue(":Occupation", fields[indexArray[6]]);
        query.bindValue(":Email", fields[indexArray[7]]);
        query.bindValue(":Phone_Number", fields[indexArray[8]]);
        query.bindValue(":Contact_Status", fields[indexArray[9]]);
        query.bindValue(":Additional_Info", fields[indexArray[10]]);


        // Failure Message if not successful
        if(!query.exec()) {
            QMessageBox::warning(this, "Database Error", query.lastError().text());
            return;
        }

        query.finish();

        // Record the timer output into QString
        QString elapsedTime = QString::number(timer.elapsed());
        // Concat the time to the status label, as well as the number of lines read
        ui->label_status->setText("Successfully imported " + QString::number(lineCount) + " contacts. Time taken: " + elapsedTime + " ms." );
        ui->label_status->setVisible(true);

        //Get the points for the data incentives
        QSqlQuery qi;
        qi.prepare("select Data_Name from Incentives");
        if(!qi.exec()){
            QMessageBox::warning(this, "Database Error while saving points", qi.lastError().text());
        }

        //See if a data incentive was fufilled
        while(qi.next()){
            QString name = qi.value(0).toString();
            QSqlQuery qp;
            qp.prepare("select Points from Incentives where Data_Name = :dn");
            qp.bindValue(":dn", name);
            if(!qp.exec()){
                QMessageBox::warning(this, "Database Error while saving points", qp.lastError().text());
            }
            int addpoints = 0;
            if(qp.next()){
               addpoints = qp.value(0).toInt();
            }
            qp.finish();
            //Check if name of data point is same as value that has changed
            if(name == "Name"){
                if(fields[indexArray[0]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Age"){
                if(fields[indexArray[1]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Location"){
                if(fields[indexArray[2]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Gender"){
                if(fields[indexArray[3]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Ethnicity"){
                if(fields[indexArray[4]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Education"){
                if(fields[indexArray[5]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Occupation"){
                if(fields[indexArray[6]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Email"){
                if(fields[indexArray[7]] != ""){
                    incentPoints += addpoints;
                }
            }
            else if(name == "Phone_Number"){
                if(fields[indexArray[8]] != ""){
                    incentPoints += addpoints;
                }
            }
        }
        qi.finish();
        for(int i = 0; i < 11; i++){
            if(fields[indexArray[i]] != ""){
                scoreAdded++;
            }
        }
        scoreAdded -= 3;
        addedContacts++;
    }

    // Set pending changes to true
    pendingChanges = true;

    // Update the table
    model->setQuery("SELECT * FROM Contacts where VID = " + QString::fromStdString(std::to_string(current_vid)));
    ui->tableView->setModel(model);

    // Show results
    score += scoreAdded + incentPoints;
    QMessageBox::information(this, "Score", "You added " + QString::number(addedContacts) + " contacts and scored " + QString::number(scoreAdded) + " points!");
    if(incentPoints > 0){
        QMessageBox::information(this, "Score", "You scored and additional " + QString::number(incentPoints) + " points from incentives!");
    }
}

/**
 * @brief Event for add new contact button
 * 
 */
void ContactManager::on_button_addnew_clicked()
{
    //Points Scored
    int scoreAdded = 0;

    // Create a new edit dialog
    ContactEdit *editDialog = new ContactEdit(this);
    // Set the mode to add
    editDialog->setAddMode();

    // Initialize with empty strings equal to column count
    QStringList data;
    for (int i = 0; i < tableModel->columnCount(); i++)
    {
        data.append("");
    }
    // Print a debug of the length of data
    qDebug() << data.length();

    // Add the VID to the list
    data[0] = QString::number(current_vid);
    // Add the contact type, which is a fixed global setting
    data[1] = QString::number(rand()%2);
    // Generate the CID, this is always 1 + the current max CID
    QSqlQuery query(db);
    query.prepare("SELECT MAX(CID) FROM Contacts");
    query.exec();
    query.first();
    int current_max_cid = query.value(0).toInt();
    qDebug() << current_max_cid;
    data[2] = QString::number(current_max_cid + 1);

    // Send this data to the edit dialog
    editDialog->setData(data);

    // Show the dialog
    editDialog->exec();

    // If the dialog was accepted, update the table
    if (editDialog->result() == QDialog::Accepted)
    {
        // Get the new data
        QStringList resultData = editDialog->getData();
        // Print a debug of the length of this data
        qDebug() << resultData.length();
        // Add a new row to the table
        tableModel->insertRow(tableModel->rowCount());
        // Get the row index of the new row
        int row = tableModel->rowCount() - 1;
        // Set the data in the new row in loop
        for (int i = 0; i < tableModel->columnCount(); i++)
        {
            // Set the data in the new row
            tableModel->setData(tableModel->index(row, i), resultData[i]);
        }
        for(int i = 3; i < 15; i++){
            if(resultData[i] != ""){
                scoreAdded++;
            }
        }
    }


    // Show result
    score += scoreAdded;
    QMessageBox::information(this, "Score", "You added 1 contact and scored " + QString::number(scoreAdded) + " points!");

    //Get the points for the data incentives
    QSqlQuery qi (db);
    qi.prepare("select Data_Name from Incentives");
    if(!qi.exec()){
        QMessageBox::warning(this, "Database Error while saving points", qi.lastError().text());
    }

    //See if a data incentive was fufilled
    while(qi.next()){
        QStringList newData = editDialog->getData();
        QString name = qi.value(0).toString();
        QSqlQuery qp (db);
        qp.prepare("select Points from Incentives where Data_Name = :dn");
        qp.bindValue(":dn", name);
        if(!qp.exec()){
            QMessageBox::warning(this, "Database Error while saving points", qp.lastError().text());
        }
        int addpoints = 0;
        if(qp.next()){
           addpoints = qp.value(0).toInt();
        }
        //Check if name of data point is same as value that has changed
        if(name == "Name"){
            if(newData[3] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Age"){
            if(newData[4] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Location"){
            if(newData[5] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Gender"){
            if(newData[6] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Ethnicity"){
            if(newData[7] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Education"){
            if(newData[8] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Occupation"){
            if(newData[9] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Email"){
            if(newData[10] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Phone_Number"){
            if(newData[11] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
    }

    // Set pending changes to true
    pendingChanges = true;

    // Delete the dialog
    delete editDialog;

}

/**
 * @brief Event for edit contacts button
 * 
 */
void ContactManager::on_button_edit_clicked()
{
    //Points Scored
    int scoreAdded = 0;
    // Get the currently selected row
    int row = ui->tableView->currentIndex().row();
    // Loop through the columns and create a QStringList of the selected row
    QStringList rowList;

    // Boolean List of empty values
    bool empty[15];

    for(int i = 0; i < 15; i++){
        empty[i] = false;
    }

    for (int i = 0; i < tableModel->columnCount(); i++)
    {
        rowList.append(tableModel->data(tableModel->index(row, i)).toString());
        if(rowList[i] == ""){
            empty[i] = true;
        }
        else{
            empty[i] = false;
        }
    }
    // Create a new dialog and pass the QStringList to it
    ContactEdit *editDialog = new ContactEdit(this);
    editDialog->setData(rowList);
    // Set the mode to edit
    editDialog->setEditMode();
    // Show the dialog
    editDialog->exec();

    // If the dialog was accepted, update the table
    if (editDialog->result() == QDialog::Accepted)
    {
        // Get the new data
        QStringList newData = editDialog->getData();
        // Update the table
        for (int i = 0; i < tableModel->columnCount(); i++)
        {
            tableModel->setData(tableModel->index(row, i), newData[i]);
        }
        // Calculate Score
        for(int i = 3; i < 15; i++){
            if(empty[i] && newData[i] != ""){
                scoreAdded++;
            }
        }
    }

    //Get the points for the data incentives
    QSqlQuery qi (db);
    qi.prepare("select Data_Name from Incentives");
    if(!qi.exec()){
        QMessageBox::warning(this, "Database Error while saving points", qi.lastError().text());
    }

    // Show results
    score += scoreAdded;
    QMessageBox::information(this, "Score", "You edited 1 contact and scored " + QString::number(scoreAdded) + " points!");

    //See if a data incentive was fufilled
    while(qi.next()){
        QStringList newData = editDialog->getData();
        QString name = qi.value(0).toString();
        QSqlQuery qp (db);
        qp.prepare("select Points from Incentives where Data_Name = :dn");
        qp.bindValue(":dn", name);
        if(!qp.exec()){
            QMessageBox::warning(this, "Database Error while saving points", qp.lastError().text());
        }
        int addpoints = 0;
        if(qp.next()){
           addpoints = qp.value(0).toInt();
        }
        //Check if name of data point is same as value that has changed
        if(name == "Name"){
            if(empty[3] && newData[3] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Age"){
            if(empty[4] && newData[4] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Location"){
            if(empty[5] && newData[5] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Gender"){
            if(empty[6] && newData[6] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Ethnicity"){
            if(empty[7] && newData[7] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Education"){
            if(empty[8] && newData[8] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Occupation"){
            if(empty[9] && newData[9] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Email"){
            if(empty[10] && newData[10] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
        else if(name == "Phone_Number"){
            if(empty[11] && newData[11] != ""){
                score += addpoints;
                QMessageBox::information(this, "Score", "You earned " + QString::number(addpoints) + " additional points from fufilling incentives!");
            }
        }
    }
    // Delete the dialog
    delete editDialog;

    // Set pending changes to true
    pendingChanges = true;
}


/**
 * @brief Saves changes to database
 *
 */
void ContactManager::SaveChanges() {

    // current date and time on the current system
    time_t now = time(0);

    // convert now to string form
    std::string date_time = ctime(&now);

    QSqlQuery qpoints (db);
    qpoints.prepare("insert into Point_History (HID, VID, Point_Origin, Point_Value, Date) values (:hid, :vid, :po, :pv, :date)");
    qpoints.bindValue(":hid", QString::number(d->getMaxValue("HID", "Point_History")+1));
    qpoints.bindValue(":vid", QString::number(current_vid));
    qpoints.bindValue(":pv", QString::number(score));
    qpoints.bindValue(":po", "Contact Added");
    qpoints.bindValue(":date", QString::fromStdString(date_time));

    if(!qpoints.exec()){
        QMessageBox::warning(this, "Database Error while saving points", qpoints.lastError().text());
    }
    qpoints.finish();
    // Save the data
    tableModel->submitAll();
}

/**
 * @brief Event for button box accepted
 * 
 */
void ContactManager::on_buttonBox_accepted()
{
    SaveChanges();
    QMessageBox::information(this, "Score", "You scored " + QString::number(score) + " points!");
    //closeDB();
    save = true;
    close();

}

/**
 * @brief Event for button box rejected
 * 
 */
void ContactManager::on_buttonBox_rejected()
{
    close();
}

/**
 * @brief Close confirmation dialog
 * 
 */
void ContactManager::closeEvent(QCloseEvent *){
    // Check for pending changes
    if (pendingChanges && !save) {
        // Show confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Pending Changes", "There are unsaved changes present. Do you want to save before exiting?",
                                      QMessageBox::Save|QMessageBox::Discard);
        if (reply == QMessageBox::Save) {
            qDebug() << "Save was clicked";
            SaveChanges();
            QMessageBox::information(this, "Score", "You scored " + QString::number(score) + " points!");
        } else {
            qDebug() << "Discard was clicked";
        }
    }
    closeDB();
}
