#include <iostream>
#include "Recordset.h"
#include "Employee.h"
#include <cassert>

using namespace std;

int main()
{

    Employee employees;

    string mainCommand = "";
    string rawInput = "";

    bool done = false;

    while ( !done )
    {

        getline(cin, rawInput);

        mainCommand = rawInput;

        if ( mainCommand == "add" )
        {
            employees.addEmployee("Chris");
        }
        else if ( mainCommand == "view" )
        {
            employees.viewEmployees("  FNAME  ,");
        }
        else if ( mainCommand == "done" )
        {
            done = true;
        }

    }

    return 0;
}
