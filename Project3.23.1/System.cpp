#include "System.h"
//System class will handle all the things between the other classas and manage the connection between them 
System::System(const string& name):name(name)
{
    this->numOfBuyers = 0;
	this->numOfBuyersSellers = 0;
	this->numOfSellers = 0;
	this->loadFromFile();
	
}
void System::saveToFile()
{
	ofstream outFile("out.txt", ios::trunc);
	list<User*>::iterator begin = usersList.begin();
	list<User*>::iterator end = usersList.end();
	outFile << usersList.size()<<endl;
	for (; begin != end; ++begin)
	{
		outFile << (typeid(**begin).name() + 6) <<" "<< **begin<<endl;
	}
    outFile.close();
}
 
System:: ~System()
{
	this->saveToFile();
	list<User*>::iterator begin = usersList.begin();
	list<User*>::iterator end = usersList.end();
	for (; begin!=end; ++begin)
		delete *begin;
}

const string& System::getName() const
{
	return this->name;
}

bool System::ifUserExists(const string& username, const type_info* t,list<User*>::const_iterator* itr) const
{
	list<User*>::const_iterator begin = usersList.begin();
	list<User*>::const_iterator end = usersList.end();


	for (; begin!=end; ++begin)
	{
		if (username == (*begin)->getUserName())
		{
			if (t == nullptr || typeid(**begin) == typeid(BuyerSeller))
			{
				*itr = begin;
				return true;
			}
				
			if (*t == typeid(**begin))
			{
				*itr = begin;
				return true;
			}
			else
			{
				itr = nullptr;
				return false;
			}
		}
	}
	itr = nullptr;
	return false;
}

void System::AddSeller(Seller& newSeller)
{
	
	this->usersList.push_back(&newSeller);
	this->numOfSellers++;
}
void System::AddBuyer(Buyer& newBuyer)
{
	this->usersList.push_back(&newBuyer);
	this->numOfBuyers++;

}
void System::AddBuyerSeller(const string&name, const string&password, const string&country, const string&city, const string&street, int houseNumber)
{
	this->usersList.push_back(new BuyerSeller(name, password, Address(houseNumber, country, city, street)));
	this->numOfBuyersSellers++;
}

void System::showAllBuyers() 
{
	 Buyer*buyer;
	list<User*>::const_iterator begin = usersList.begin();
	list<User*>::const_iterator end = usersList.end();


	for (; begin != end; ++begin)
	{
		buyer = dynamic_cast< Buyer*>(*begin);
		if(buyer)
		   buyer->show(true);
		cout << endl;
	}
}
 
void System::showAllSellers() 
{
	const Seller* seller;
	list<User*>::const_iterator begin = usersList.begin();
	list<User*>::const_iterator end = usersList.end();


	for (; begin != end; ++begin)
	{
		seller = dynamic_cast<const Seller*>(*begin);
		if (seller)
			seller->show();
		cout << endl;
	}
}
void System::showAllBuyerSeller() 
{
	 BuyerSeller* buyerSeller;
	list<User*>::const_iterator begin = usersList.begin();
	list<User*>::const_iterator end = usersList.end();


	for (; begin != end; ++begin)
	{
		buyerSeller = dynamic_cast< BuyerSeller*>(*begin);
		if (buyerSeller)
			buyerSeller->show();
		cout << endl;
	}
}
void System::addProductToSeller(list<User*>::iterator* itr, const string& nameOfProduct, double price, int category)
{
	Seller*seller;
		seller = dynamic_cast<Seller*>(**itr);
		if(seller)
			seller->addProduct(nameOfProduct, price, (Product::eCategory) category);
	
}


bool System::ifBuyerBoughtFromSeller(list<User*>::const_iterator& itrB, string& usernameOfSeller, list<User*>::const_iterator& itrS) const
{
		Seller*seller;
		Buyer*buyer;

	     if (!this->ifUserExists(usernameOfSeller,&typeid(Seller),&itrS))
		   return false;


	   seller =dynamic_cast<Seller*>(*itrS);
	   buyer = dynamic_cast<Buyer*>(*itrB);


	list<Seller*>::const_iterator begin = buyer->getAllSellerHistory().begin();
	list<Seller*>::const_iterator end = buyer->getAllSellerHistory().end();

	for (;begin!=end &&seller&&buyer; ++begin)
	{
		if (*begin == seller)
			return true;
	}
	return false;
}
void System::addFeedbackToSeller(list<User*>::iterator* itrB, list<User*>::iterator* itrS, string& feedback,int day,int month,int year)
{
	Buyer*buyer = nullptr;
	Seller*seller = nullptr;

		buyer = dynamic_cast<Buyer*>(**itrB);
		seller = dynamic_cast<Seller*>(**itrS);
	if(seller&&buyer)
		seller->addFeedbackToArr(*buyer, feedback, day, month, year);
}
void System::searchProductName(const string& pName,bool& isFound) const
{
	Seller* seller;
	list<User*>::const_iterator begin = usersList.begin();
	list<User*>::const_iterator end = usersList.end();
	for (; begin != end; ++begin)
	{
		
		seller = dynamic_cast<Seller*>(*begin);
		if(seller)
		     seller->searchProductByName(pName,isFound);
	}
}

