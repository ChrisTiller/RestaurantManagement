#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include<climits>
#include <fstream>

using namespace std;

int MAX_CHAR = 80;

class ingredient{
    public:
	char itemName[80]; // will store name of items
	int itemcode;//will store the unique itemcode
	int intrQty; // will store quantity values
	double perPrice; // will store the price per item
	double total; // will store total price of items
    }inventory[100];

class Inventory
{
public:
    void bar();
    void errorMsg();
    void menuDisplay();
    void viewInventory();
    void welcomeMessage();
    void invTempl();
    void nameSearch();
    void addRemoveMenu();
    void addQty();
    void addNewItem();
    void delItem();
    void printListing(ingredient inventory[]);
private:
    int optionSelect;
    string user;
    int i;
    int j;
    int listCount;
    int x;
    double qtyTot;
    double perPriceTot;
    double priceTot;
    int printInventory(ingredient inventory[], int);
    int readFile();
    char exitAns;

};
//FUNCTION DEFINITIONS
// used for header of the program
void Inventory::welcomeMessage(){
	cout << "\n\n\t\t\t ------------------------------" << endl;
	cout << "\t\t\t  CS240 Restaurant MGMT System \n";
	cout << "\t\t\t ------------------------------" << endl;
	cout << "\t\t\t      -Inventory Manager-" << endl;
	cout << endl << endl;
};

// used for any error that occured
void Inventory::errorMsg()
{
	cout << "\t\t\tInvalid value. Try again." << endl;
}

// external file reading goes in this function
int Inventory::readFile()
{
	char stkName[MAX_CHAR], qty[MAX_CHAR], perPrice[MAX_CHAR],itemcode[MAX_CHAR];
	double total, qtyTot = 0, perPriceTot = 0, priceTot = 0;
	int i = 1, listCount = 0;
	//char newFileConfirm;

	ifstream stockNameRead;
	stockNameRead.open("inventory.txt");

	if(stockNameRead.fail()) // this part is to check whether the file exist or not
	{
		cout << "\nFile not found." << endl;
		getch();
		menuDisplay();  // program will go back to main menu if the file doesn't exist
	}

	while(!stockNameRead.eof()) // loop until file
	{
		// this statement will store information (in char) from external file, for temporarily
		// it will read until character ';' is found
		stockNameRead.getline(stkName, MAX_CHAR, ';');
		// it will read until a space is found
		stockNameRead.getline(itemcode, MAX_CHAR, ',');
		// it will read until a space is found
		stockNameRead.getline(qty, MAX_CHAR, ',');
		// it will read until new line is found
		stockNameRead.getline(perPrice, MAX_CHAR, '\n');
		// this will copy character in stkName into the struct data
		strcpy(inventory[i].itemName, stkName);
		// this will convert char to int (qty is char)
		inventory[i].itemcode = atoi(itemcode);
		// this will convert char to int (qty is char)
		inventory[i].intrQty = atoi(qty);
		// this will convert char to floating value (perPrice is char)
		inventory[i].perPrice = atof(perPrice);
		// total calculation goes here
		inventory[i].total = (inventory[i].intrQty * inventory[i].perPrice);
		i++;
		listCount++; // used for count the number of item in external file
	}
	stockNameRead.close();
	return listCount;
}

