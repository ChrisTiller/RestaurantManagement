#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <limits>
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
    void menu_Display();
    int readFile();
    void viewInventory();
    void welcomeMessage();
    void invTempl();
    void update_file();
    void sortItem_code(ingredient inventory[]);
    void nameSearch();
    void addQty();
    void addNewItem();
    void delItem();
    void printInventory(ingredient inventory[], int);
    void printListing(ingredient inventory[]);
    void help();
private:
    int listCount;
    int in_file;
    double qtyTot;
    double per_Price_Total;
    double priceTot;



};
//FUNCTION DEFINITIONS
// used for header of the program
void Inventory::welcomeMessage(){
	cout << "\n\n\t\t\t ------------------------------" << endl;
	cout << "\t\t\t  CS240 Restaurant MGMT System \n";
	cout << "\t\t\t ------------------------------" << endl;
	cout << endl << endl;
}
// external file reading goes in this function
int Inventory::readFile()
{
	char Name[MAX_CHAR], qty[MAX_CHAR], perPrice[MAX_CHAR],itemcode[MAX_CHAR];
	int i = 1, listCount = 0;
	ifstream read_file;
	read_file.open("inventory.txt");
	if(read_file.fail()) // this part is to check whether the file exist or not
	{
		cout << "\nFile not found." << endl;
		getch();
		menu_Display();  // program will go back to main menu if the file doesn't exist
	}
	//used for skipping the first line of the database file which is a header.
    read_file.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
    // run loop until the end of the file
	while(!read_file.eof())
	{
        // this statement will store information (in char) from external file, for temporarily
		// it will read until character ';' is found
		read_file.getline(Name, MAX_CHAR, ';');
		// it will read until a ',' is found
		read_file.getline(itemcode, MAX_CHAR, ',');
		// it will read until a ',' is found
		read_file.getline(qty, MAX_CHAR, ',');
		// it will read until new line is found
		read_file.getline(perPrice, MAX_CHAR, '\n');
		// this will copy character in stkName into the struct data
		strcpy(inventory[i].itemName, Name);
		// this will convert char to int (qty is char)
		inventory[i].itemcode = atoi(itemcode);
		// this will convert char to int (qty is char)
		inventory[i].intrQty = atoi(qty);
		// this will convert char to floating value (perPrice is char)
		inventory[i].perPrice = atof(perPrice);
		// total calculation goes here
		inventory[i].total = (inventory[i].intrQty * inventory[i].perPrice);
		i++;
		// used for count the number of item in external file
		listCount++;
    }
	read_file.close();
	return listCount;
}

