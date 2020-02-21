
#include <iostream>
#include "Order.h"
using namespace std;
Order::Order()
{
	this->totalCost = 0;


}
Order:: ~Order()
{
}

void Order::addProduct(const Product& newProduct)
{
	productsList.push_back(&newProduct);
	totalCost += newProduct.getPrice();
}
const list<const Product*>& Order::getAllOrderProducts() const 
{
	return this->productsList;
}

double Order::getTotalCost() const
{
	return this->totalCost;
}

ostream & operator<<(ostream & os, const Order & other)
{
	list<const Product*>::const_iterator begin = other.productsList.begin();
	list<const Product*>::const_iterator end = other.productsList.end();
	for (; begin!=end; ++begin)
	{
		os << **begin;
	}

	os << "The total cost of the order is: " << other.getTotalCost() << endl;
	return os;
}
