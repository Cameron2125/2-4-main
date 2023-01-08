#include <iostream>
#include "gtest.h"
#include "../dbControl/dbcontrol.h"

using namespace std;

class dbTest : public ::testing::Test{
protected:
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    dbTest(){
    }

    virtual ~dbTest(){

    }

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
        std::cout<<"Start Test"<<endl;
    }
    virtual void TearDown() {
        std::cout<<"Test Complete"<<endl;
    }
    // Objects declared here can be used by all tests in the test case for Foo.

};

TEST(min, TESTSIMPLE) {
    dbControl db;
    ASSERT_TRUE(18 == db.getMinValue("Age", "Organizer"));
    db.closeDB();
}

TEST(max, TESTSIMPLE) {
    dbControl db;
    ASSERT_TRUE(21 == db.getMaxValue("Age", "Organizer"));
    db.closeDB();
}

TEST(avg, TESTSIMPLE) {
    dbControl db;
    float avg1 = 19.8;
    ASSERT_TRUE(avg1 == db.getAvgValue("Age", "Organizer"));
    db.closeDB();
}

TEST(runQuery, TESTSIMPLE) {
    dbControl db;
    QSqlQuery q = db.runQuery("select Name from Organizer");
    if(q.next()){
        ASSERT_TRUE("Paola Bentley" == q.value(0).toString());
    }
    db.closeDB();
}

TEST(getField, TESTSIMPLE) {
    dbControl db;
    std::string field = db.getField(0, 1,  "Organizer");
    ASSERT_TRUE("1" == field);
    db.closeDB();
}

TEST(getTable, TESTSIMPLE) {
    dbControl db;
    QSqlQuery q = db.getTable("Organizer");
    if(q.next()){
        ASSERT_TRUE("1" == q.value(0).toString());
    }
    db.closeDB();
}

TEST(getColumn, TESTSIMPLE) {
    dbControl db;
    QSqlQuery q = db.getColumn("Name", "Organizer");
    if(q.next()){
        ASSERT_TRUE("Paola Bentley" == q.value(0).toString());
    }
    db.closeDB();
}

TEST(getTableLength, TESTSIMPLE) {
    dbControl db;
    int length = db.getTableLength("Organizer");
    ASSERT_TRUE(5 == length);
    db.closeDB();
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
