#ifndef _P_H
#define _P_H

#include <iostream>
using namespace std;

class Seller;

class Product
{
public:
	enum eCategory { Children, Electronic, Office, Clothes };
private:
	static int counter;
	int id;
	string name;
	double price;
	Seller& seller;
	eCategory category;
	const Product& operator=(const Product& other);

public:
	Product(const Product&cpy) = delete;
	Product(const string& name, double price, eCategory category,Seller& seller);
	~Product();
	eCategory getCategory() const;
	double getPrice() const;
	Seller&getSeller() const;
	int getId() const;
	const string& getName() const;
	bool setPrice(double newPrice);
	bool setCategory(Product::eCategory newCategory);
	friend ostream& operator<<(ostream&os, const Product&other);
};

#endif // !_P_H
