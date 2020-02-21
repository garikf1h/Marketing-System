#ifndef BS_H_
#define BS_H_

#include "Seller.h"
#include "Buyer.h"

class BuyerSeller:public Buyer, public Seller {

private:
	const BuyerSeller& operator=(const BuyerSeller& other);//cant copy or use opretor =
public:
	BuyerSeller(const string& name, const string& password, const Address& address);
	BuyerSeller(const BuyerSeller&cpy)=delete;
	void show() const;


};

#endif // !BS_H_
