#ifndef ORDERS_H
#define ORDERS
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

struct orderItem
{
	int id;
	char name[50];
	int price;
	int quantity;
	orderItem *next;
};

class orderItems
{
private:
	orderItem *head,*tail;
public:
	orderItems()
	{
		head=NULL;
		tail = NULL;
	}
	void addItem(int id, char itemName[50], float price, int qty)
	{
		orderItem *newItem=new orderItem();
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
		float orderTotal=0;
		float lineTotal=0;
		orderItem *temp=head;
		cout<<"Name\tPrice\tQty.\tLine Total"<<endl;
		cout<<"----\t-----\t----\t----------"<<endl;
		while(temp !=NULL)
		{
			lineTotal=temp->price*temp->quantity;
			cout<<temp->name<<"\t"<<temp->price<<"\t"<<temp->quantity<<"\t"<<lineTotal<<endl;
			orderTotal += lineTotal;
			temp=temp->next;
		}
		cout<<"\nTotal Amount Payable: "<<orderTotal<<endl<<endl;
	}

};



#endif
