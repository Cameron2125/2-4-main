#include <iostream>
#include "dbcontrol.h"

using namespace std;

int main()
{
    dbControl test;
    test.openDB();
    cout << test.getAvgValue("Age", "Contacts") << endl;

}
