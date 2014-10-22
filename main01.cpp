#include<iostream>
#include"menu.h"
using namespace std;

void main()
{
	menuItems *mi=new menuItems();
	mi->loadDataFromTextFile();
	mi->addMenuItem("pizz",50);
	mi->addMenuItem("Pizz",10);
	mi->addMenuItem("ham",30);
	mi->displayMenuItems();
	mi->deleteMenuItem(2);
	mi->displayMenuItems();
	
}