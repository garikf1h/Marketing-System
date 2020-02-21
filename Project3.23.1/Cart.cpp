
#include "Cart.h"

Cart::Cart()
{
	this->totalPrice = 0;
}
Cart::~Cart()
{
}
void Cart::addToCart(const Product&productToAdd)
{

	this->productsArray.push_back(&productToAdd);
	this->totalPrice += productToAdd.getPrice();
}




const list<const Product*>& Cart::getAllProducts() const
{
	return productsArray;
}

void Cart::show() const
{
	list<const Product*>::const_iterator begin = productsArray.begin();
	list<const Product*>::const_iterator end = productsArray.end();
	for (; begin != end ; ++begin)
	{
		cout << **begin;
	}
}

void Cart::deleteProduct(const Product&productToDelete)
{
	list <const Product*>::const_iterator begin = productsArray.begin();
	list <const Product*>::const_iterator end = productsArray.end();
	for (; begin != end; ++begin)
	{
		if (*begin == &productToDelete)
		{
			productsArray.erase(begin);
			break;
		}
	}
	
}
const Product* Cart::returnProductById(int id,bool& isFound) const
{
	list <const Product*>::const_iterator begin = productsArray.begin();
	list <const Product*>::const_iterator end = productsArray.end();
	for (; begin!=end; ++begin)
	{
		if ((*begin)->getId() == id)
		{
			isFound = true;
			return *begin;
		}
	}
	return nullptr;
}
bool Cart::checkIfEmpty() const
{
	return productsArray.empty();
}

double Cart::getTotalPrice() const
{
	return this->totalPrice;
}
