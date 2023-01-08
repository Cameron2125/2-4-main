#include <iostream>
#include <QtSql>
#include "gtest/gtest.h"
#include "../Final_System/dbControl/dbcontrol.h"

using namespace std;

class dbControl_Test : public ::testing::Test {
protected:
    dbControl_Test() {

    }

    virtual ~dbControl_Test() {

    }

    virtual void SetUp() {
        cout << "Start Test" << endl;
    }

    virtual void TearDown() {
        cout << "End Test" << endl;
    }
};



TEST(min, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    ASSERT_TRUE(18 == db->getMinValue("Age", "Organizer"));
    db->closeDB();
}

TEST(max, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    ASSERT_TRUE(21 == db->getMaxValue("Age", "Organizer"));
    db->closeDB();
}

TEST(avg, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    float avg1 = 19.8;
    ASSERT_TRUE(avg1 == db->getAvgValue("Age", "Organizer"));
    db->closeDB();
}

TEST(runQuery, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    QSqlQuery q = db->runQuery("select Name from Organizer");
    if(q.next()){
        ASSERT_TRUE("Paola Bentley" == q.value(0).toString());
    }
    db->closeDB();
}

TEST(getField, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    std::string field = db->getField(0, 1,  "Organizer");
    ASSERT_TRUE("1" == field);
    db->closeDB();
}

TEST(getTable, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    QSqlQuery q = db->getTable("Organizer");
    if(q.next()){
        ASSERT_TRUE("1" == q.value(0).toString());
    }
    db->closeDB();
}

TEST(getColumn, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    QSqlQuery q = db->getColumn("Name", "Organizer");
    if(q.next()){
        ASSERT_TRUE("Paola Bentley" == q.value(0).toString());
    }
    db->closeDB();
}

TEST(getTableLength, TESTSIMPLE) {
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    int length = db->getTableLength("Organizer");
    ASSERT_TRUE(7 == length);
    db->closeDB();
}

TEST(getLIDFromUserName, TESTSIMPLE){
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
    QString id = db->getLIDFromUserName("fowlersp");
    ASSERT_TRUE("6" == id);
    db->closeDB();
}
