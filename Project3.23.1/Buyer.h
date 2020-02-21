#pragma warning (disable:4996)

#ifndef _B_H
#define _B_H
 // !1
#include <list>
#include <iterator>
#include "Cart.h"
#include "Order.h"
#include "Address.h"
#include "Feedback.h"
#include "Seller.h"
#include "User.h"

class User;

class Buyer:virtual public User
{
private:
	list <Seller*> sellerHistory;
	Order* currOrder;
	Cart cart;
	bool ifSellerExists(const Seller& seller);
	const Buyer& operator=(const Buyer& other);
public:
	Buyer(const string& name, const string& password,const Address& address);
	Buyer(const Buyer& cpy) = delete;
	virtual ~Buyer();
	const list<Seller*>& getAllSellerHistory() const;
	const Cart& getCart() const;
	bool addProductToCart(const Product& productToAdd);
	void makePayment();
	void addProductToOrder(const Product& productToAdd);
	void show(int ind) const ;
	const Product* returnProductInCartById(int id, bool &isFound) const;
	void showCart() const;
	void productToOrderFromCart(int id, bool&isFound);
	void showOrder() const;
	bool checkIfEmptyCart() const ;
	bool isOrderNull() const;
	bool operator>(const Buyer&other) const;
};

#endif