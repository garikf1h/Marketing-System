#pragma warning (disable:4996)

#ifndef IO_H
#define IO_H

#include <iostream>
#include "System.h"
#include <string>
using namespace std;

class IOcontroller
{
private:
	
	System theSystem;
	const IOcontroller& operator=(const IOcontroller& other);

	static constexpr int DELAY = 1500;
	void printMenuAll(const string& name) const;
	void addBuyerOrSellerMenu(const string& whoToAdd);
	void addItemToSellerMenu();
	void addFeedbackToSellerMenu();
	friend void getCurrentDate(int &year, int&month, int& day) ;
	void showAllBuyersSellerDetailsMenu( const string& whoToPrint) ;
	void showAllDetailsOfProductByNameMenu()const;
	void addToCartMenu();
	void makeOrderMenu();
	void makePaymentMenu();
	const string getFeedbackFromUserInput() const;
	void getIdInputToOrder(list<User*>::iterator* itrB, bool& isFound, const string& userName);
	void checkOperators();
	void getUserDetails (const string& whoToAdd, string& name, string& password, string& city, string& street, string& country, int& houseNumber) const;
	void addFeedbackIfvalidSeller(list<User*>::iterator itrB, const string& buyer, const string& seller, list<User*>::iterator itrS, int& ind);
	static void cinFail()
	{
		cout << "Wrong input for number .Please try again" << endl;
		cin.clear();
		IOcontroller::clearBuffer();
		_sleep((IOcontroller::DELAY));
	}
	static void clearBuffer()
	{
		cin.seekg(0, ios::end);
		cin.clear();
	}

public:
	IOcontroller(const string& name);
	IOcontroller(const IOcontroller&cpy)=delete;

	void run();
};
#endif // !IO_H
