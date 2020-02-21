
#include "Address.h"
#include <iostream>
using namespace std;

Address::Address(int houseNum, const string& country, const string& city, const string& street)
{
	this->setCountry(country);
	this->setCity(city);
	this->setStreet(street);
	this->setHouseNumber(houseNum);
}

const string& Address::getCity() const {
	return this->city;
}
const string& Address::getCountry() const {
	return this->country;
}
const string& Address::getStreet() const {
	return this->street;
}
int Address::getHouseNumber()const {
	return this->houseNumber;
}
void Address::setHouseNumber(int newHouseNum)
{
	this->houseNumber = newHouseNum;
}
bool Address::setCountry(const string& newCountry)
{
	if (isValidString(newCountry))
	{
		this->country = newCountry;
		return true;
	}
	return false;
}
bool Address::setCity(const string& newCity)
{
	if (isValidString(newCity))
	{
		this->city = newCity;
		return true;
	}
	return false;

}
bool Address::setStreet(const string& newStreet)
{
	if (isValidString(newStreet))
	{
		this->street = newStreet;
		return true;
	}
	return false;
}
void Address:: show() const
{
	cout << " Country: " << this->country << " City: " << this->city << " Street: " << this->street << " " << this->houseNumber;
}

bool isValidString(const string& str)
{
	
 	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
			return false;
	}
	return true;
}
ostream&operator<<(ostream&os, const Address&other)
{
	os << other.country << " " << other.city << " " << other.street << " " << other.houseNumber;
	return os;
}
istream&operator>>(istream&in, Address&other)
{
	in >> other.country >> other.city >>other.street >> other.houseNumber;
	return in;
}