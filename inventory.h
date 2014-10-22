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
    void errorMsg();
    void menuDisplay();
    void viewInventory();
    void welcomeMessage();
    void invTempl();
    void update_file();
    void sortItem_code(ingredient inventory[]);
    void nameSearch();
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

#endif
