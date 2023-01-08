#include "dataanalysis.h"

DataAnalysis::DataAnalysis() {
    //contsruct the database tool and open the default database
    db = new dbControl();
}

DataAnalysis::DataAnalysis(string fn) {
    //construct the database tool and open an alternate database
    db = new dbControl(fn);
}

DataAnalysis::~DataAnalysis() {
    //close the database and delete the pointer
    db->closeDB();
    delete db;
}

float DataAnalysis::percentMale() {
    //prepare queries
    QString strMale = "select * from Contacts where Gender = \"male\";";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryMale = db->runQuery(strMale);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numMale = 0;
    int total = 0;

    //count number of male contacts
    while (qryMale.next()) {
        numMale++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of male contacts
    return (float)numMale / (float)total;
}

float DataAnalysis::percentFemale() {
    //prepare queries
    QString strFemale = "select * from Contacts where Gender = \"female\";";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryFemale = db->runQuery(strFemale);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numFemale = 0;
    int total = 0;

    //count number of female contacts
    while (qryFemale.next()) {
        numFemale++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of female contacts
    return (float)numFemale / (float)total;
}

float DataAnalysis::percentVolunteering() {
    //prepare queries
    QString strVolunteer = "select * from Contacts where Contact_Status = 1;";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryVolunteer = db->runQuery(strVolunteer);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numVolunteer = 0;
    int total = 0;

    //count number of volunteering contacts
    while (qryVolunteer.next()) {
        numVolunteer++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of volunteering contacts
    return (float)numVolunteer / (float)total;
}

float DataAnalysis::percentNotVolunteering() {
    //prepare queries
    QString strNotVolunteer = "select * from Contacts where Contact_Status = 0;";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryNotVolunteer = db->runQuery(strNotVolunteer);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numNotVolunteer = 0;
    int total = 0;

    //count number of non volunteering contacts
    while (qryNotVolunteer.next()) {
        numNotVolunteer++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of non volunteering contacts
    return (float)numNotVolunteer / (float)total;
}
