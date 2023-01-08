#include "dataanalysis.h"

DataAnalysis::DataAnalysis() {

}

DataAnalysis::DataAnalysis(dbControl* database) {
    //copy over the database control tool
    db = database;
}

DataAnalysis::~DataAnalysis() {

}

float DataAnalysis::percentMale() {
    //prepare queries
    QString strMale = "select * from Contacts where Gender = \"m\" or Gender = \"male\";";
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
    QString strFemale = "select * from Contacts where Gender = \"f\" or Gender = \"female\";";
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

float DataAnalysis::percentWhite() {
    //prepare queries
    QString strWhite = "select * from Contacts where Ethnicity = \"White\";";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryWhite = db->runQuery(strWhite);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numWhite = 0;
    int total = 0;

    //count number of White contacts
    while (qryWhite.next()) {
        numWhite++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of White contacts
    return (float)numWhite / (float)total;
}

float DataAnalysis::percentBlack() {
    //prepare queries
    QString strBlack = "select * from Contacts where Ethnicity = \"Black\";";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryBlack = db->runQuery(strBlack);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numBlack = 0;
    int total = 0;

    //count number of Black contacts
    while (qryBlack.next()) {
        numBlack++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of Black contacts
    return (float)numBlack / (float)total;
}

float DataAnalysis::percentHispanic() {
    //prepare queries
    QString strHispanic = "select * from Contacts where Ethnicity = \"Hispanic\";";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryHispanic = db->runQuery(strHispanic);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numHispanic = 0;
    int total = 0;

    //count number of Hispanic contacts
    while (qryHispanic.next()) {
        numHispanic++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of Hispanic contacts
    return (float)numHispanic / (float)total;
}

float DataAnalysis::percentAsian() {
    //prepare queries
    QString strAsian = "select * from Contacts where Ethnicity = \"Asian\";";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryAsian = db->runQuery(strAsian);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numAsian = 0;
    int total = 0;

    //count number of Asian contacts
    while (qryAsian.next()) {
        numAsian++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of Asian contacts
    return (float)numAsian / (float)total;
}

float DataAnalysis::percentOther() {
    //prepare queries
    QString strOther = "select * from Contacts where Ethnicity = \"Other\";";
    QString strAll = "select * from Contacts;";

    //run queries
    QSqlQuery qryOther = db->runQuery(strOther);
    QSqlQuery qryAll = db->runQuery(strAll);

    //initialize variables for counting the contacts
    int numOther = 0;
    int total = 0;

    //count number of contacts who do not have a specified ethnicity
    while (qryOther.next()) {
        numOther++;
    }
    //count total number of contacts
    while (qryAll.next()) {
        total++;
    }

    //return percentage of contacts who do not have a specified ethnicity
    return (float)numOther / (float)total;
}
