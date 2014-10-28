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
#include"inventory.h"
#include "orders.h"
#include "menu.h"

using namespace std;

void Employees();
void Scheduling();
void Payrolls();
void Open_inventory();
void passwordAdmin();
void operation(bool);
void Menu();
void Cashier();
void restaturantMenuConfigurationsMenu();

Inventory open;
int main()
{
    cout << setprecision(2) << fixed << endl;  // set decimal to two decimal places
	system("mode con cols=80 lines=43");  // resizing the console window
	passwordAdmin();
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

void Open_inventory()
{
    open.menu_Display();
}

void passwordAdmin()
{
    open.welcomeMessage();
    int pass_code;
    cout << "\n " << endl;
	cout << "\t Enter the Password <five digits No>:  ";
	cin >> pass_code;

	// to get rid of non-integer value entered
	cin.clear();
	cin.ignore( 100, '\n' );

	// Password for authentication
	if (( pass_code == 25801 )||( pass_code == 98765 ))
	{
	   operation(true);
	   getch();
    }
    else
    {
        system("cls");
        cout<<"Invalid Password";
        //passwordAdmin();
        operation(false);
        getch();
    }
}

void operation(bool isAdmin)
{
    bool done = false;
    string rawInput;

    while (!done)
    {
        system("cls");
        open.welcomeMessage();
        cout << "Program Options" << endl;

        cout << "Inventory" << endl;
        cout << "Cashier" << endl;

        if ( isAdmin )
        {
            cout << "Employees" << endl;
            cout << "Scheduling" << endl;
            cout << "Payroll" << endl;
            cout << "Menu" << endl;
        }

        cout << "Select the name of the option you want to go to: ";
        getline(cin, rawInput);

        Command userCommand;

        parseCommand(userCommand, rawInput);

        if ( userCommand.mainCommand == "Employees" )
        {
            if ( isAdmin)
                Employees();
        }
        else if ( userCommand.mainCommand == "Scheduling" )
        {
            if ( isAdmin )
                Scheduling();
        }
        else if ( userCommand.mainCommand == "Payroll" )
        {
            if (isAdmin)
                Payrolls();
        }
        else if ( userCommand.mainCommand == "Inventory" )
        {
            Open_inventory();
        }
        else if ( userCommand.mainCommand == "Cashier")
        {
            Cashier();
        }
        else if ( userCommand.mainCommand == "Menu" )
        {
            if ( isAdmin)
                Menu();
        }
        else if ( userCommand.mainCommand == "exit" )
        {
            done = true;
        }
    }
}

void Menu()
{
    menuItems *mi=new menuItems();
	menuItems *miLoadData=new menuItems();
	orderItems *oi=new orderItems();
    char name[500];

	mi->loadDataFromTextFile();

	int choice,id,qty;
	id=-1;
	float price;
    restaturantMenuConfigurationsMenu();
        string temp;
        getline(cin, temp);

        choice = stringToInt(temp);
        switch(choice)
        {
        case 1:
            cout<<"Enter Item Name: ";
            cin>>name;
            cout<<"Enter Price: ";
            cin>>price;
            mi->addMenuItem(name,price);
            miLoadData->loadDataFromTextFile();
            break;
        case 2:
            mi->displayMenuItems();
            break;
        case 3:
            cout<<"\n\nEnter Item ID to delete (Enter 0 to Cancel) : ";
            cin>>id;
            if(id==0)
                return;


            if(mi->searchMenuItem(id))
            {
                mi->deleteMenuItem(id);
                miLoadData->loadDataFromTextFile();
            }
            else
                cout<<"Item Not Found\n";

            break;
        case 4:
            cout<<"\n\nEnter Item ID to Modify Details (Enter 0 to Cancel) : ";
            cin>>id;
            if(id==0)
                return;

            if(mi->searchMenuItem(id))
            {
                cout<<"Enter New Name: ";
                cin>>name;
                cout<<"Enter New Price: ";
                cin>>price;
                mi->editMenuItem(id,name,price);
                miLoadData->loadDataFromTextFile();
            }
            else
                cout<<"Item Not Found\n";
            break;
        default:
            cout<<"Invalid Input. Exiting...\n";
            return;
            break;
        }

}

void Cashier()
{


    menuItems *mi=new menuItems();
	menuItems *miLoadData=new menuItems();
	orderItems *oi=new orderItems();
   // char name[500];

	mi->loadDataFromTextFile();

	int choice,id,qty;
	id=-1;
	float price;

    mi->displayMenuItems();
        char name[50] ;
        while(id!=0)
        {

            cout<<"\n\nEnter Item ID to add to the order (Enter 0 to Finish) : ";            string temp;
            getline(cin, temp);
            id = stringToInt(temp);
            if(id==0)
            {
                oi->displayMenuItems();
                //display order details
                return;
            }
            strcpy(name,mi->getItemName(id));
            price=mi->getItemPrice(id);
            cout<<"\n\nEnter Quantity: ";
            temp = "";
            getline(cin, temp);            qty = stringToInt(temp);

            oi->addItem(id,name,price,qty);
            miLoadData->loadDataFromTextFile();
        }
}

void restaturantMenuConfigurationsMenu()
{
	cout<<"Press 1 to Add New Menu Item\n";
	cout<<"Press 2 to Display All Menu Items\n";
	cout<<"Press 3 to Delete A Menu Item\n";
	cout<<"Press 4 to Modify a Menu Item\n";
	cout<<"Any other key to exit\n";
}