// used for printing the data in class after external file has read
int Inventory::printInventory(ingredient inventory[], int listCount)
{
	int count = 1;
	qtyTot = 0;
	perPriceTot = 0;
	priceTot = 0;
	for ( int count = 1; count <= listCount; count++ )
	{
		qtyTot = qtyTot + inventory[count].intrQty;  // calculation for total of quantity
		perPriceTot = perPriceTot + inventory[count].perPrice; // calculation for total of price per item
		priceTot = priceTot + inventory[count].total; // calculation for total of price total
		// this part will output the data calculated
		cout << (count) << "." << setw(3) << setfill(' ') << "";
		cout << inventory[count].itemName << "\t\t";
		cout << inventory[count].itemcode << "\t";
		cout << inventory[count].intrQty << "\t";
		cout << "$ " << inventory[count].perPrice;
		cout << "\t\t    $ " << inventory[count].total << endl;
	}
	cout << "\n*" << setw(70) << setfill('*') << "" << endl;
	// printing the total calculated before
	cout << "      Total : ";
	cout << "\t\t\t" << setprecision(0) << qtyTot << "\t" << "$ "<< setprecision(2) << perPriceTot << "\t\t    ";
    cout << "$ " << priceTot << endl;
	cout << "*" << setw(70) << setfill('*') << "" << endl;
}
// print to new external file, the inventory listing (text version)
void Inventory::printListing ( ingredient inventory[] )
{
    system("cls");
    welcomeMessage();
    int n;
    listCount = readFile();

    cout << "Printing list, Please wait";
    Sleep(3000); // wait for 3 seconds
    // operation on writing data onto new external file
    // the process is the same as displaying the inventory in console
    // but this time it is used to write it on external file
    ofstream write;
    write.open("Inventory_Listing.txt");
    write << "\n\n*********************************" << endl;
    write << "GROUP PROJECT #1" << endl;
    write << "*********************************" << endl;
    write << "Tel: 1-800-*******" << endl;
    write << "Fax : 1-800-*******" << endl;
    write << "Website : http://restaurantmgmt.com/" << endl;
    write << "*********************************" << endl;
    write << "~ Printed Inventory Listing ~" << endl << endl;
    // print out current time and date by using predefined macro names
    write << "Printed on : " << __DATE__ << " " << __TIME__ << endl;
	write << "\n=" << setw(70) << setfill('=') << "" << endl;
	write << "No. " << setw(1) << setfill(' ') << "";
	write << "Item Name" << "\t\t";
	write << "I.C." << "\t";
	write << "Qty" << "\t";
	write << "Cost-per-item";
	write << "\t    Total";
	write << "\n=" << setw(70) << setfill('=') << "" << endl;
    for ( int count = 1; count <= listCount; count++ )
    {
        // this part will output the data calculated
    	write << (count) << "." << setw(3) << setfill(' ') << "";
		write << inventory[count].itemName << "\t\t";
		write << inventory[count].itemcode << "\t";
		write << inventory[count].intrQty << "\t";
		write << "$ " << inventory[count].perPrice;
		write << "\t\t    $ " << inventory[count].total << endl;
    }
    write << "\n=" << setw(70) << setfill('=') << "" << endl;
    write << "      Total : ";
    write << "\t\t\t" << qtyTot << "\t" << "$ " << perPriceTot << "\t\t    ";
    write << "$ " << priceTot << endl;
    write << "=" << setw(70) << setfill('=') << "" << endl;
    write << "\nGroup Project 2014: Chris, Muath and Dhiraj";
    write.close();
    cout << "\n\nList printed! Press any key to open the file.\n";
    cout << "\n# Note: The file is located in the same directory.";
    getch();
    system("start Inventory_Listing.txt");
    // open the file Inventory_Listing.txt located in the same directory as the program
    menuDisplay();
}
// list bar at the top of inventory
void Inventory::bar()
{
	cout << "\n*" << setw(70) << setfill('*') << "" << endl;
	cout << "No. " << setw(1) << setfill(' ') << "";
	cout << "Item Name" << "\t\t";
	cout << "I.C." << "\t";
	cout << "Qty" << "\t";
	cout << "Cost-per-item";
	cout << "\t    Total";
	cout << "\n*" << setw(70) << setfill('*') << "" << endl;
}

// call this function to easy display the inventory
void Inventory::invTempl()
{
	system("cls");
	readFile();
	x = readFile(); // readFile() will return the number of item and save it into x
	welcomeMessage();
	bar();
	printInventory(inventory, x); // x here are used for iteration counter
}
// function for view info inventory feature (part of features)
void Inventory::viewInventory()
{
	invTempl();
	cout << "\n\t Press any key to continue..." << endl;
	getch();
	menuDisplay(); // back to menu()
};
// used for searching for item name
void Inventory::nameSearch()
{
	char searchStr[MAX_CHAR];
	int flag;
    string ans;
	x = readFile();

	do
	{
        system("cls");
        invTempl();
    	cout << endl << endl;
    	cout << "Please Enter the item name (type \"exit\" to cancel): ";
    	cin>>(searchStr);  // user will input any query here

    	// if user entered "exit" this statement will return to main menu
    	if( strncmp( "exit", searchStr, 10 ) == 0 )
    	   menuDisplay();

    	for( int i = 1; i <= x; ++i )
    	{
    		// comparison between query and item name will be calculated here
    		if( strncmp( inventory[i].itemName, searchStr, 100 ) == 0 )
    		{
    			// if it is true then program will display found item
    			cout	<< "\nItem found on item # " << i << " :" << '\n';
    			cout	<< "------------------------------------------------------" << '\n';
    			cout << "Name: " << "\t\t" <<  inventory[i].itemName << '\n';
    			cout << "I.C.: " << "\t\t" <<  inventory[i].itemcode<< '\n';
    			cout << "Quantity: " << '\t' <<  inventory[i].intrQty << '\n';
    			cout << "Per-Price: " << '\t' << "$ " <<  inventory[i].perPrice << '\n';
    			cout << "Total Price: " << '\t' << "$ " <<  inventory[i].total << '\n';
    			cout	<< "------------------------------------------------------" << '\n';
    			cout << " Do you want to search anything else:"<<endl;
    			cin>>ans;
    			if(ans=="yes"||ans=="y")
                    nameSearch();
    			cout << "\nPress any key to continue..." << endl;
    			getch();
    			menuDisplay();
    		}
    	}
    	cout << "\nWe didn't find your item, try again!";
    	flag = 1;
    	getch();
    }while (flag == 1);
    return;
}

