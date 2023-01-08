#ifndef DBCONTROL_H
#define DBCONTROL_H

#include<string>
#include<iostream>
#include <QtSql>
#include <vector>

class dbControl
{
public:
    /*!
     * \brief dbControl
     * Base contructor for database control
     */
    dbControl();
    dbControl(std::string fn);
    /*!
     * \brief operator =
     * Copy assignment constructor
     */
    void operator = (dbControl &);/**<copy assignment*/

    QSqlDatabase db;

    std::string fileName;
    std::string dataBasePath = "../../resources/sample_db.sqlite";

    /*!
     * \brief openDB
     * Opens database
     */
    void openDB();
    /*!
     * \brief openDB(fileName)
     * Opens an alternate database other than the main database
     * This should only be used in testing.
     * \param fileName
     */
    void openDB(std::string full_name);

    /*!
     * \brief closeDB
     * Closes database
     */
    void closeDB();
    /*!
     * \brief runQuery
     * Runs the given query
     * \param str
     * \return
     * The query that was run
     */
    QSqlQuery runQuery(QString str);

    /*!
     * \brief getFeild
     * Returns the value in the specified feild
     * \param colum
     * the colum of desired data
     * \param ID
     * id of object
     * \param table
     * the name of table the object is housed in
     * \return
     * string representation of the data
     */
    std::string getField(int column, int ID, std::string tableName);

    /*!
     * \brief getFeild
     * Returns the value in the specified feild
     * \param colum
     * the colum of desired data
     * \param ID
     * id of object
     * \param IDcolum
     * the colum that the id is in
     * \param table
     * the name of table the object is housed in
     * \return
     * This will return a string representation of the data
     */
    std::string getFeild(int colum, int ID, int IDcolum,
                         std::string tableName);

    /*!
     * \brief getTable
     * Will run "select * from tableName;" in sql
     * \param tableName
     * \return
     * This will return an QSqlQuery with the entire table
     */
    QSqlQuery getTable(std::string tableName);
    /*!
     * \brief getColumn
     * Will run "select columnName from tableName;" in sql
     * \param columnName
     * \param tableName
     * \return
     * This method will return the query that only gets one column
     * from a table
     */
    QSqlQuery getColumn(std::string columnName, std::string tableName);

    /*!
     * \brief getTableLength
     * Will run "select cnt(*) from tableName;" in sql
     * \param tableName
     * \return
     * The number of entries in the table
     */
    int getTableLength(std::string tableName);

    /*!
     * \brief addColumntoTable
     * Will run "alter table tableName add columnName columntype;" in sql
     * and add a column to the table, This will only add a column to the
     * end of a table if you need to add a column somewhere in the middle
     * of the table speak to me
     * \param columnName
     * \param tableName
     */
    void addColumnToTable(std::string columnName, std::string columnType, std::string tableName);

    /*!
     * \brief getMaxValue
     * Will run "select max(columnName) from tableName;" in sql
     * \param columnName
     * \param tableName
     * \return
     * This will return the max value of a column from a table
     * When using this be careful that the column stores an int or float
     */
    float getMaxValue(std::string columnName, std::string tableName);

    /*!
     * \brief getMinValue
     * Will run "select min(columnName) from tableName;" in sql
     * \param columnName
     * \param tableName
     * \return
     * This will return the min value of a column from a table
     * When using this be careful that the column stores an int or float
     */
    float getMinValue(std::string columnName, std::string tableName);

    /*!
     * \brief getAvgValue
     * Will run "select avg(columnName) from tableName;" in sql
     * \param columnName
     * \param tableName
     * \return
     * This will return the avg value of a column from a table
     * When using this be careful that the column stores an int or float
     */
    float getAvgValue(std::string columnName, std::string tableName);

    /*!
     * \brief errorM
     * Prints out error message
     * \param errorType
     */
    void errorM(std::string errorType);


    std::vector<std::string> getList(int column, int id, int idcolumn, std::string table);
    std::vector<std::string> getList(int column, std::string table);


private:




};

#endif // DBCONTROL_H