void System::addProductById(int id, bool& isFound, list<User*>::iterator* itr)
{
	int i;
	const Product* productToReturn = nullptr;
	Seller*seller=nullptr;
	Buyer*buyer = nullptr;
	BuyerSeller*buyerSeller = nullptr;
	list<User*>::iterator begin = usersList.begin();
	list<User*>::iterator end = usersList.end();

	for (; begin!=end&&!isFound ; ++begin)
	{
		seller = dynamic_cast<Seller*>(*begin);
		if(seller)
		    productToReturn = seller->searchProductById(id, isFound);
	}
	      
	if (--begin==*itr)//check if same seller and buyer, can't by product from myself
		isFound = false;

	if (isFound)
	{
		buyer = dynamic_cast<Buyer*>(**itr);
		 if(buyer)
		   buyer->addProductToCart(*productToReturn);
	}
}
bool System::showCartByBuyer(list<User*>::iterator* itr) const
{

	Buyer*buyer;
	    buyer = dynamic_cast<Buyer*>(**itr);
	if (buyer)
	{
		buyer->showCart();
		return true;
	}
	return false;
}

bool System::addProductToOrderInBuyer(list<User*>::iterator* itr, int id, bool&isFound)
{
	Buyer*buyer = nullptr;

		buyer = dynamic_cast<Buyer*>(**itr);
		if (buyer)
		{
			buyer->productToOrderFromCart(id, isFound);
			return true;
		}
	return false;
}
bool System::showOrderByBuyer(list<User*>::iterator* itr) const
{
	Buyer*buyer = nullptr;
	buyer = dynamic_cast<Buyer*>(**itr);
	if (buyer)
	{
		buyer->showOrder();
		return true;
	}
	return false;
}
bool System::makePaymentByBuyer(list<User*>::iterator* itr)
{
	Buyer*buyer = nullptr;
	buyer = dynamic_cast<Buyer*>(**itr);
	if (buyer)
	{
		buyer->makePayment();
		return true;
	}
	return false;
}

bool System::checkIfEmptyCartOfIndexBuyer(list<User*>::iterator* itr) const
{
	Buyer*buyer = nullptr;
			buyer = dynamic_cast<Buyer*>(**itr);
		if(buyer)
			return buyer->checkIfEmptyCart();
	
	return false;
}
bool System::isBuyerOfSellerArrayEmpty(const string& whoToCheck) const
{
	if(whoToCheck == "buyer")
	    return (this->numOfBuyers== 0 && this->numOfBuyersSellers == 0);
	if (whoToCheck == "seller")
		return (this->numOfSellers == 0 && this->numOfBuyersSellers == 0);
	if (whoToCheck == "buyerSeller" )
		return (this->numOfBuyersSellers == 0);

	return false;
}
bool System::isOrderNullInBuyer(list<User*>::iterator* itr) const
{
	Buyer* buyer = nullptr;
	
		buyer = dynamic_cast<Buyer*>(**itr);
		if(buyer)
			return buyer->isOrderNull();
	
	return false;

}
void System::operator+=(Buyer& newBuyer)
{
	this->AddBuyer(newBuyer);
}
void System::operator+=(Seller& newSeller)
{
	this->AddSeller(newSeller);
}

bool System::checkCarts(list<User*>::iterator* itr1, list<User*>::iterator* itr2)
{
	Buyer*b1 = dynamic_cast<Buyer*>(**itr1);
	Buyer*b2 = dynamic_cast<Buyer*>(**itr2);
	if (b1 && b2)
		return(*b1 > *b2);
	else
		return false;
}
void System::readFieldsFromFile(ifstream &inFile, string&type,string&username, string&password, string&country, string&city,string &street,int&housenum)
{
	
	inFile >> type;
	inFile >> username;
	inFile >> password;
	inFile >> country;
	inFile >> city;
	inFile >> street;
	inFile >> housenum;
}
void System::loadFromFile()
{
	int numOfUsers;
	string username, password, type, country, city, street;
	int housenum;
	ifstream inFile("out.txt");
	inFile >> numOfUsers;
	for (int i = 0; i < numOfUsers; i++)
	{
	
		readFieldsFromFile(inFile,type, username, password, country, city, street, housenum);
		if (type == "Buyer")
			*this+=*new Buyer(username, password, Address(housenum, country, city, street));
	    if (type == "Seller")
		    *this+=*new Seller(username, password, Address(housenum, country, city, street));
	    if (type == "BuyerSeller")
	     	AddBuyerSeller(username, password, country, city, street, housenum);
	}

	

}
