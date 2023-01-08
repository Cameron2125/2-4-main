#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <vector>
#include <iostream>
#include <QtSql>

#include "../contact.h"
#include "../dbControl/dbcontrol.h"

using namespace std;

class DataAnalysis
{
public:
    /**
     * @brief Default constructor used to connect to the default database
     */
    DataAnalysis();
    /**
     * @brief Additional constructor to control which database to connect to
     * @param fn The name of the database to connect to
     */
    DataAnalysis(string fn);
    /**
     * @brief The destructor for the class that deletes the dbControl pointer
     */
    ~DataAnalysis();

    /**
     * @brief Returns the percentage of male contacts in the system
     * @return A float for the percentage
     */
    float percentMale();
    /**
     * @brief Returns the percentage of female contacts in the system
     * @return A float for the percentage
     */
    float percentFemale();

    /**
     * @brief Returns the percentage of contacts who are volunteering in the system
     * @return A float for the percentage
     */
    float percentVolunteering();
    /**
     * @brief Returns the percentage of contacts who are not volunteering in the system
     * @return A float for the percentage
     */
    float percentNotVolunteering();

private:
    //pointer for the database controller
    dbControl *db;
};

#endif // DATAANALYSIS_H
