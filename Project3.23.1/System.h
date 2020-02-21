#pragma warning (disable:4996)

#ifndef _SY_H
#define _SY_H

#include <list>
#include <iterator>
#include "BuyerSeller.h"
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;
class System
{
private:
	string name;
	list<User*>usersList;
	int numOfBuyers;
	int numOfSellers;
	int numOfBuyersSellers;
	const System& operator=(const System& other);
	void saveToFile();

public:
	System(const string &name);
	System(const System& cpy) = delete;
	~System();
	const string& getName() const;
	bool ifUserExists(const string& username, const type_info* t, list<User*>::const_iterator* itr = nullptr) const;
	bool ifBuyerBoughtFromSeller(list<User*>::const_iterator& itrB, string& usernameOfSeller, list<User*>::const_iterator& itrS) const;
	void addProductToSeller(list<User*>::iterator* itr, const string&nameOfProduct, double price, int category);
	void addFeedbackToSeller(list<User*>::iterator* itrS, list<User*>::iterator* itrB, string& feedback, int day, int month, int year);
	void AddSeller(Seller& newSeller);
	void AddBuyer(Buyer& newBuyer);
	void showAllBuyers() ;
	void showAllSellers() ;
	void showAllBuyerSeller() ;
	void searchProductName(const string& pName, bool& isFound) const;
	void addProductById(int id, bool& isFound, list<User*>::iterator* itr);
	bool showCartByBuyer(list<User*>::iterator* itr) const;
	bool addProductToOrderInBuyer(list<User*>::iterator* itr, int id, bool&isFound);
	bool showOrderByBuyer(list<User*>::iterator* itr) const;
	bool makePaymentByBuyer(list<User*>::iterator* itr);
	bool checkIfEmptyCartOfIndexBuyer(list<User*>::iterator* itr) const;
	bool isBuyerOfSellerArrayEmpty(const string& whoToCheck) const;
	bool isOrderNullInBuyer(list<User*>::iterator* itr) const;
	void AddBuyerSeller(const string& name, const string& password, const string& country, const string& city, const string&street, int houseNumber);
	void operator+=(Buyer& newBuyer);
	void operator+=(Seller& newSeller);
	bool checkCarts(list<User*>::iterator* itr1, list<User*>::iterator* itr2);
	void loadFromFile();
	void readFieldsFromFile(ifstream &inFile, string&type, string&username, string&password, string&country, string&city, string &street, int&housenum);


};
 // !S_H

#endif // !_SY_H
