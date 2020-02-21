#include "Date.h"

Date::Date(int d, int m, int y) : day(d), month(m), year(y)
{

}
int Date::getDay()const
{
	return this->day;
}

int Date::getMonth()const
{
	return this->month;
}

int Date::getYear()const
{
	return this->year;
}