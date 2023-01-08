#include "date.h"

Date::Date()
{
    //set valid months that can be inputted
    validMonths = {1,2,3,4,5,6,7,8,9,10,11,12};
    for (int i = 1; i <= 12; i++) {
        //listing off all months w/ 31 days
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 ||
            i == 10 || i == 12) {

            daysInMonth[i] = 31;
        }
        //all months with 30 days
        else if (i == 4 || i == 6 || i == 9 || i == 11) {
            daysInMonth[i] = 30;
        }
        else {
            daysInMonth[i] = 29;
        }
    }
}

/**
 * @brief setDate:
 * @param month
 * @param day
 * @param year
 * @return
 */
int Date::setDate(int month, int day, int year) {
    //if invalid date, end
    if (!validateDate(month, day, year)) {
        return -1;
    }

    //begin formatting date
    formattedDate = "";

    std::string formattedMonth = "";
    //prepend a 0 if less than 10
    if (month < 10) {
         formattedMonth =+ "0";
    }
    formattedMonth += std::to_string(month);

    std::string formattedDay = "";
    if (day < 10) {
         formattedDay =+ "0";
    }
    formattedDay += std::to_string(day);

    std::string formattedYear = std::to_string(year);

    formattedDate += formattedMonth + "/" + formattedDay + "/" + formattedYear;
    return 0;
}

/**
 * @brief validateDate: iterates through acceptable month values
 * and compares with inputted month. Repeats for day and year.
 * @param month
 * @param day
 * @param year
 * @return
 */
bool Date::validateDate(int month, int day, int year) {
    //check if input month is in validMonths list
    bool validMonth = (std::find(validMonths.begin(), validMonths.end(), month) != validMonths.end());
    if (!validMonth) {
        std::cout << "invalid month entered";
        return false;
    }

    //ensure day is within range of acceptable days(adjusted for leap year)
    if (day >= 1 && day <= daysInMonth[month]
        && leapYearAdjusted(month, day, year)) {
    }
    else{
        std::cout << "invalid day entered";
        return false;
    }

    bool validYear = false;
    //if year has four digits, accept
    if (year >= 1000 && year < 9999) {
        validYear = true;
    }
    if (!validYear) {
        std::cout << "invalid year entered";
        return false;
    }
    return true;
}

/**
 * @brief leapYearAdjusted: if date is in month of february, and
 * it is a leap year, then 29 is a valid number of days. If it is
 * not a leap year, 29 is not valid.
 * @param month
 * @param day
 * @param year
 * @return
 */
bool Date::leapYearAdjusted(int month, int day, int year) {
    if (month != 2) {
        return true;
    }
    else if (year % 100 == 0 && year % 400 == 0) {
        return true;
    }
    else if (year % 100 != 0 && year % 4 == 0) {
        return true;
    }
    else if (day == 29) {
        return false;
    }
    else{
        return false;
    }
}
