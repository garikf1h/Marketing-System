#include "Buyer.h"
#include <string.h>
#include <iostream>
using namespace std;
Buyer::Buyer(const string& userName,const  string& password, const Address& address) : User(userName, password, address)
{
	this->currOrder = nullptr;
}
Buyer::~Buyer()
{
	delete currOrder;
}

const Cart & Buyer::getCart()const 
{
	return this->cart;
}
const list<Seller*>& Buyer ::getAllSellerHistory() const
{
	return sellerHistory;
}

bool Buyer::addProductToCart(const Product& productToAdd) 
{
	cart.addToCart(productToAdd);
	return true;
}


void Buyer::makePayment()
{
	list<const Product*>::const_iterator begin = this->currOrder->getAllOrderProducts().begin();
	list<const Product*>::const_iterator end = this->currOrder->getAllOrderProducts().end();


	for ( ;begin!=end; ++begin)
	{
		 Seller &seller = (*begin)->getSeller();
		if (!ifSellerExists(seller))
			sellerHistory.push_back(&seller);
	}
	delete []this->currOrder;
	this->currOrder = nullptr;
}

bool Buyer:: ifSellerExists(const Seller& seller)
{
	list<Seller*>::iterator begin = sellerHistory.begin();
	list<Seller*>::iterator end = sellerHistory.end();
	for (;begin!=end;++begin)
	{
		if (*begin == &seller)
			return true;
	}
	return false;
}


void Buyer::show(int ind) const
{
	if(strcmp(typeid(*this).name() + 6,"BuyerSeller")!=0 || ind)//no option to dynamic cast no declration of buyerSeller class
		User::show();

	cout << " And has " << this->cart.getAllProducts().size() << " products in cart " << endl;
}
const Product* Buyer::returnProductInCartById(int id,bool &isFound) const
{
	return cart.returnProductById(id, isFound);
}
void Buyer::addProductToOrder(const Product& productToAdd)
{
	if (this->currOrder == nullptr)
		this->currOrder = new Order[1];
	this->currOrder->addProduct(productToAdd);
	
	this->cart.deleteProduct(productToAdd);
}
void Buyer::showCart() const
{
	this->cart.show();
}
void Buyer::showOrder() const
{
	cout << *this->currOrder;
}
void Buyer::productToOrderFromCart(int id, bool&isFound) 
{
	
	const Product* productToAddToOrder = this->returnProductInCartById(id, isFound);
	if (isFound)
		this->addProductToOrder(*productToAddToOrder);

}
bool Buyer::checkIfEmptyCart() const 
{
	return cart.checkIfEmpty();
}
bool Buyer::isOrderNull() const
{
	return (this->currOrder == nullptr);
}

bool Buyer::operator>(const Buyer & other) const
{
	return (this->cart.getTotalPrice() > other.cart.getTotalPrice());
}
