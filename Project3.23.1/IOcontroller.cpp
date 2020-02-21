//manage all the connection with the user input and output in the main to the system
#include "IOcontroller.h"
#include <ctime>
#include <string>
IOcontroller::IOcontroller(const string& name) : theSystem(name)
{
	
}
void IOcontroller::printMenuAll(const string& name) const
{
	cout << "Hello, Welcome To " << name << " please choose option from 1 - 11" << endl;
	cout << "1 - Add buyer" << endl;
	cout << "2 - Add seller" << endl;
	cout << "3 - Add BuyerSeller" << endl;
	cout << "4 - Add item to seller" << endl;
	cout << "5 - Add feedback to seller" << endl;
	cout << "6 - Add product to cart" << endl;
	cout << "7 - Make order" << endl;
	cout << "8 - Make payment" << endl;
	cout << "9 - Show all buyers details" << endl;
	cout << "10- Show all sellers details" << endl;
	cout << "11 - Show all sellersBuyers details" << endl;
	cout << "12 - Search product by name" << endl;
	cout << "13 - open oparetor menu" << endl;
	cout << "14 - EXIT" << endl;
}
void IOcontroller::addToCartMenu() 
{
	int productId;
	bool isFound;
	string name;
	list<User*>::iterator itrB;
	int ind = 1;
	cout << "Please enter the username of buyer you want to add product to cart to ";
	cin >> name;
 	while (ind == 1)
	{
		if (theSystem.ifUserExists(name,&typeid(Buyer),&itrB))
		{
			cout << "Please enter products id you want to add , when you finish typing id's enter -1 " << endl;
			cin >> productId;
			if (productId == -1)
				ind = -1;
			while (productId != -1)
			{
				isFound = false;
				theSystem.addProductById(productId, isFound,&itrB);
				if (!isFound)
					cout << "The product "<<productId<<" doesn't exist in our website or buyerSeller try to buy product from himself" << endl;
				else
					cout << "The product " << productId << " was added succsessfully " << endl;
				cin >> productId;
				if (productId == -1)
					ind = -1;
			}
		}
		else
		{
			cout << "The username dosnt exist, press 1 to enter diffrent name else press 2 to go back to the menu" << endl;
			cin >> ind;
			clearBuffer();
			if(ind == 1)
				cin >> name;
		}
	}
}

void IOcontroller::makeOrderMenu()
{
	string userName;
	list<User*>::iterator itrB;
	bool isFound;
	cout << "Please enter username you want to make order for ";
	cin>>userName;
	if (theSystem.ifUserExists(userName, &typeid(Buyer), &itrB))
	{
		theSystem.showCartByBuyer(&itrB);
		if (!theSystem.checkIfEmptyCartOfIndexBuyer(&itrB))
			getIdInputToOrder(&itrB, isFound, userName);
		if (theSystem.checkIfEmptyCartOfIndexBuyer(&itrB))
		{
			cout << "The cart of user " << userName << " is empty. Going back to the main manu"<<endl;
			_sleep(DELAY);
		}
	}
	else
	{
		cout << "The username is not in the system. Going back to the main menu." << endl;
		_sleep(DELAY);
	}
}
void IOcontroller::getIdInputToOrder(list<User*>::iterator* itrB,bool& isFound,const string& userName)
{
	
	int id;
	cout << "please enter the product id you want,if you want to finish the order press -1 " << endl;
	cin >> id;
	while (id != -1 && !theSystem.checkIfEmptyCartOfIndexBuyer(itrB))
	{
		isFound = false;
		theSystem.addProductToOrderInBuyer(itrB, id, isFound);
		if (!isFound)
			cout << "The product which id is: " << id << " is not in cart list of " << userName;
		else
			cout << "The product which id is: " << id << " was added successfully to the order!";
		if (!theSystem.checkIfEmptyCartOfIndexBuyer(itrB))
		{
			cout << " Enter -1 to stop entering id and go back to the main manu or press another id " << endl;
			cin >> id;
		}
	}
}
void IOcontroller::checkOperators()
{
	string input,name1,name2;
	list<User*>::iterator itrB1, itrB2;
	cout << "Hey, enter the operator you want to check : += add buyer or seller, > to compare between 2 carts "<< endl;//opretor <<(ostream) can be checked in the print and inside the classes
	cin >> input;
	if ( input == "+=")
	{
		cout << "enter buyer or seller" << endl;
		cin >> input;
		addBuyerOrSellerMenu(input);
	}
	if (input ==">")
	{
		cout << "Enter the first buyer"<<endl;
		cin >> name1;
		cout << "Enter the second buyer"<<endl;
		cin >> name2;
		if (theSystem.ifUserExists(name1,&typeid(Buyer),&itrB1) && theSystem.ifUserExists(name2,&typeid(Buyer),&itrB2))
		{
			if (theSystem.checkCarts(&itrB1, &itrB2))
				cout << "total cart cost of " << name1 << " > total cart cost " << name2 << endl;
			else
				cout << "total cart cost of " << name1 << " <= total cart cost " << name2 << endl;
		}
		else
			cout << "One of the usernames isn't exist. going back to the main manu";
		_sleep(DELAY);

	}
}
const string IOcontroller::getFeedbackFromUserInput() const
{

	string feedback;
	getline(cin,feedback);
    return feedback;

}

