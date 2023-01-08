#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <vector>
#include <iostream>
#include <QtSql>

#include "../dbControl/dbcontrol.h"

using namespace std;

//NOTES: percentage gender, age group?, ethnicity, education level?, etc.

class DataAnalysis
{
public:
    /**
     * @brief Default constructor; DO NOT USE
     */
    DataAnalysis();
    /**
     * @brief Primarily used constructor for creating a DataAnalysis object connected to the database
     * @param db The dbControl object that connects to the database
     */
    DataAnalysis(dbControl* database);
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

    //FIXME: missing any ethnicities?

    /**
     * @brief Returns the percentage of contacts who have an ethnicity of White in the system
     * @return A float for the percentage
     */
    float percentWhite();
    /**
     * @brief Returns the percentage of contacts who have an ethnicity of Black in the system
     * @return A float for the percentage
     */
    float percentBlack();
    /**
     * @brief Returns the percentage of contacts who have an ethnicity of Hispanic in the system
     * @return A float for the percentage
     */
    float percentHispanic();
    /**
     * @brief Returns the percentage of contacts who have an ethnicity of Asian in the system
     * @return A float for the percentage
     */
    float percentAsian();
    /**
     * @brief Returns the percentage of contacts who do not have a specified ethnicity in the system
     * @return A float for the percentage
     */
    float percentOther();

private:
    //database controller object
    dbControl *db;
};

#endif // DATAANALYSIS_H
