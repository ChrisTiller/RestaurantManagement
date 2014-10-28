#include<iostream>
#include"menu.h"
#include"orders.h"
using namespace std;

void mainMenu()
{
	cout<<"Press 1 for Cashier\n";
	cout<<"Press 2 for Admin\n";
}
void restaturantMenuConfigurationsMenu()
{
	cout<<"Press 1 to Add New Menu Item\n";
	cout<<"Press 2 to Display All Menu Items\n";
	cout<<"Press 3 to Delete A Menu Item\n";
	cout<<"Press 4 to Modify a Menu Item\n";
	cout<<"Any other key to exit\n";
}

int main()
{

	menuItems *mi=new menuItems();
	menuItems *miLoadData=new menuItems();
	orderItems *oi=new orderItems();


	mi->loadDataFromTextFile();

	int choice,id,qty;
	id=-1;
	float price;
	while(1)
	{
		mainMenu();
		cin>>choice;
		switch(choice)
		{
		case 1:

			mi->displayMenuItems();
			char name[50] ;
			while(id!=0)
			{

				cout<<"\n\nEnter Item ID to add to the order (Enter 0 to Finish) : ";
				cin>>id;
				if(id==0)
				{
					oi->displayMenuItems();
					//display order details
					exit(1);
				}
				strcpy(name,mi->getItemName(id));
				price=mi->getItemPrice(id);
				cout<<"\n\nEnter Quantity: ";
				cin>>qty;
				oi->addItem(id,name,price,qty);
				miLoadData->loadDataFromTextFile();
			}
			break;
		case 2:
			restaturantMenuConfigurationsMenu();
			cin>>choice;
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
					continue;
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
					continue;
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
				exit(1);
				break;
			}
			break;
		default:
			cout<<"Invalid Input. Exiting...\n";
			exit(1);
			break;
		}
	}



    return 0;

}
