
#pragma warning (disable:4996)

#ifndef _C_H
#define _C_H
 // !_C_H


#include "Product.h"
#include <iostream>
#include <list>
#include <iterator>
using namespace std;

class Cart {

private:
	list<const Product*> productsArray;
	double totalPrice;
	const Cart& operator=(const Cart& other);

public:
	Cart();
	Cart(const Cart& cpy) = delete;
	~Cart();
	void addToCart( const Product&product);
	const list<const Product*>& getAllProducts() const;
	void show() const ;
	void deleteProduct(const Product&productToDelete);
	const Product* returnProductById(int id, bool& isFound) const;
	bool checkIfEmpty() const ;
	double getTotalPrice() const;
};

#endif