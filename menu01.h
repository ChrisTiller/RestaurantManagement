#ifndef MENU_H
#define MENU
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

struct item
{
	int id;
	char name[50];
	int price;
	item *next;
};

class menuItems
{
private:
	item *head,*tail;
public:
	menuItems()
	{
		head=NULL;
		tail = NULL;
	}
	void addMenuItem(char itemName[50], float price)
	{
		int itemsCount=0;
		char line[1000];
		char dataFilePath[1000]="menu.txt"; 
		fstream readWrite;
		readWrite.open(dataFilePath,ios::in);
		if (readWrite.is_open())
		{
			while(!readWrite.eof())
			{
				readWrite.getline(line,1000,'\n');
				itemsCount++;
			}
			readWrite.close();
			readWrite.open(dataFilePath,ios::app);
			readWrite<<itemsCount<<"/"<<itemName<<"/"<<price<<"\n";
			readWrite.close();
		}
		else
		{
			//Error Opening File
		}
	}
	void displayMenuItems()
	{		
		item *temp=head;
		cout<<"ID\tName\tPrice"<<endl;
		cout<<"--\t----\t-----"<<endl;
		while(temp !=NULL)
		{
			cout<<temp->id<<"\t"<<temp->name<<"\t"<<temp->price<<endl;
			temp=temp->next;
		}
	}
	bool deleteMenuItem(int id)
	{
		if(searchMenuItem(id))
		{
			item *temp,*previous;
			if(head->id==id)
			{
				temp=head->next;
				delete head;
				head=temp;
				writeDataToTextFile();
				return true;
			}
			else
			{
				temp=head;
				while(temp !=NULL)
				{
					if(temp->id==id)
					{
						previous->next=temp->next;
						delete temp;
						writeDataToTextFile();
						return true;
					}
					previous=temp;
					temp=temp->next;
				}
			}
		}
		return false;
	}
	void writeDataToTextFile()
	{
		char dataFilePath[1000]="menu.txt"; 
		fstream readWrite;
		readWrite.open(dataFilePath,ios::out);
		item *temp=head;
		while(temp !=NULL)
		{
			readWrite<<temp->id<<"/"<<temp->name<<"/"<<temp->price<<"\n";
			temp=temp->next;
		}
		readWrite.close();
	}
	void loadDataFromTextFile()
	{
		menuItems();
		int itemsCount=0;
		char line[1000];
		char dataFilePath[1000]="menu.txt"; 
		fstream readWrite;
		readWrite.open(dataFilePath,ios::in);
		if (readWrite.is_open())
		{
			while(!readWrite.eof())
			{
				readWrite.getline(line,1000,'\n');
				int l=strlen(line);
				if(l==0)
					break;
				item *newItem=new item();
				newItem->id=atoi(strtok(line,"/"));
				strcpy(newItem->name,strtok(NULL,"/"));
				newItem->price=atoi(strtok(NULL,"/n"));
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
		}
		else
		{
			//Error Opening File
		}
	}
	bool searchMenuItem(int id)
	{
		item *temp=head;
		while(temp !=NULL)
		{
			if(temp->id==id)
				return true;
			temp=temp->next;
		}
		return false;
	}
};



#endif