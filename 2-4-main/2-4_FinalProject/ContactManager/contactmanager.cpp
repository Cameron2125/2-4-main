#include "contactmanager.h"
#include "ui_contactmanager.h"

// Constructor
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

// Destructor
ContactManager::~ContactManager()
{
    delete ui;
}

// Load, overrides dbPath using dbControl
void ContactManager::load(dbControl *db, int vid){
    dbPath = QString::fromStdString(db->dataBasePath);
    this->current_vid = vid;
    load(vid);
}

// Load, overrides dbPath using dbControl
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
    // populateTableView(vid);
}

// Checks DB
bool ContactManager::checkDB(QString path) {
    QFileInfo check_file(path);
    // check path is an existing file, and not a directory
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

// Function that populates the tableView with the data from the database
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

// Links the tableView to the database as editable
void ContactManager::linkEditableTableView(int vid) {
    // New model
    tableModel = new QSqlTableModel(0, db);
        tableModel->setTable("Contacts");
        tableModel->setFilter("VID =" + QString::number(vid));
        tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tableModel->select();
    ui->tableView->setModel(tableModel);
}

// Import CSV Button Clicked
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

    // Check that the "Contacts" table exists
    QSqlQuery queryCheck;
    queryCheck.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Contacts';");
    // If not exist, error message
    if (queryCheck.next() == false)
    {
        QMessageBox::warning(this, "Error", "Contacts table does not exist");
        return;
    }

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
    int indexArray[5];
    // Initialize the array to -1
    for (int i = 0; i < 5; i++)
    {
        indexArray[i] = -1;
    }
    // First read line 1
    QString line = in.readLine();
    // Split line into a QStringList, using a csv format
    QStringList lineList = line.split(";");
    // Escape quotes
    lineList.replaceInStrings("\"", "");

    // If lineList has less than 5 elements, error message and return
    if (lineList.size() < 5)
    {
        QMessageBox::warning(this, "Error", "File format is incorrect");
        return;
    }

    // Find the index of each column
    for (int i = 0; i < lineList.size(); i++)
    {
        // If the column is first_name, store the index in indexArray[0]
        if (lineList[i] == "first_name")
        {
            indexArray[0] = i;
        }
        // If the column is last_name, store the index in indexArray[1]
        else if (lineList[i] == "last_name")
        {
            indexArray[1] = i;
        }
        // If the column is phone_num, store the index in indexArray[2]
        else if (lineList[i] == "phone_num")
        {
            indexArray[2] = i;
        }
        // If the column is email, store the index in indexArray[3]
        else if (lineList[i] == "email")
        {
            indexArray[3] = i;
        }
        // If the column is age, store the index in indexArray[4]
        else if (lineList[i] == "age")
        {
            indexArray[4] = i;
        }
    }

    // If any of the indexes are -1, error message and return
    for (int i = 0; i < 5; i++)
    {
        if (indexArray[i] == -1)
        {
            // Identify the missing column
            QString missingColumn;
            if (i == 0)
            {
                missingColumn = "first_name";
            }
            else if (i == 1)
            {
                missingColumn = "last_name";
            }
            else if (i == 2)
            {
                missingColumn = "phone_num";
            }
            else if (i == 3)
            {
                missingColumn = "email";
            }
            else if (i == 4)
            {
                missingColumn = "age";
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

    db.transaction();
    // Read data using the indexes
    while (!in.atEnd()) {
        lineCount++;
        QString line = in.readLine();
        QStringList fields = line.split(";");
        // Escape quotes
        fields.replaceInStrings("\"", "");
        // Insert into database
        QSqlQuery query(db);
        query.prepare("INSERT INTO Contacts (VID, Contact_Type, CID, Name, Phone_Number, Email, Age) VALUES (:VID, :Contact_Type, :CID, :Name, :Phone_Number, :Email, :Age)");
        // Find the entry using the indexArray and add to query
        QString fullName = fields[indexArray[0]] + " " + fields[indexArray[1]];
        query.bindValue(":VID", QString::number(current_vid));
        query.bindValue(":Contact_Type", QString::number(0));
        query.bindValue(":CID", QString::number(0));
        query.bindValue(":Name", fullName);
        query.bindValue(":Phone_Number", fields[indexArray[2]]);
        query.bindValue(":Email", fields[indexArray[3]]);
        query.bindValue(":Age", fields[indexArray[4]]);

        // Failure Message if not successful
        if(!query.exec()) {
            QMessageBox::warning(this, "Database Error", query.lastError().text());
            return;
        }
    }
    db.commit();

    linkEditableTableView(current_vid);
    // Update the table
    // model->setQuery("SELECT * FROM contact_list");
    // ui->tableView->setModel(model);

    // Record the timer output into QString
    QString elapsedTime = QString::number(timer.elapsed());
    // Concat the time to the status label, as well as the number of lines read
    ui->label_status->setText("Successfully imported " + QString::number(lineCount) + " contacts. Time taken: " + elapsedTime + " ms." );
    ui->label_status->setVisible(true);
}


void ContactManager::on_button_addnew_clicked()
{
    int row = tableModel->rowCount();
    tableModel->insertRow(row);
}

