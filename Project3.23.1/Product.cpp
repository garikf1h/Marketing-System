#include "Product.h"
#include <string>
#include <iostream>
#include "Seller.h"

using namespace std;
int Product::counter = 0;
Product::Product(const string& name, double price, Product::eCategory category,Seller& seller):seller(seller)
{
	this->name = name;
	this->setPrice(price);
	this->setCategory(category);
	this->id = ++counter;
}
Product::~Product() {
	
}
Product::eCategory Product::getCategory() const {
	return category;
}

double Product:: getPrice() const
{
	return this->price;
}
Seller& Product::getSeller() const
{
	return this->seller;
}
int Product::getId() const
{
	return this->id;
}
const string& Product::getName() const
{
	return this->name;
}
bool Product::setPrice(double newPrice)
{
	if (newPrice <= 0)
		return false;
	this->price = newPrice;
	return true;
}
bool Product::setCategory(Product::eCategory newCategory)
{
	if (newCategory >= 1 && newCategory <= 4)
	{
		this->category = newCategory;
		return true;
	}
	return false;
}


ostream & operator<<(ostream & os, const Product & other)
{
	os << "Product id: " << other.getId() << " product name: " << other.getName() << ", price: " << other.getPrice() << ", the seller is: " << other.getSeller().getUserName() << endl;
	return os;

}
