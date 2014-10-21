//
//  Oreders.h
//  chaser


#ifndef chaser_Oreders_h
#define chaser_Oreders_h
//#ifndef ORDERS_H
//#define ORDERS
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

struct item
{
    int id;
    char name[50];
    int price;
    int quantity;
    item *next;
};

class orderItems
{
private:
    item *head,*tail;
public:
    orderItems()
    {
        head=NULL;
        tail = NULL;
    }
    void addItem(int id, char itemName[50], float price, int qty)
    {
        item *newItem=new item();
        newItem->id=id;
        strcpy(newItem->name,itemName);
        newItem->price=price;
        newItem->quantity=qty;
        if(head==NULL)
        {
            head = newItem;
            tail = newItem;
            tail->next=NULL;
        }
        else
        {
            tail->next = newItem;
            tail = newItem;
            tail->next=NULL;
        }
    }
    void displayMenuItems()
    {
        item *temp=head;
        cout<<"Name\tPrice"<<endl;
        cout<<"----\t-----"<<endl;
        while(temp !=NULL)
        {
            cout<<temp->name<<"\t"<<temp->price<<endl;
            temp=temp->next;
        }
    }
    
    
};



#endif
