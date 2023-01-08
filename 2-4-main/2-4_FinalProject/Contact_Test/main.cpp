#include <iostream>
#include "gtest.h"
#include "../contact.h"
#include "../date.h"

using namespace std;

class ContactTest : public ::testing::Test {
protected:
    ContactTest() {

    }

    virtual ~ContactTest() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
};

TEST(general, TEST_NAME) {
    //create new Contact to test
    Contact *c = new Contact("Star", "Patrick");

    //ensure constructor properly assigns first and last name
    ASSERT_EQ(c->firstName, "Patrick") << "Both names should be \"Patrick\"" << endl;
    ASSERT_EQ(c->lastName, "Star") << "Both names should be \"Star\"" << endl;

    //set the gender of the Contact and ensure it is set properly
    c->setGender("male");
    ASSERT_EQ(c->getGender(), "male") << "Both genders should be \"male\"" << endl;

    //test setting the volunteering status of the Contact
    ASSERT_EQ(c->setVolunteeringStatus(true), "Volunteering") << "Contact should be \"Volunteering\"" << endl;
    ASSERT_EQ(c->setVolunteeringStatus(false), "Not volunteering") << "Contact should be \"Not volunteering\"" << endl;

    //add recruitment attempts and test they are accounted for
    Date d;
    c->addRecruitmentAttempt(d);
    c->addRecruitmentAttempt(d);
    ASSERT_EQ(c->getNumAttempts(), 0) << "Contact should have 0 attempts (hasn't been added to a group)" << endl;
    ASSERT_EQ(c->setAssignmentGroup(0), 0) << "Contact should be assigned to group 0" << endl;
    c->addRecruitmentAttempt(d);
    c->addRecruitmentAttempt(d);
    ASSERT_EQ(c->getNumAttempts(), 2) << "Contact should have 2 attempts" << endl;

    //delete Contact pointer after test is over
    delete c;
}

TEST(general, TEST_GENDER) {

}

TEST_F(ContactTest, TESTFIXTURE) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
