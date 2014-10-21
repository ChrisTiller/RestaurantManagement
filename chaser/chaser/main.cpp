///Users/moathaldhubayb/Desktop/new project/chaser/chaser/Oreders.h
//  main.cpp
//  chaser

#include<iostream>
#include"menu.h"
#include"Oreders.h"
using namespace std;

int mainMenu()
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
    mainMenu();
    int choice,id,qty;
    float price;
    cin>>choice;
    switch(choice)
    {
        case 1:
            orderItems *oi=new orderItems();
            mi->displayMenuItems();
            char name[50] ;
            while(id!=0)
            {
                cout<<"\n\nEnter Item ID to add to the order (Enter 0 to Finish) : ";
                cin>>id;
                if(id==0)
                {
                    //display order details
                    exit(1);
                }
                strcpy(name,mi->getItemName(id));
                price=mi->getItemPrice(id);
                cout<<"\n\nEnter Quantity: ";
                cin>>qty;
                oi->addItem(id,name,price,qty);
            }
            break;
        case 2:
        
            restaturantMenuConfigurationsMenu();
         break;
        
        default:
          cout<<"Invalid Input. Exiting...\n";
            exit(1);
            break;
        
    }
    
    mi->loadDataFromTextFile();
    mi->addMenuItem("burg",50);
    mi->addMenuItem("ham",10);
    mi->addMenuItem("---",30);
    mi->displayMenuItems();
    mi->deleteMenuItem(2);
    mi->displayMenuItems();
    
}