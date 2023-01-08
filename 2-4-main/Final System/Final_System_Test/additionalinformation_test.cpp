#include <iostream>
#include <QtSql>
#include "gtest/gtest.h"
#include "../Final_System/additionalinformation.h"

using namespace std;

class additionalinformation_test : public ::testing::Test {
protected:

    virtual ~additionalinformation_test() {

    }

    virtual void SetUp() {
        cout << "Start Test" << endl;
    }

    virtual void TearDown() {
        cout << "End Test" << endl;
    }
};



TEST(correctDateNorm, TESTSIMPLE) {
    //testing that validDate data works for both valid and invalid cases
    additionalInformation ad;
    ASSERT_TRUE(ad.validDate(1,1,2020));
    ASSERT_FALSE(ad.validDate(200,30,2020));
}

TEST(february, TESTSIMPLE) {
    //testing that validDate data works for both valid and invalid cases
    //in febuary
    additionalInformation ad;
    ASSERT_TRUE(ad.validDate(29,2,2020));
    ASSERT_FALSE(ad.validDate(29,2,2021));
    ASSERT_FALSE(ad.validDate(29,2,2100));
    ASSERT_TRUE(ad.validDate(29,2,2000));
}

TEST(getCID, TESTSIMPLE){
    additionalInformation ad;
    dbControl *db = new dbControl("project_db.sqlite");
    ad.load(1, db);
    //testing that Molly Sosa returns correct CID
    ASSERT_TRUE("1003" == ad.getCID("Molly Sosa", "1"));
}

TEST(getAttemps, TESTSIMPLE){
    additionalInformation ad;
    dbControl *db = new dbControl("project_db.sqlite");
    ad.load(1, db);
    //checking that number of attempts are correct
    ASSERT_TRUE("1" == ad.getAttempts("1003"));
}
