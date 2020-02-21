#pragma warning (disable:4996)
#ifndef _F_H
#define _F_H
//class that is part for every user in the system
#include "Date.h"
#include <iostream>
using namespace std;
class Buyer;
class Feedback
{
private:
	const Buyer* reviewer;
	string review;
	const Date reviewDate;
	const Feedback& operator=(const Feedback& other);

public:
	Feedback(const Buyer& reviewer, const string& review,const Date& reviewDate);
	Feedback(const Feedback& cpy) = delete;

	~Feedback();
	const string& getReview() const;
	const Buyer* getReviewr() const;
	const Date& getDate() const;
	friend ostream& operator<<(ostream&os, const Feedback&other);
};
#endif