#include <iostream>
#include "Recordset.h"
#include "Employee.h"
#include <cassert>
#include <math.h>

using namespace std;

struct Command
{
    string mainCommand;
    string commandArguments;
};

string trim(string);
void parseCommand(Command&, string);

int main()
{


    Recordset rc1("test.txt", ";");

    rc1.addField("Test1");
    rc1.addField("Test2");
    rc1.addField("Test3");
    rc1.addField("Test4");
    rc1.addField("Test5");
    rc1.addField("Test6");
    rc1.addField("Test7");
    rc1.addField("Test8");
    rc1.addField("Test9");
    rc1.addField("Test10");

    for ( int i = 0 ; i < 20000 ; i++)
    {
        rc1.addRow();

        rc1.fields("Test1")= i;
        rc1.fields("Test2")= i;
        rc1.fields("Test3")= i;
        rc1.fields("Test4")= i;
        rc1.fields("Test5")= i;
        rc1.fields("Test6")= i;
        rc1.fields("Test7")= i;
        rc1.fields("Test8")= i;
        rc1.fields("Test9")= i;
        rc1.fields("Test10")= i;
    }

    cout << "Done" << endl;

    rc1.write();

    cout << "Wrote to file" << endl;

    Employee employees;

    string mainCommand = "";
    string rawInput = "";

    bool done = false;

    while ( !done )
    {

        getline(cin, rawInput);

        Command userCommand;

        parseCommand(userCommand, rawInput);

        if ( userCommand.mainCommand == "add" )
        {
            employees.addEmployee(userCommand.commandArguments);
        }
        else if ( userCommand.mainCommand == "view" )
        {
            employees.viewEmployees(userCommand.commandArguments);
        }
        else if ( userCommand.mainCommand == "remove" )
        {
            employees.removeEmployee(userCommand.commandArguments);
        }
        else if ( userCommand.mainCommand == "edit" )
        {
            employees.editEmployee(userCommand.commandArguments);
        }
        else if ( userCommand.mainCommand == "exit" )
        {
            done = true;
        }
        else if ( userCommand.mainCommand == "help" )
        {
            cout << "add <column name:row value>, ..." << endl;
            cout << "remove <column name:row value>, ... " << endl;
            cout << "view <column name>, ... " << endl;
            cout << "exit" << endl;
        }
        else
        {
            cout << "Unknown command: " << userCommand.mainCommand << endl;
            cout << "Enter help for a list of commands." << endl;
        }

    }

    return 0;
}

void parseCommand(Command& com, string rawInput)
{

    rawInput = trim(rawInput);

    int position = 0;

    if ( ( position = rawInput.find(" ")) == std::string::npos )
    {
        com.mainCommand = rawInput;
    }
    else
    {
        com.mainCommand = trim(rawInput.substr(0, position));
        rawInput.erase(0, position + 1 );
        com.commandArguments = trim(rawInput.substr(0, rawInput.length()));
    }

}

