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
#include "Assignment2Header.h"



using namespace std;


void pause() {
	long count = 0;
	while (isspace(cin.peek()) && count != 30000000) {
		count++;
	}
}

//INVENTORY ITEM CLASS DEFINITIONS

//ACCESSORS AND MUTATORS
InventoryItem::~InventoryItem() {
	cout << "InventoryItem " << name_ << " with " << quantity_ << " items " << " destroyed" << endl; 
}
void InventoryItem::set_name(string name)
{
	name_ = name;
}

string InventoryItem::get_name() const {
	return name_;
}
void InventoryItem::set_quantity(int quantity) {
	quantity_ = quantity;
}
int InventoryItem::get_quantity() const {
	return quantity_;
}
//OTHERS
void InventoryItem::Display() const {
	cout << "Name: " << setw(30)<< name_ << "    Quantity:" << setw(10) << quantity_ << endl ;
}

//PRODUCT CLASS DEFINITIONS


Product::~Product() {
	cout << "Product " << product_id_ << " priced " << product_price_ << " destroyed" << endl; 
}

//ACCESSORS AND MUTATORS
void Product::set_condition(char condition) {
	product_condition_ = condition;
}
char Product::get_condition_char() const {
	return product_condition_;
}
void Product::set_product_id(int ID) {
	product_id_= ID;
}
int Product::get_product_id() const {
	return product_id_;
}
void Product::set_price(float price) {
	product_price_=price;
}
float Product::get_price() const {
	return product_price_;
}
//OTHERS
void Product::Display() const {
	InventoryItem::Display();
	cout << "Product ID :" << setw(20)<< product_id_ <<  "      Price " << setw(10) << fixed << setprecision(2) << product_price_<< "    Condition" << setw(10)<< translate_condition(define_condition(product_condition_)) << endl;
}


//INVENTORY SYSTEM DEFINITIONS
//INVENTORY MANAGEMENT
InventorySystem::~InventorySystem(){
	delete [] ItemList; 
	//delete my_prod; 
}
void InventorySystem::BuildInventory() {
	string temp_string, name, condition;
	char final_condition;
	float price;
	int quantity;
ifstream fin;
fin.open("products.txt");
cout << "FILE OPENED" << endl;
while (getline(fin, temp_string, ';')) {
	name = "";
	quantity = 0;
	price = 0.00;
	//condition = "";
	name = temp_string;              // just read first name and last name into buffer

	getline(fin, temp_string, ';');         // just read student ID into buffer
	quantity = atoi(temp_string.c_str());   // c_str ( ) function returns a pointer to char
								 // atoi converts a char array to an integer

	getline(fin, temp_string, ';');       // delimeter is '\n' now - must use \n as this is the last field in the record
	price = atof(temp_string.c_str());   // c_str ( ) function returns a pointer to char
								  // atof converts a char array to a floating point value
	getline(fin, temp_string, '\n');       // delimeter is '\n' now - must use \n as this is the last field in the record
	condition = temp_string.c_str();
	for (int i = 0; i < condition.length(); i++) {
		if (condition[i] != ' ') {
			final_condition = condition[i];
		}
	}
	
	//cout << name << "\t" << quantity << "\t" << price << "\t" << condition << endl;
	//cout << item_count_;
	Product *myprod = new Product(name, quantity, price, final_condition);
	ItemList[item_count_] = myprod;
	item_count_++; 
}

fin.close();

}



void InventorySystem::ShowInventory() {
	InventoryItem * inv_ptr;
	for (int i = 0; i < 512; i++) {
		inv_ptr = ItemList[i];
		Product * prod_ptr = static_cast<Product *>(inv_ptr);
		if (prod_ptr != NULL) {
			prod_ptr->Display();
		}
	}
	delete inv_ptr;
}


void InventorySystem::ShowDefectiveInventory() {
	InventoryItem * inv_ptr;
	for (int i = 0; i < 512; i++) {
		inv_ptr = ItemList[i];
		Product * prod_ptr = static_cast<Product *>(inv_ptr);
		if (prod_ptr != NULL) {
			if ((prod_ptr->get_condition_char() == 'D')) {
				prod_ptr->Display();
			}
		}
	}
	delete inv_ptr;
}


void InventorySystem::Terminate() {
	InventoryItem * inv_ptr;
	inv_ptr = ItemList[0];
	Product * prod_ptr = static_cast<Product *>(inv_ptr);
	ofstream myfile("output.txt", ofstream::out);
	cout << "In the Terminate" << endl;
	for (int i= 0; i < 512; i++) {
		inv_ptr = ItemList[i];
		if (inv_ptr != NULL) {
			Product * prod_ptr = static_cast<Product *>(inv_ptr);
			myfile << prod_ptr->get_name() << ";" << prod_ptr->get_quantity() << ";" << prod_ptr->get_price() << ";" << prod_ptr->get_condition_char() << endl;
		}
	}
	delete inv_ptr;
	cout << "Out of the Terminate" << endl;
}


//ACCESSORS AND MUTATORS
void InventorySystem::set_store_name(string name) {
	store_name_ = name;
}
string InventorySystem::get_store_name() const {
	return store_name_;
}
void InventorySystem::set_store_ID(int ID) {
	store_ID_ = ID;
}
int InventorySystem::get_store_ID() const {
	return store_ID_;
}
void InventorySystem::set_item_count(int count) {
	item_count_ = count;
}
int InventorySystem::get_item_count() const {
	return item_count_;
}

int main() {
	InventorySystem * sys_ptr = new InventorySystem("Mort Mart", 2266);
	sys_ptr->BuildInventory();
	cout << "Built Inventory" << endl;
	sys_ptr->ShowInventory();
	cout << "Showed Inventory" << endl;
	sys_ptr->ShowDefectiveInventory();
	cout << "Showed Defective Inventory" << endl;
	sys_ptr->Terminate();
	pause();

};
