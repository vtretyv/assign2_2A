#pragma once
#pragma once
/*Name: Vladimir Tretyakov
Student ID : 20082073
Date : 2/ 1 / 2017
Class : CS2B
Assignment : 2
Project Purpose : Use 2 classes to make an online inventory manager
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>


typedef  enum { pcNew, pcUsed, pcRefurbished, pcDefective } T_ProductCondition;

using namespace std;

const int g_kSize = 8;


int generateProductID() {
	int id = 0;
	id = rand() % 10000;      // generate a number between 0-9999
	return id;
}
T_ProductCondition define_condition(char condition) {
	switch (condition) {
	case 'N':
		return pcNew;
		break;
	case  'U':
		return pcUsed;
		break;
	case 'R':
		return pcRefurbished;
		break;
	case  'D':
		return pcDefective;
		break;
	}
}
string translate_condition(T_ProductCondition mycon) {
	switch (mycon) {
	case pcNew:
		return "New";
		break;
	case  pcUsed:
		return "Used";
		break;
	case pcRefurbished:
		return "Refurbished";
		break;
	case  pcDefective:
		return "Defective";
		break;
	}
}

class InventoryItem {
protected:
	//Variables
	string name_;
	int quantity_;
public:
	//Construct & Dstruct
	InventoryItem() : name_(""), quantity_(0)  { cout << "InventoryItem Created" << endl; }
	InventoryItem(string name, int quantity) : name_(name), quantity_(quantity) { cout << "InventoryItem Created" << endl; }
	virtual ~InventoryItem(); 

	//Accessors and Mutators
	void set_name(string name);
	string get_name() const;

	void set_quantity(int quantity);
	int get_quantity() const;

	//Others
	virtual void Display() const;
};
class Product : public InventoryItem {
private:
	//Variables
	T_ProductCondition condition_;
	char product_condition_;
	int product_id_;
	float  product_price_;

public:
	//Construct & Dstruct
	Product() : product_id_(generateProductID()), product_price_(0.0) {}
	Product(string name, int quantity, float price, char condition ) : /*name_(name), quantity_(quantity),*/ InventoryItem(name, quantity), product_price_(price), product_condition_(condition), condition_(define_condition(condition)), product_id_(generateProductID()) { cout << "Product Constructed" << endl; }
	virtual ~Product();

	//Accessors and Mutators
	void set_condition(char condition);
	char get_condition_char() const;

	void set_product_id(int ID);
	int get_product_id() const;

	void set_price(float price);
	float get_price() const;

	//other functions
	virtual void Display() const;

};


class InventorySystem {
private:
	//class variables
	string store_name_;
	int store_ID_, item_count_;
	InventoryItem * ItemList[512];

public:
	//Constructors & Dstructors
	InventorySystem() : store_ID_(0), item_count_(0), ItemList() { cout << "Inventory Created" << endl; srand(time(NULL)); }
	InventorySystem(string name, int ID) : store_name_(name), store_ID_(ID), item_count_(0), ItemList() { cout << "Inventory Created" << endl; srand(time(NULL));}
	~InventorySystem();

	//Inventory Access
	 void BuildInventory();
	 void ShowInventory();
	 void ShowDefectiveInventory();
	 void Terminate();

	 //Muttators and Accessors
	 void set_store_name(string name);
	 string get_store_name() const;



	 void set_store_ID(int ID);
	 int get_store_ID() const;

	 void  set_item_count(int count);
	 int get_item_count() const;



};