void IOcontroller::getUserDetails(const string& whoToAdd, string& name, string& password, string& city, string& street, string& country,int& houseNumber) const
{
	int ind = 1;
	cout << "Hello, please enter the name of the " << whoToAdd << " ";
	cin >> name;
	cout << endl;
	cout << "Please enter the password for " << name << " " ;
	cin >> password;
	cout << endl;
	cout << "Please enter the country for " << name << " ";
	cin >> country;
	cout << endl;
	cout << "Please enter the city for " << name << " ";
	cin >> city;
	cout << endl;
	cout << "Please enter the street for " << name << " ";
	cin >> street;
	cout << endl;
	cout << "Please enter house number for " << name << " ";
	cin >> houseNumber;
	cout << endl;
}

void IOcontroller::addBuyerOrSellerMenu(const string& whoToAdd)
{
	string name, password, city, street, country;
	int houseNumber;
	list<User*>::iterator itr;
	clearBuffer();
	getUserDetails(whoToAdd,name,password, city, street, country,houseNumber);
	if (whoToAdd == "buyer")
	{
		if (theSystem.ifUserExists(name,nullptr,&itr))
			cout << "Username is already exist in the System, you will move back to the main menu" << endl;
		else
		{
			Buyer*newBuyer = new Buyer(name, password, Address(houseNumber, country, city, street));
			theSystem += *newBuyer;
cout << endl << whoToAdd << " was added successfully. Going back to the main menu" << endl;
		}
	}
	else if (whoToAdd == "seller")
	{
		if (theSystem.ifUserExists(name, nullptr,&itr))
			cout << "Username is already exist in the System, you will move back to the main menu" << endl;
		else
		{
			Seller* newSeller = new Seller(name, password, Address(houseNumber, country, city, street));
			theSystem += *newSeller;
			cout << endl << whoToAdd << " was added successfully. Going back to the main menu" << endl;
		}
	}
	else
	{
		if (theSystem.ifUserExists(name, nullptr, &itr))
			cout << "Username is already exist in the System, you will move back to the main menu" << endl;
		else
		{
			theSystem.AddBuyerSeller(name, password, country, city, street, houseNumber);
			cout << endl << whoToAdd << " was added successfully. Going back to the main menu" << endl;
		}
	}
	_sleep(DELAY);

}
void IOcontroller::showAllBuyersSellerDetailsMenu( const string& whoToPrint)
{
	if (whoToPrint == "buyer")
		if (!theSystem.isBuyerOfSellerArrayEmpty(whoToPrint))
			theSystem.showAllBuyers();
		else
			cout << "There are not buyers in the system"<<endl;
	else if (whoToPrint == "seller")
		if (!theSystem.isBuyerOfSellerArrayEmpty(whoToPrint))
		      theSystem.showAllSellers();
		else
	     cout << "There are not sellers in the system"<<endl;
	else 
	if (!theSystem.isBuyerOfSellerArrayEmpty(whoToPrint))
		theSystem.showAllBuyerSeller();
	else
		cout << "There are not buyersellers in the system" << endl;

	_sleep(DELAY);

}
void getCurrentDate(int &year,int&month,int& day) 
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	year = 1900 + ltm->tm_year;
	month = 1 + ltm->tm_mon;
	day = ltm->tm_mday;

}
void IOcontroller:: showAllDetailsOfProductByNameMenu() const
{
	int ind = 1;
	string productName;
	while (ind == 1)
	{
		bool productFound = false;
		cout << "Please enter product you want to search details about " << endl;
		cin >> productName;
		theSystem.searchProductName(productName, productFound);
		if (!productFound)
			cout << "The product "<<productName<<" doesnt exist in the system,if you want to search diffrent product ,press 1 or another digit to go back to the menu " << endl;
		else
			cout << "Do you want to search another product? press 1 for yes or another digit to go to the main menu " << endl;	
		cin >> ind;
		clearBuffer();
	}
}
void IOcontroller::addFeedbackToSellerMenu()
{
	string buyer,seller;
	list<User*>::iterator itrB,itrS;
	int ind=1;
	while (ind == 1)
	{
		cout << "Please Enter the username of the buyer that bought a product ";
		cin >> buyer;
		clearBuffer();
		if (theSystem.ifUserExists(buyer,&typeid(Buyer),&itrB))//check if buyer extists in the system,returns the index of buyer by ref
		{
			cout << "Please Enter the username of the seller you want to add a feedback to ";
			cin >> seller;
			clearBuffer();
			if (theSystem.ifBuyerBoughtFromSeller(itrB, seller, itrS))//check if buyer bougth from seller,returns by ref the index.
				addFeedbackIfvalidSeller(itrB, buyer, seller, itrS, ind);
			else
			{
				cout << "This seller is not in the history of " << buyer << " Enter 1 to keep trying or another digit to get to the main manu ";
				cin >> ind;
			}
		}
		else
		{
			cout << "This buyer doesn't exist in the system. Enter 1 to keep trying or another digit to get to the main manu ";
			cin >> ind;
		}
	}
}
void IOcontroller:: addFeedbackIfvalidSeller(list<User*>::iterator itrB,const string& buyer,const string& seller, list<User*>::iterator itrS,int& ind)
{
	string feedback;
	int year, month, day;
	cout << "Hey, " << buyer << " please enter the feedback for " << seller << endl;
	feedback = this->getFeedbackFromUserInput();
	getCurrentDate(year, month, day);
	theSystem.addFeedbackToSeller(&itrB, &itrS, feedback, day, month, year);
	cout << "Feedback was added to " << seller << ". going back to the main manu." << endl;
	ind = 2;
	_sleep(DELAY);

}
void IOcontroller::makePaymentMenu()
{
	int confirmButton;
	int ind=1;
	list<User*>::iterator itr;
	string username;
	while (ind == 1)
	{
		cout << "Please Enter the username of the buyer you want to make payment for ";
		cin >> username;
		if (theSystem.ifUserExists(username,&typeid(Buyer),&itr))
		{
			if (!theSystem.isOrderNullInBuyer(&itr))
			{
				theSystem.showOrderByBuyer(&itr);
				cout << "Please confirm the order by pressing 1 ,if you want to go to the main menu,press 2 ";
				cin >> confirmButton;
				if (confirmButton == 1)
				{
					theSystem.makePaymentByBuyer(&itr);
					cout << "Order complete. We will send your products soon " << endl;
					_sleep(DELAY);
				}
				ind = 2;
			}
			else
			{
				cout << "The buyer " << username << " has no open order to pay for. please add products to order from cart. going back to the main menu.";
				_sleep(DELAY);
				ind = 2;
			}
		}
		else
		{
			cout << "This buyer "<<username<<" doesn't exist in the system. Enter 1 to keep trying or another digit to get to the main manu ";
			cin >> ind;
			clearBuffer();
		}
	}
}
void IOcontroller::addItemToSellerMenu()
{
	string username,nameOfProduct;
	int category, ind = 1;
	list<User*>::iterator itr;
	double price;
	bool first = false;
	cout << "Please Enter the username of the seller you want to add product to: ";
	cin >> username;
		while (ind == 1)
		{
			if ( first || theSystem.ifUserExists(username,&typeid(Seller),&itr))
			{
				cout << "Adding product to: " << username << endl;
				cout << "Enter the name of the product,max 20 letters: ";
				cin >> nameOfProduct;
				cout << "What's the price of " << nameOfProduct << "? ";

				cin >> price;
				while (price <= 0)
				{
					cout << "Price is negative or 0, please enter a new price"<<endl;
					cin >> price;
				}
				cout << "Enter the category of " << nameOfProduct << " enter 1 -if the category is children, enter 2 for Electronics,enter 3 for office, enter 4 for clothes " << endl;
				cin >> category;
				theSystem.addProductToSeller(&itr, nameOfProduct, price, category);
				cout << "Product was added succsesfully. Do you want to add another product? press 1 for yes or another digit to get back to the main menu " << endl;
				cin >> ind;
				first = true;
			}
			else
			{
				cout << "The username " << username << " doesn't exist in the system. if you want to keep trying press 1 or another digit to go to the main menu: "<<endl;
			    cin >> ind;
				clearBuffer();
				if (ind == 1)
				{
					cout << "Please Enter the username of the seller you want to add product to: ";
					cin >> username;
				}
			}
		}
}

