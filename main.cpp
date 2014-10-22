#include <iostream>
#include "Recordset.h"
#include "Employee.h"
#include "Calendar.h"
#include <cassert>
#include <math.h>
#include <cstdlib>

using namespace std;

struct Command
{
    string mainCommand;
    string commandArguments;
};

void parseCommand(Command&, string);
void Employees();
void Scheduling();

int main()
{

    bool done = false;

    string rawInput;

    while (!done)
    {
        system("cls");

        cout << "Program Options" << endl;
        cout << "Employees" << endl;
        cout << "Scheduling" << endl;

        cout << "Type the name of the option you want to go to: ";
        getline(cin, rawInput);

        Command userCommand;

        parseCommand(userCommand, rawInput);

        if ( userCommand.mainCommand == "Employees" )
        {
            Employees();
        }
        else if ( userCommand.mainCommand == "Scheduling" )
        {
            Scheduling();
        }
        else if ( userCommand.mainCommand == "exit" )
        {
            done = true;
        }


    }


    return 0;
}

void Scheduling()
{
    string rawInput;

    getline(cin, rawInput);

    Calendar cal;

    cal.printCalendar(rawInput);

    getchar();
}

void Employees()
{


    Employee employees;

    string mainCommand = "";
    string rawInput = "";
    string prompt = "Command>";

    bool done = false;

    system("cls");
    employees.viewEmployees("");

    while ( !done )
    {
        cout << prompt;
        getline(cin, rawInput);

        system("cls");
        employees.viewEmployees("");

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
            cout << "edit <search column:search value>, <column to edit:value to replace>, ..." << endl;
            cout << "exit" << endl;
        }
        else
        {
            cout << "Unknown command: " << userCommand.mainCommand << endl;
            cout << "Enter help for a list of commands." << endl;
        }

    }

    return;
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

