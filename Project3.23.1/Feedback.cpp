#include "Feedback.h"

//#include <iostream>
#include <string>
using namespace std;
Feedback::Feedback(const Buyer&reviewer, const string& review,const Date& reviewDate) : reviewDate(reviewDate), review(review)
{
	this->reviewer = &reviewer;
}
Feedback::~Feedback()
{
}
const string& Feedback:: getReview() const
{
	return this->review;
}
const Buyer* Feedback::getReviewr() const
{
	return this->reviewer;
}

const Date& Feedback::getDate() const
{
	return this->reviewDate;
}

ostream& operator<<(ostream & os, const Feedback & other)
{
	os << other.review;
	return os;
}
