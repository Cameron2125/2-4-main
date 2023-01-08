#ifndef CONTACT_H
#define CONTACT_H

#include "date.h"
#include <vector>
#include <iostream>

using namespace std;

class Contact
{
public:
    Contact();
    Contact(string lastName, string firstName);

    int setAssignmentGroup(int group);
    int getAssignmentGroup();
    string addAdditionalInfo(string info);
    vector<Date> addRecruitmentAttempt(Date day);
    string setVolunteeringStatus(bool active);
    string getVolunteeringStatus();
    int getNumAttempts();

    void setGender(string gender);
    string getGender();

    string lastName = "";
    string firstName = "";
private:

    string address = "";
    int age;
    string gender = "";
    string ethnicity = "";
    string education = "";
    string occupation = "";
    string party = "";
    string additionalInfo = "";
    //volunteerRecruiter vr; //to be implemented later
    vector<Date> recruitmentAttempts;
    string volunteeringStatus = "";
    int assignmentGroup = -1;
};

#endif // CONTACT_H