void IOcontroller::run()
{
	int userChoise;

	this->printMenuAll(theSystem.getName());
	cin >> userChoise;
	clearBuffer();
	while (userChoise != 14)
	{
		if (userChoise == 1)
			this->addBuyerOrSellerMenu("buyer");
		if(userChoise==2)
			this->addBuyerOrSellerMenu( "seller");
		if (userChoise == 3)
			this->addBuyerOrSellerMenu("buyerSeller");
		if (userChoise == 4)
			this->addItemToSellerMenu();
		if(userChoise==5)
			this->addFeedbackToSellerMenu();
		if (userChoise == 6)
			this->addToCartMenu();
		if (userChoise == 7)
			this->makeOrderMenu();
		if (userChoise == 8)
			this->makePaymentMenu();
		if (userChoise == 9)
			this->showAllBuyersSellerDetailsMenu("buyer");
		if (userChoise == 10)
			this->showAllBuyersSellerDetailsMenu("seller");
		if (userChoise == 11)
			this->showAllBuyersSellerDetailsMenu("buyerSeller");
		if (userChoise == 12)
			this->showAllDetailsOfProductByNameMenu();
		if (userChoise == 13)
			checkOperators();
		if (userChoise > 14 || userChoise <= 0||cin.fail())
		{
			cinFail();
			
		}
		this->printMenuAll(theSystem.getName());
		cin >> userChoise;
		clearBuffer();

	}
}
