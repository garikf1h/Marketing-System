#include "BuyerSeller.h"

BuyerSeller::BuyerSeller(const string& name, const string& password, const Address & address):User(name,password,address),Buyer(name, password, address),Seller(name, password, address)
{

}

void BuyerSeller::show() const 
{
	Seller::show();
	Buyer::show(false);
	 
}
