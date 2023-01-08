#include <iostream>
#include <QtSql>
#include "gtest.h"
#include "../Final_System/DataAnalysisEngine/dataanalysis.h"


using namespace std;

class DataAnalysisEngine_Test : public ::testing::Test {
protected:
    DataAnalysisEngine_Test() {
        //create the engine
        eng = new DataAnalysis(db);
    }

    virtual ~DataAnalysisEngine_Test() {
        //delete the pointer
        //delete eng;
    }

    virtual void SetUp() {
        cout << "Start Test" << endl;
    }

    virtual void TearDown() {
        cout << "End Test" << endl;
    }

    //create a DataAnalysis object
    DataAnalysis *eng;
    //create a dbControl object
    dbControl *db = new dbControl("../Final_System/resources/test_db.sqlite");
};

TEST_F(DataAnalysisEngine_Test, testPercentMale) {
    //test percentage of male contacts
    ASSERT_TRUE((eng->percentMale() - 0.55) < 0.001) << "Percent male contacts should be 0.55 (55%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentFemale) {
    //test percentage of female contacts
    ASSERT_TRUE((eng->percentFemale() - 0.45) < 0.001) << "Percent female contacts should be 0.45 (45%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentVolunteering) {
    //test percentage of volunteering contacts
    ASSERT_TRUE((eng->percentVolunteering() - 0) < 0.001) << "Percent volunteering contacts should be 0 (0%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentNotVolunteering) {
    //test percentage of non volutneering contacts
    ASSERT_TRUE((eng->percentNotVolunteering() - 1) < 0.001) << "Percent non volunteering contacts should be 1 (100%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentWhite) {
    //test percentage of contacts who identify as white
    ASSERT_TRUE((eng->percentWhite() - 0.4) < 0.001) << "Percent white contacts should be 0.4 (40%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentBlack) {
    //test percentage of contacts who identify as black
    ASSERT_TRUE((eng->percentBlack() - 0.15) < 0.001) << "Percent black contacts should be 0.15 (15%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentHispanic) {
    //test percentage of contacts who identify as hispanic
    ASSERT_TRUE((eng->percentHispanic() - 0.3) < 0.001) << "Percent hispanic contacts should be 0.3 (30%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentAsian) {
    //test percentage of contacts who identify as asian
    ASSERT_TRUE((eng->percentAsian() - 0) < 0.001) << "Percent asian contacts should be 0 (0%)" << endl;
}

TEST_F(DataAnalysisEngine_Test, testPercentOther) {
    //test percentage of contacts who identify as other
    ASSERT_TRUE((eng->percentOther() - 0.15) < 0.001) << "Percent other contacts should be 0.15 (15%)" << endl;
}
