#include <iostream>
#include <QtSql>
#include "gtest.h"
#include "../DataAnalysisEngine/dataanalysis.h"
#include "../contact.h"
#include <vector>

using namespace std;

class DataAnalysisEngineTest : public ::testing::Test {
protected:
    DataAnalysisEngineTest() {
        //open the sample database
        eng = new DataAnalysis("../../resources/sample_db.sqlite");
    }

    virtual ~DataAnalysisEngineTest() {
        //delete the pointer
        delete eng;
    }

    virtual void SetUp() {
        cout << "Start Test" << endl;
    }

    virtual void TearDown() {
        cout << "End Test" << endl;
    }

    //create a DataAnalysis object
    DataAnalysis *eng;
};

TEST_F(DataAnalysisEngineTest, testPercentMale) {
    //test percentage of male contacts
    ASSERT_EQ(eng->percentMale(), 1) << "Percent male contacts should be 1 (100%)" << endl;
}

TEST_F(DataAnalysisEngineTest, testPercentFemale) {
    //test percentage of female contacts
    ASSERT_EQ(eng->percentFemale(), 0) << "Percent male contacts should be 0 (0%)" << endl;
}

TEST_F(DataAnalysisEngineTest, testTotalPercentGender) {
    //test percentage of male and female contacts equals 100%
    float totalPercent = eng->percentMale() + eng->percentFemale();
    ASSERT_EQ(totalPercent, 1) << "Total percent of male and female contacts should be 1 (100%)" << endl;
}

TEST_F(DataAnalysisEngineTest, testPercentVolunteering) {
    //test percentage of volunteering contacts
    ASSERT_EQ(eng->percentVolunteering(), 0.6) << "Percent volunteering contacts should be 0.6 (60%)" << endl;
}

TEST_F(DataAnalysisEngineTest, testPercentNotVolunteering) {
    //test percentage of non volutneering contacts
    ASSERT_EQ(eng->percentNotVolunteering(), 0.4) << "Percent non volunteering contacts should be 0.4 (40%)" << endl;
}

TEST_F(DataAnalysisEngineTest, testTotalPercentVolunteering) {
    //test percentage of volunteering and non volunteering contacts equals 100%
    float totalPercent = eng->percentVolunteering() + eng->percentNotVolunteering();
    ASSERT_EQ(totalPercent, 1) << "Total percent of volunteering and non volunteering contacts should be 1 (100%)" << endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
