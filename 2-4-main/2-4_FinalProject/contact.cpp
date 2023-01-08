#include "contact.h"

Contact::Contact()
{

}

Contact::Contact(string lastName, string firstName)
{
    this->lastName = lastName;
    this->firstName = firstName;
}

int Contact::setAssignmentGroup(int group) {
    if (assignmentGroup != -1) {
        cout<<"Contact has already been assigned to group." << endl;
        return -1;
    }

    if (group >= 0 && group < 3) {
        assignmentGroup = group;
        return group;
    }
    else {
        cout << "Invalid group assignment." << endl;
        return -1;
    }
}

int Contact::getAssignmentGroup(){
    return assignmentGroup;
}

string Contact::addAdditionalInfo(string info){
    additionalInfo += ", " + info;
    return additionalInfo;
}

vector<Date> Contact::addRecruitmentAttempt(Date day){

    if(assignmentGroup < 0){
        cout<< "Contact has not yet been assigned" << endl;
        return recruitmentAttempts;
    }
    else if(assignmentGroup == 0){
        recruitmentAttempts.push_back(day);
        return recruitmentAttempts;
    }
    else{
        cout << "Contact is other group" << endl;
        return recruitmentAttempts;
    }

}
int Contact::getNumAttempts(){
    return recruitmentAttempts.size();
}
string Contact::setVolunteeringStatus(bool active){

    if(active){
        volunteeringStatus = "Volunteering";
        return volunteeringStatus;
    }
    else{
        volunteeringStatus = "Not volunteering";
        return volunteeringStatus;
    }

}

string Contact::getVolunteeringStatus() {
    return volunteeringStatus;
}

void Contact::setGender(string gender) {
    this->gender = gender;
}

string Contact::getGender() {
    return gender;
}
