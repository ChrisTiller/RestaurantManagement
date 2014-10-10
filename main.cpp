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

void parseCommand(Command&, string);

int main()
{

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