// used for printing the data in class after external file has read
void Inventory::printInventory(ingredient inventory[], int listCount)
{

	for ( int count = 1; count <= listCount; count++ )
	{
		// calculation for total of quantity
		qtyTot = qtyTot + inventory[count].intrQty;
		// calculation for total of price per item
		per_Price_Total = per_Price_Total + inventory[count].perPrice;
		// calculation for total of price total
		priceTot = priceTot + inventory[count].total;
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
	cout << "\t\t\t" << setprecision(0) << qtyTot << "\t" << "$ "<< setprecision(2) << per_Price_Total << "\t";
    cout <<"\t"<< "$ " << priceTot << endl;
	cout << "*" << setw(70) << setfill('*') << "" << endl;

}
// print to new external file, the inventory listing (text version)
void Inventory::printListing ( ingredient inventory[] )
{
    system("cls");
    welcomeMessage();
    listCount = readFile();
    cout << "Printing list, Please wait";
    // wait for 1.5 seconds
    Sleep(1500);
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
    write << "\t\t\t" << qtyTot << "\t" << "$ " << per_Price_Total << "\t\t    ";
    write << "$ " << priceTot << endl;
    write << "=" << setw(70) << setfill('=') << "" << endl;
    write << "\nGroup Project 2014: Chris, Muath and Dhiraj";
    write.close();
    cout << "\n\nList printed! Press any key to open the file.\n";
    cout << "\n# Note: The file is located in the same directory.";
    getch();
    system("start Inventory_Listing.txt");
    // open the file Inventory_Listing.txt located in the same directory as the program
    menu_Display();
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
	// readFile() will return the number of item and save it into in_file
	in_file= readFile();
	welcomeMessage();
	bar();
	// in_file here are used for iteration counter
	printInventory(inventory, in_file);
}
void Inventory::update_file()
{
    ofstream updateFile;
    updateFile.open("inventory.txt");
    updateFile<<"Name;I.C,Qty,price,TP"<<endl;
	for ( int j = 1; j <= in_file; j++ )
		{
		    updateFile << inventory[j].itemName << ';';
			updateFile << inventory[j].itemcode << ',';
			updateFile << inventory[j].intrQty << ',';
			if ( j < in_file )
			updateFile << inventory[j].perPrice << '\n';
			else if ( j == in_file )
			updateFile << inventory[j].perPrice;
		}

		updateFile.close();

}
// sorting itemcode are calculated here
void Inventory::sortItem_code(ingredient inventory[])
{
	in_file= readFile();

	for( int i = 1; i <= in_file; ++i )
	{
		while( inventory[i].itemcode < inventory[i-1].itemcode )
		{
            // swapping the item so that the lowest is at the top
			swap( inventory[i].itemcode, inventory[i-1].itemcode );
			swap( inventory[i].perPrice, inventory[i-1].perPrice );
			swap( inventory[i].itemName, inventory[i-1].itemName );
			swap( inventory[i].intrQty, inventory[i-1].intrQty );
			 // see predefined function above
			--i;
			if( !i )
			break;
		}
	}

	system("cls");
	cout << "Sorted by Itemcode" << endl;
	bar();
	printInventory(inventory, in_file);
	update_file();
	cout << "\n\nPress any key to continue...";
	getch();
	menu_Display();
}

// function for view info inventory feature (part of features)
void Inventory::viewInventory()
{
	invTempl();
	cout << "\n\t Press any key to continue..." << endl;
	getch();
	// back to menu()
	menu_Display();
};
// used for searching for item name
void Inventory::nameSearch()
{
	char searchStr[MAX_CHAR];
	bool flag =true;
    string ans;
	in_file= readFile();
	while (flag == true)
	{
        system("cls");
        invTempl();
    	cout << endl << endl;
    	cout << "Please Enter the item name (type ""exit"" to cancel): ";
    	//user will input any query here
    	cin>>(searchStr);  //
    	// if user entered "exit" this statement will return to main menu
    	if( strncmp( "exit", searchStr, 10 ) == 0 )
        {
            flag=false;
        }
        else
        {
            for( int i = 1; i <= in_file; ++i )
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
                flag=false;
                }
            }
        cout << "\n Please make sure you item name is correct.";
        cout << "\n Press any key to search the item again.";
    	flag = true;
    	getch();
        }
    }
    menu_Display();
    return;
}

