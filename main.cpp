#include <iostream>
#include "Recordset.h"
#include "Employee.h"
#include "Calendar.h"
#include "Scheduling.h"
#include "helperFile.h"
#include "Payroll.h"
#include <cassert>
#include <math.h>
#include <cstdlib>

using namespace std;

void Employees();
void Scheduling();
void Payrolls();

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
        cout << "Payroll" << endl;

        cout << "Select the name of the option you want to go to: ";
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
        else if ( userCommand.mainCommand == "Payroll" )
        {
            Payrolls();
        }
        else if ( userCommand.mainCommand == "exit" )
        {
            done = true;
        }
    }

    return 0;
}

void Payrolls()
{
    Payroll payroll;

    string mainCommand = "";
    string rawInput = "";
    string prompt = "Command>";

    bool done = false;

    system("cls");

    while ( !done )
    {
        cout << prompt;

        getline(cin, rawInput);

        system("cls");

        Command userCommand;

        parseCommand(userCommand, rawInput);

        if ( userCommand.mainCommand == "payroll" )
        {
            payroll.completePayroll(userCommand.commandArguments);
        }
        else if ( userCommand.mainCommand == "help" )
        {
            cout << "payroll <date from>-<date through>" << endl;
        }
        else if ( userCommand.mainCommand == "exit")
        {
            done = true;
        }

    }

    return;
}

void Scheduling()
{
    Schedules Schedule;

    string mainCommand = "";
    string rawInput = "";
    string prompt = "Command>";

    bool done = false;

    system("cls");

    while ( !done )
    {
        cout << prompt;

        getline(cin, rawInput);

        system("cls");

        Command userCommand;

        parseCommand(userCommand, rawInput);

        if ( userCommand.mainCommand == "calendar" )
        {
            Schedule.viewCalendar(userCommand.commandArguments);
            done = true;
        }
        else if ( userCommand.mainCommand == "help" )
        {
            cout << "calendar <mm/yyyy>" << endl;
        }
        else if ( userCommand.mainCommand == "exit")
        {
            done = true;
        }

    }

    return;
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
            cout << "Enter help for a list of commands" << endl;
        }

    }

    return;
}
