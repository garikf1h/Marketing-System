#ifndef U_H_
#define U_H_
#include "Address.h"
//abstract class cant make only user this will be a father of other classes
#include <iostream>
#include <fstream>

using namespace std;
class User {
protected:
	string userName;
	string password;
	Address address;
	User(const string& userName, const  string& password, const Address& address);
	

public:
	virtual ~User();
	const string& getUserName()const;
	const string& getPassword()const;
	const Address &getAddress()const;
	bool setAddress(const Address &newAddress);
	void show() const;
	friend ostream& operator<<(ostream&os, const User&other);
	friend istream&operator>>(istream&in, User&other);
};

#endif // !U_H_
