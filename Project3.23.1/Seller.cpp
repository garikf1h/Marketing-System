#include "Seller.h"
#include <string.h>

#include "Buyer.h"

Seller::Seller(const string& userName,const string& password,const Address& address) : User(userName,password,address)
{

}
Seller::~Seller()
{
	for (int i = 0; i < feedbacksArr.getLogSize(); i++)
	{
		delete feedbacksArr[i];
	}
	list<const Product*>::const_iterator begin = productsList.begin();
	list<const Product*>::const_iterator end = productsList.end();
	for ( ;begin!=end; ++begin )
	{
		delete *begin;
	}
}
const list<const Product*>& Seller::getProduct() const
{
	return this->productsList;
}
void Seller:: addFeedbackToArr(const Buyer&buyer, string& feedback, int day, int month, int year)
{
	const Feedback* newFeedback = new const Feedback(buyer, feedback, Date(day, month, year));
	feedbacksArr+= newFeedback;
}


void Seller::addProduct(const string& nameOfProduct, double price, int category)
{
	productsList.push_back(new Product(nameOfProduct, price, (Product::eCategory)category, *this));
}
void Seller::show() const
{
	User::show();
	cout << " And has " << this->feedbacksArr.getLogSize() << " feedbacks" << endl;
}
void Seller::searchProductByName(const string& name,bool &isFound) const
{

	list<const Product*>::const_iterator begin = productsList.begin();
	list<const Product*>::const_iterator end = productsList.end();

	for (; begin!=end; ++begin)
	{
		if ((*begin)->getName() == name)
		{
			cout << **begin;
			isFound = true;
		}
	}

}
const Product* Seller::searchProductById(int id, bool& isFound) const
{
	list<const Product*>::const_iterator begin = productsList.begin();
	list<const Product*>::const_iterator end = productsList.end();

	for (; begin != end && !isFound; ++begin)
	{
		if ((*begin)->getId() == id)
		{
			isFound = true;
			return *begin;
		}
	}
	return nullptr;
}
