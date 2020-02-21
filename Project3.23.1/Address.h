#pragma warning (disable:4996)

#ifndef _A_H
#define _A_H
#include <string>
using namespace std;

class Address
{
private:
	string country;
	string city;
	string street;
	int houseNumber;

public:

	Address(int houseNum, const string& country, const string& city, const string& street);

	const string& getCity() const;
	const string& getCountry() const;
	const string& getStreet() const;
	int getHouseNumber() const;
	void setHouseNumber(int newHouseNum);
	bool setCountry(const string& newCountry);
	bool setCity(const string& newCity);
	bool setStreet(const string& newStreet);
	void show() const;
	friend bool isValidString(const string& name);
	friend ostream&operator<<(ostream&os, const Address&other);
	friend istream&operator>>(istream&in, Address&other);
	friend class Buyer;
	friend class Seller;

};



#endif // !1
