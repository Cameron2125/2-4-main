#include <iostream>
#include "gtest.h"
#include "../contact.h"
#include "../date.h"

using namespace std;

class DateTest : public ::testing::Test {
protected:
    DateTest() {

    }

    virtual ~DateTest() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
};

/**
 * @brief test for dates with numbers <10 (success)
 */
TEST(setDate1, TESTSIMPLE) {
    Date d = Date();
    d.setDate(1,2,2000);
    ASSERT_EQ(d.formattedDate, "01/02/2000");
}

/**
 * @brief test for dates with mix of numbers <10 and >10 (success)
 */
TEST(setDate2, TESTSIMPLE) {
    Date d = Date();
    d.setDate(10,2,2000);
    ASSERT_EQ(d.formattedDate, "10/02/2000");
}

/**
 * @brief test for dates with >10 (success)
 */
TEST(setDate3, TESTSIMPLE) {
    Date d = Date();
    d.setDate(11,30,2102);
    ASSERT_EQ(d.formattedDate, "11/30/2102");
}

/**
 * @brief test for invalid day (failure)
 */
TEST(setDate4, TESTSIMPLE) {
    Date d = Date();
    d.setDate(11,32,2102);
    ASSERT_EQ(d.formattedDate, "");
}

/**
 * @brief test for invalid month (failure)
 */
TEST(setDate5, TESTSIMPLE) {
    Date d = Date();
    d.setDate(13,31,2102);
    ASSERT_EQ(d.formattedDate, "");
}

/**
 * @brief test for invalid year (failure)
 */
TEST(setDate6, TESTSIMPLE) {
    Date d = Date();
    d.setDate(10,20,57438);
    ASSERT_EQ(d.formattedDate, "");
}

/**
 * @brief test for invalid date with boundary values (failure)
 */
TEST(setDate7, TESTSIMPLE) {
    Date d = Date();
    d.setDate(0,20,1999);
    ASSERT_EQ(d.formattedDate, "");
}

/**
 * @brief test for invalid date with boundary values (failure)
 */
TEST(setDate8, TESTSIMPLE) {
    Date d = Date();
    d.setDate(1,0,1999);
    ASSERT_EQ(d.formattedDate, "");
}

/**
 * @brief test for appended 0's value (failure)
 */
TEST(setDate9, TESTSIMPLE) {
    Date d = Date();
    d.setDate(0005,21,1999);
    ASSERT_EQ(d.formattedDate, "05/21/1999");
}

/**
 * @brief leap year test (failure)
 */
TEST(leapYear1, TESTSIMPLE) {
    Date d = Date();
    d.setDate(2,29,2022);
    //should be invalid date
    ASSERT_EQ(d.formattedDate, "");
}

/**
 * @brief Leap year test (success)
 */
TEST(leapYear2, TESTSIMPLE) {
    Date d = Date();
    d.setDate(2,29,2024);
    //should be valid date
    ASSERT_EQ(d.formattedDate, "02/29/2024");
}

/**
 * @brief Leap year test for turn of century (failure)
 */
TEST(leapYear3, TESTSIMPLE) {
    Date d = Date();
    d.setDate(2,29,2500);
    //should be invalid date
    ASSERT_EQ(d.formattedDate, "");
}

/**
 * @brief Leap year test for turn of century (success)
 */
TEST(leapYear4, TESTSIMPLE) {
    Date d = Date();
    d.setDate(2,29,2400);
    //should be valid date
    ASSERT_EQ(d.formattedDate, "02/29/2400");
}

/**
 * @brief Leap year test for turn of century (success)
 */
TEST(leapYear5, TESTSIMPLE) {
    Date d = Date();
    d.setDate(2,29,2400);
    //should be valid date
    ASSERT_EQ(d.formattedDate, "02/29/2400");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