// menu for add and remove item (as part of system features)
void Inventory::addRemoveMenu()
{
	int  flag = 0;
	string addRemoveOption;

	do
	{
        system("cls");
        welcomeMessage();

    	cout << "=============" << endl;
    	cout << "ADD / REMOVE" << endl;
        cout << "=============" << endl;
    	cout << "\n[1] Add New Item                             (add)" << endl;
    	cout << "[2] Edit Item                                (edit)" << endl;
    	cout << "[3] Delete Item                              (del)"<< endl << endl;
    	cout << "[0] Back                                     (exit)" << endl;
    	cout << endl;
    	cout << "Choose option : ";
    	cin >> addRemoveOption;
        if (addRemoveOption=="add")
            addNewItem();
        else if (addRemoveOption=="edit")
            addQty();
        else if (addRemoveOption=="del")
           delItem();
        else if (addRemoveOption=="exit")
            menuDisplay();
    	else
    	{
    		errorMsg();
    		getch();
    		flag = 1;
    	}
    }while (flag == 1);
}

// main menu display
void Inventory::menuDisplay()
{
	system("cls");
	welcomeMessage();
	cout << "=========" << endl;
	cout << "MAIN MENU" << endl;
	cout << "=========" << endl << endl;
	cout <<setw(5)<<" View Current Inventory                        (view)" << endl;
	cout <<setw(5)<< " Add / Remove Item                             (modify)" << endl;
	cout <<setw(5)<< " Search by Item Name                           (search)" << endl;
	cout <<setw(5)<< " Print Inventory Listing                       (print)" << endl;
	cout <<setw(5)<< " Logout                                        (exit)" << endl;
	cout << endl;
	cout << "Choose option : ";
	cin >> user; // user will input desire option

    if (user=="exit")
        {
        cout << "\n\nAre you sure to logout? (Y/N)" << endl;
        cin >> exitAns;
        if (exitAns == 'y' || exitAns == 'Y')
            cout<<"Thank you for using this program. Press any key to exit"<<endl;
            return;
        }
    else if (user=="view")
    {
        viewInventory();
    }
    else if (user=="modify")
    {
        addRemoveMenu();
    }
    else if (user=="search")
    {
        nameSearch();
    }
    else if (user=="print")
    {
        printListing(inventory);
    }
    else
    {
        cout<<"Invalid choice"<<endl;
        menuDisplay();
    }
};
// this function will be called if wrong input in the main menu occurs
// function for adding new item in the inventory
void Inventory::addNewItem()
{
	char newItem[MAX_CHAR], iteration = 'y';
	int qtyNew,code;
	float priceNew;
	invTempl();
	while ( iteration == 'Y' || iteration == 'y' )
	{
		x = readFile();
		invTempl();
		cout << "\nEnter the name of item : ";
		cin>>newItem;  // user will input the name of the new item

        cout<<"\nEnter the item code of the item : ";
		cin >> code;

		cout << "\nEnter the quantity of the item : ";
		cin >> qtyNew; // user will input the quantity of the new item

		cout << "\nEnter the price of the item : ";
		cin >> priceNew; // user will input the price of the new item

		// update new struct data
		strcpy(inventory[x+1].itemName, newItem);
		inventory[x+1].itemcode = code;
		inventory[x+1].intrQty = qtyNew;
		inventory[x+1].perPrice = priceNew;

		// open the external file
		ofstream updateFile;
		updateFile.open("inventory.txt");
		x++;
		// this will update the external file
		for ( i = 1; i <= x; i++ )
		{

			updateFile << inventory[i].itemName << ';';
			updateFile << inventory[i].itemcode << ',';
			updateFile << inventory[i].intrQty << ',';
			if ( i < x )
			updateFile << inventory[i].perPrice << '\n';
			else if ( i == x )
			updateFile << inventory[i].perPrice;
		}
		updateFile.close();
		system("cls");
		invTempl();
		cout << "\n\nWould you like to add more? (Y/N)" << endl;
		cin >> iteration;
		cin.ignore(); // flush the buffer
	}
	menuDisplay();
}
// function to add quantity of item in current inventory
void Inventory::addQty()
{
	int itemAdd, howMany, i;
	char newItem[MAX_CHAR], iteration = 'y',input;
	int qtyNew,new_itemcode;
	float priceNew;

back:
	while ( iteration == 'Y' || iteration == 'y')
	{
		x = readFile();
		invTempl();
		cout << "\nEnter the Item code of the itemyou like to edit: ";
		cin >> itemAdd;  // ask user which item they need to add
		cout<<"\nEnter the new IC code: ";
		cin>>new_itemcode;
		cout << "\nHow many would you like to add : ";
		cout << "\n# Use negative integers to remove quantity #" << endl;
		cin >> howMany;  // input the new quantity
		// HINT : use negative number to decrease the quantity
		cout << "\nEnter the new price of the item : ";
		cin >> priceNew;
		ofstream updateFile;
		updateFile.open("inventory.txt");

		// update external file with new quantity value

		for ( i = 1; i <= x; i++ )
		{
		    if(itemAdd==inventory[i].itemcode)
            {
                // update the struct data for quantity

		inventory[i].itemcode =new_itemcode;
		inventory[i].intrQty = (inventory[i].intrQty + howMany);
		inventory[i].perPrice=(priceNew);
	    }
            updateFile << inventory[i].itemName << ';';
			updateFile << inventory[i].itemcode << ',';
			updateFile << inventory[i].intrQty << ',';
			if ( i < x )
			updateFile << inventory[i].perPrice << '\n';
			else if ( i == x )
			updateFile << inventory[i].perPrice;
		}

		updateFile.close();
		system("cls");
		cout<<"After edit"<<endl;
		invTempl();
		cout << "\n\nWould you like to edit more? (Y/N)" << endl;
		cin >> iteration;
	}

	menuDisplay();

}

