#ifndef _O_H
#define _O_H
 


#include "Array.h"
#include "Cart.h"
#include <iostream>
using namespace std;
class Order {
private:
	list<const Product*> productsList;
	double totalCost;
	const Order& operator=(const Order& other);

public:
	Order();
	Order(const Order& cpy) = delete;
	~Order();
	double getTotalCost() const;
	void addProduct(const Product& newProduct);
	const list<const Product*> &getAllOrderProducts() const;
	friend ostream& operator<<(ostream&os, const Order&other);

};
#endif //