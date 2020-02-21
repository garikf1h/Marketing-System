#pragma warning (disable:4996)


#ifndef _D_H
#define _D_H
class Date
{

private:
	int day, month, year;
public:
	Date(int d, int m, int y);
	int getDay() const;
	int getMonth() const;
	int getYear()const;
};
 // !D_H
#endif