#ifndef _SE_H
#define _SE_H

#include "Array.h"
#include <list>
#include <iterator>
#include "User.h"
using namespace std;
class Product;
class Feedback;

class Seller :virtual public User
{

private:
	Array<const Feedback*>feedbacksArr;
	list<const Product*>productsList;
	const Seller& operator=(const Seller& other);

public:
	Seller(const string& userName,const string& password, const Address& myAddress);
	Seller(const Seller& cpy) = delete;
	virtual ~Seller();
	const list<const Product*>& getProduct() const;
	void addFeedbackToArr(const Buyer&buyer, string& feedback, int day, int month, int year);
	 void show()const;
	void addProduct(const string& nameOfProduct, double price, int category);
	void searchProductByName(const string& name, bool& isFound) const;
	const Product* searchProductById(int id, bool& isFound) const;
};
#endif // !_SE_H
 // !_B_H
