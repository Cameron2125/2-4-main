#include <iostream>
#include <QtSql>
#include "gtest.h"
#include "../Final_System/datagui.h"
#include "../Final_System/shop.h"


using namespace std;

class DataAnalysisTest : public ::testing::Test {
protected:
    DataAnalysisTest() {
        //create the engine
    }

    virtual ~DataAnalysisTest() {
        //delete the pointer
        //delete eng;
    }

    virtual void SetUp() {
        cout << "Start Test" << endl;
    }

    virtual void TearDown() {
        cout << "End Test" << endl;
    }


};
TEST_F(DataAnalysisTest, testGetAverage) {
    //preparing the objects for dataGUI
     DataGui eng(1);
     dbControl db("../Final_System/resources/testingDB.sqlite");
     eng.load(&db);

     //testing that average interest for contacts of VID 1 is between 0.84 and 0.85
    ASSERT_TRUE(eng.getAverage(1,0,12,"Contacts") > 0.84 && eng.getAverage(1,0,12,"Contacts") < 0.85);

    //testing that average age for contacts of VID 1 is between 23 and 23.5
    ASSERT_TRUE(eng.getAverage(1,0,4,"Contacts") > 23 && eng.getAverage(1,0,4,"Contacts") < 23.5) ;
    db.closeDB();



}
TEST_F(DataAnalysisTest, testethInterest) {
    //preparing the objects for dataGUI

    DataGui eng(1);
    dbControl db("../Final_System/resources/testingDB.sqlite");
    eng.load(&db);
    ASSERT_TRUE(eng.ethInterest().size() == 6);
    std::vector<double> vals = eng.ethInterest();

    //testing that each value for interest is correct
    //follows structure black,white,asian,hispanic, american indian, other
    ASSERT_TRUE(vals[0] > 0.92 && vals[0] < 0.94);
    ASSERT_TRUE(vals[1] > 0.86 && vals[1] < 0.87);
    ASSERT_TRUE(vals[2] > 0.99 && vals[2] < 1.01);
    ASSERT_TRUE(vals[3] > 0.87 && vals[3] < 0.879);
    ASSERT_TRUE(vals[4] > -0.01 && vals[4] < 0.01);
    ASSERT_TRUE(vals[5] > 0.9 && vals[5] < 0.91);
    db.closeDB();

}
TEST_F(DataAnalysisTest, testEduInterest) {
    //preparing the objects for dataGUI

    DataGui eng(1);
    dbControl db("../Final_System/resources/testingDB.sqlite");
    eng.load(&db);
    std::vector<double> vals = eng.eduInterest();

    //testing that interest of each type of education is correctly represented as is in DB
    //structure follows High School, College, Masters, Doctorate, Other
    ASSERT_TRUE(eng.eduInterest().size() == 5);
    ASSERT_TRUE(eng.eduInterest()[0] > 0.92 && eng.eduInterest()[0] < 0.93);
    ASSERT_TRUE(eng.eduInterest()[1] > 0.86 && eng.eduInterest()[1] < 0.87);
    ASSERT_TRUE(eng.eduInterest()[2] > 0.99 && eng.eduInterest()[2] < 1.01);
    ASSERT_TRUE(eng.eduInterest()[3] > 0.87 && eng.eduInterest()[3] < 0.88);
    db.closeDB();



}
TEST_F(DataAnalysisTest, testEthDist) {
    //preparing the objects for dataGUI

    DataGui eng(1);
    dbControl db("../Final_System/resources/testingDB.sqlite");
    eng.load(&db);
    std::vector<double> vals = eng.ethDist();

    //testing that correct number of contacts with certain ethnicity
    // are recorded correctly
    //follows structure black,white,asian,hispanic, american indian, other
    ASSERT_TRUE(eng.ethDist().size() == 6);
    ASSERT_TRUE(eng.ethDist()[0] == 66);
    ASSERT_TRUE(eng.ethDist()[1] == 49);
    ASSERT_TRUE(eng.ethDist()[2] == 76);
    ASSERT_TRUE(eng.ethDist()[3] == 82);
    ASSERT_TRUE(eng.ethDist()[4] == 0);
    ASSERT_TRUE(eng.ethDist()[5] == 351);
    db.closeDB();



}
TEST_F(DataAnalysisTest, testEduDist) {
    //preparing the objects for dataGUI

    DataGui eng(1);
    dbControl db("../Final_System/resources/testingDB.sqlite");
    eng.load(&db);
    std::vector<double> vals = eng.eduDist();

    //testing that each type of education is correctly represented as is in DB
    //structure follows High School, College, Masters, Doctorate, Other
    ASSERT_TRUE(eng.eduDist().size() == 5);
    ASSERT_TRUE(eng.eduDist()[0] == 65);
    ASSERT_TRUE(eng.eduDist()[1] == 75);
    ASSERT_TRUE(eng.eduDist()[2] == 48);
    ASSERT_TRUE(eng.eduDist()[3] == 82);
    ASSERT_TRUE(eng.eduDist()[4] == 81);
    db.closeDB();


}

