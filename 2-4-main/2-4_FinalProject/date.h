#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class Date
{
public:
    Date();

    std::string formattedDate = "";
    std::vector<int> validMonths;
    std::map<int, int> daysInMonth;
    int setDate(int month, int day, int year);
    bool validateDate(int month, int day, int year);

private:
    bool leapYearAdjusted(int month, int day, int year);
};

#endif // DATE_H
