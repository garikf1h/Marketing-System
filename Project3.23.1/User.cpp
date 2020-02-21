#include "User.h"

User::User(const string& userName, const string& password, const Address& address): address(address), userName(userName), password(password)
{
}

User::~User()
{
}

const string& User::getUserName() const
{
	return this->userName;
}

const string& User::getPassword() const
{
	return this->password;
}

const Address & User::getAddress() const
{
	return this->address;
}

bool User::setAddress(const Address & newAddress)
{
	this->address = newAddress;
	return true;
}
ostream & operator<<(ostream & os, const User & other)
{

		os << other.userName << " " << other.password << " "<< other.address;
	

	return os;
}

istream&operator>>(istream&in, User&other)
{
	in >> other.userName >> other.password >>  other.address;
	return in;
}

void User::show() const
{
	cout << "User name: " << this->userName << " ";
	address.show();
}