void Inventory::delItem()
{
    char iteration='y';
    back:
    while ( iteration == 'Y' || iteration == 'y')
	{
        x=readFile();
        invTempl();
        int aaa;
        cout <<"Enter the item code you want to delete." <<endl;
        cin >>aaa;
        //Lets open our file that holds our records (records.txt), if it does not open show error
       	ofstream updateFile;
		updateFile.open("temp.txt"); //temp file that will have our records with out the deleted line
        //Now our file (records.txt) is open lets loop through an find our customer name which was
        //inputted just a ways up.
         //if last name is found delete the whole line
        for ( i = 1; i <= x; i++ )
		{
            if ( ( aaa!=inventory[i].itemcode))
            {
                updateFile << inventory[i].itemName << ";";
                updateFile << inventory[i].itemcode << ",";
                updateFile << inventory[i].intrQty << ",";
                if ( i < x )
                updateFile << inventory[i].perPrice << '\n';
                else if ( i == x )
                updateFile << inventory[i].perPrice;
            }
            else
            {
                cout<<"Item  deleted:"<<endl;
                cout	<< "------------------------------------------------------" << '\n';
                cout << "Name: " << "\t\t" <<  inventory[i].itemName << '\n';
                cout << "I.C.: " << "\t\t" <<  inventory[i].itemcode<< '\n';
                cout << "Quantity: " << '\t' <<  inventory[i].intrQty << '\n';
                cout << "Per-Price: " << '\t' << "$ " <<  inventory[i].perPrice << '\n';
                cout << "Total Price: " << '\t' << "$ " <<  inventory[i].total << '\n';
                cout	<< "------------------------------------------------------" << '\n';
                getch();
            }
		}
        //close our files, because were done!

        updateFile.close();
        // delete the original file
        remove("inventory.txt");
    // rename old to new
        rename("temp.txt","inventory.txt");
        invTempl();
        cout << "\n\nWould you like to delete more? (Y/N)" << endl;
        cin >> iteration;
    }
menuDisplay();
}

#endif