// main menu display
void Inventory::menu_Display()
{
    string user_input;
    system("cls");
	welcomeMessage();
	cout << "=========" << endl;
	cout << "MAIN MENU" << endl;
	cout << "=========" << endl << endl;
	cout <<setw(5)<< " View Current Inventory                        (view)" << endl;
	cout <<setw(5)<< " Add / Remove Item                             (add/edit/del)" << endl;
	cout <<setw(5)<< " Search by Item Name                           (search)" << endl;
	cout <<setw(5)<< " Sorting                                       (sort)" << endl;
	cout <<setw(5)<< " Print Inventory Listing                       (print)" << endl;
	cout <<setw(5)<< " Logout                                        (exit)" << endl;
	cout << endl;
	cout << "Command>";

	// user will input desire option
	cin >> user_input;

    if (user_input=="exit")
        {
            return;
        }
    else if (user_input=="view")
    {
        viewInventory();
    }
    else if ((user_input=="add")||(user_input=="edit")||(user_input=="del"))
    {
        if (user_input=="add")
            addNewItem();
        else if (user_input=="edit")
            addQty();
        else if (user_input=="del")
           delItem();
    }
    else if (user_input=="search")
    {
        nameSearch();
    }
    else if (user_input=="sort")
    {
        sortItem_code(inventory);
    }
    else if (user_input=="print")
    {
        printListing(inventory);
    }
    else if (user_input=="help")
    {
        help();
    }
    else
    {
        cout<<"Unknown Command"<<endl;
        cout << "Enter help for a list of commands." << endl;
        Sleep(1500);
        menu_Display();
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
		in_file= readFile();
		invTempl();
		cout << "\nEnter the name of item : ";
		// user will input the name of the new item
		cin>>newItem;

        cout<<"\nEnter the item code of the item : ";
        // user will input the unique code for the new item.
		cin >> code;

		cout << "\nEnter the quantity of the item : ";
		// user will input the quantity of the new item
		cin >> qtyNew;

		cout << "\nEnter the price of the item : ";
		// user will input the price of the new item
		cin >> priceNew;

		// update new struct data
		strcpy(inventory[in_file+1].itemName, newItem);
		inventory[in_file+1].itemcode = code;
		inventory[in_file+1].intrQty = qtyNew;
		inventory[in_file+1].perPrice = priceNew;

		// open the external file
		ofstream updateFile;
		updateFile.open("inventory.txt");
		in_file++;
		// this will update the external file
		update_file();
		system("cls");
		invTempl();
		cout << "\n\nWould you like to add more? (Y/N)" << endl;
		cin >> iteration;
		// flush the buffer
		cin.ignore();
	}
	menu_Display();
}
// function to add quantity of item in current inventory
void Inventory::addQty()
{
	int itemAdd, howMany, i;
	int new_itemcode;
	float priceNew;
	char iteration='y';
    while ( iteration == 'Y' || iteration == 'y')
	{
		in_file= readFile();
		invTempl();
		// ask user which item they need to add
		cout << "\nEnter the Item code of the item you like to edit: ";
		cin >> itemAdd;
		cout<<"\nEnter the new IC code: ";
		cin>>new_itemcode;
		cout << "\nHow many would you like to add : ";
		cout << "\n# Use negative integers to remove quantity #" << endl;
		// input the new quantity
		// HINT : use negative number to decrease the quantity
		cin >> howMany;
		cout << "\nEnter the new price of the item : ";
		cin >> priceNew;
		ofstream updateFile;
		updateFile.open("inventory.txt");

		// update external file with new quantity value
        updateFile<<"Name;I.C,Qty,price,TP"<<endl;
		for ( i = 1; i <= in_file; i++ )
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
			if ( i < in_file )
                updateFile << inventory[i].perPrice << '\n';
			else if ( i == in_file )
                updateFile << inventory[i].perPrice;
		}

		updateFile.close();
		system("cls");
		cout<<"After edit"<<endl;
		invTempl();
		cout << "\n\nWould you like to edit more? (Y/N)" << endl;
		cin >> iteration;
	}

	menu_Display();

}

void Inventory::delItem()
{
    char iteration='y';
   // back:
    while ( iteration == 'Y' || iteration == 'y')
	{
       in_file=readFile();
        invTempl();
        int user_input;
        cout <<"Enter the item code you want to delete." <<endl;
        cin >>user_input;
        //Lets open our file that holds our database (inventory.txt), if it does not open show error
       	ofstream updateFile;
       	//temp file that will have our records with out the deleted line
		updateFile.open("temp.txt");
        //Now our file (incentory.txt) is open lets loop through an find our item code which was inputted just a ways up.
         //if item code is found delete the whole line
         updateFile<<"Name;I.C,Qty,price,TP"<<endl;
        for ( int i = 1; i <=in_file; i++ )
		{
            if ( ( user_input!=inventory[i].itemcode))
            {
                updateFile << inventory[i].itemName << ';';
                updateFile << inventory[i].itemcode << ',';
                updateFile << inventory[i].intrQty << ',';
                if ( i < in_file )
                updateFile << inventory[i].perPrice << '\n';
                else if ( i == in_file )
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
        //close our files after we are done!
        updateFile.close();
        // delete the original file
        remove("inventory.txt");
    // rename old to new
        rename("temp.txt","inventory.txt");
        invTempl();
        cout << "\n\nWould you like to delete more? (Y/N)" << endl;
        cin >> iteration;
    }
menu_Display();
}
void Inventory::help()
    {
        cout << "Type the function you want to do. For eg:"<<endl;
        cout<<"For viewing the inventory list Type view"<<endl;
        cout<<"For printing the inventory list Type print"<<endl;
        cout<<"Also you can access directly with the commands. For eg:"<<endl;
        cout << "add name <space> item code <space> quantity <space>, ..." << endl;
        cout << "remove <item code > " << endl;
        cout << "edit <item code > " << endl;
        cout << "For exiting Please Type exit"<< endl;
        getch();
        menu_Display();
    }

#endif
