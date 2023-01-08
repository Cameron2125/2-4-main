#include "dbcontrol.h"

dbControl::dbControl() {
    openDB();
}

dbControl::dbControl(std::string fn) {
    fileName =  fn;
    openDB(fn);
}

void dbControl::operator=(dbControl &dbc)
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")){
        std::cerr << "Unable to load database this demo needs the SQLITE driver" <<std::endl;
        exit(-1);
    }
    this->fileName = dbc.fileName;
    openDB(fileName);
}

void dbControl::openDB() {
    std::string full_name = "./resources/project_db.sqlite";
    // open the database --------------------

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(full_name));

    if(!db.open()){
        std::cerr << "Database does not open -- "
                  << db.lastError().text().toStdString()
                  << std::endl;

        std::cerr << "  File -- " << full_name << std::endl;
        exit(0);
    }else{
        std::cerr << "Opened database successfully\n";
    }
}

void dbControl::openDB(std::string full_name){
    // open the database --------------------

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(full_name));

    if(!db.open()){
        std::cerr << "Database does not open -- "
                  << db.lastError().text().toStdString()
                  << std::endl;

        std::cerr << "  File -- " << full_name << std::endl;
        exit(0);
    }else{
        std::cerr << "Opened database successfully\n";
    }
}

void dbControl::closeDB() {
    db.close();
    std::cerr << "Database Closed\n";
}

QSqlQuery dbControl::runQuery(QString str){
    return db.exec(str);
}

std::string dbControl::getField(int column, int ID, std::string tableName){
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    query.prepare(QString("select * from %1").arg(table));

    if (!query.exec()){
        errorM(" getField");
    }

    while (query.next() && (query.value(0).toInt() != ID)) {

    }
    std::string returner = query.value(column).toString().toStdString();
    return returner;

}

std::string dbControl::getFeild(int colum, int ID, int IDcolum, std::string tableName){
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    query.prepare(QString("select * from %1").arg(table));

    if (!query.exec()){
        errorM(" getField");
    }

    while (query.next() & (query.value(IDcolum).toInt() != ID)) {

    }
    std::string returner = query.value(colum).toString().toStdString();
    return returner;

}

QSqlQuery dbControl::getTable(std::string tableName){
    QString table = QString::fromStdString(tableName);
    QSqlQuery query;
    query.prepare(QString("select * from %1").arg(table));
    if(!query.exec()){
        errorM(" getTable");
    }
    return query;
}

QSqlQuery dbControl::getColumn(std::string columnName, std::string tableName){
    QString table = QString::fromStdString(tableName);
    QString column = QString::fromStdString(columnName);
    QSqlQuery query;
    query.prepare(QString("select %1").arg(column) + QString(" from %1").arg(table));
    if(!query.exec()){
        errorM(" getColumn");
    }
    return query;
}

int dbControl::getTableLength(std::string tableName){


    QString table = QString::fromStdString(tableName);
    QSqlQuery query;
    query.prepare(QString("select * from %1").arg(table));
    int length = 0;

    if(!query.exec()){
        errorM(" getTableLength");
    }


    while(query.next()){

        length++;
    }


    return length;
}

void dbControl::addColumnToTable(std::string columnName, std::string columnType, std::string tableName){
    QString table = QString::fromStdString(tableName);
    QString column = QString::fromStdString(columnName);
    QString columnt = QString::fromStdString(columnType);
    QSqlQuery query;
    query.prepare(QString("alter table %1").arg(table) + QString(" add %1").arg(column) + QString(" %1").arg(columnt));

    if(!query.exec()){
        errorM(" addColumnToTable");
    }
}

float dbControl::getMaxValue(std::string columnName, std::string tableName){
    QString table = QString::fromStdString(tableName);
    QString column = QString::fromStdString(columnName);
    QSqlQuery query;
    query.prepare(QString("select max(%1").arg(column) + QString(") from %1").arg(table));
    query.bindValue(":column", column);
    if(!query.exec()){
        errorM(" getMaxValue");
    }

    float max = 0;
    if(query.next()){
        max = query.value(0).toFloat();
    }
    else{
        std::cerr << "Could not get max" << std::endl;
    }

    query.clear();
    return max;
}

float dbControl::getMinValue(std::string columnName, std::string tableName){
    QString table = QString::fromStdString(tableName);
    QString column = QString::fromStdString(columnName);
    QSqlQuery query;
    query.prepare(QString("select min(%1").arg(column) + QString(") from %1").arg(table));
    if(!query.exec()){
        errorM(" getMinValue");
    }

    float min = 0;
    if(query.next()){
        min = query.value(0).toFloat();
    }


    return min;
}

float dbControl::getAvgValue(std::string columnName, std::string tableName){
    QString table = QString::fromStdString(tableName);
    QString column = QString::fromStdString(columnName);
    QSqlQuery query;
    query.prepare(QString("select avg(%1").arg(column) + QString(") from %1").arg(table));
    if(!query.exec()){
        errorM(" getAvgValue");
    }

    float avg = 0;
    if(query.next()){
        avg = query.value(0).toFloat();
    }
    else{
        std::cerr << "Could not get avg" << std::endl;
    }

    return avg;
}

void dbControl::errorM(std::string errorType){
    std::cerr << "Error" << errorType << std::endl;
}

QString dbControl::getLIDFromUserName(QString username) {
    QSqlQuery qry;
    qry.prepare("Select * from Login where Username = :user");
    qry.bindValue(":user", username);
    if(!qry.exec()){
        errorM(" getLIDFromUserName");
    }
    qry.next();

    return qry.value(0).toString();
}

QString dbControl::getRIDFromLID(QString lId, QString table) {
    QSqlQuery qry;
    qry.prepare(QString("Select * from %1 where LID = :id").arg(table));
    qry.bindValue(":table", table);
    qry.bindValue(":id", lId);

    qry.exec();
    qDebug() << qry.next();

    return qry.value(0).toString();
}

std::vector<std::string> dbControl::getList(int column, int id, int idcolumn, std::string table){

    QSqlQuery query;
    QString tableN = QString::fromStdString(table);

    query.prepare(QString("select * from %1").arg(tableN));

    query.exec();

    std::vector<std::string> returner;

    while (query.next()){

        if (query.value(idcolumn).toInt() == id){

            returner.push_back(query.value(column).toString().toStdString());

        }
    }
    return returner;
}
std::vector<std::string> dbControl::getList(int column, std::string table){

    QSqlQuery query;
    QString tableN = QString::fromStdString(table);

    query.prepare(QString("select * from %1").arg(tableN));

    query.exec();

    std::vector<std::string> returner;

    while (query.next()){

            returner.push_back(query.value(column).toString().toStdString());

    }
    return returner;
}
