#ifndef _AR_H
#define _AR_H

#include <iostream>
using namespace std;
template <class T>
class Array
{
private:
	int pSize, logSize;
	char delimiter;
	T*arr;
	Array(const Array<T>&other);
	const Array&operator=(const Array&other);
public:
	Array(int size = 10, char delimiter = ' ');
	
	~Array();
	
	int getLogSize() const;
	void resizeArray();
	const Array&operator+=(const T&newVal);
	const T& operator[](int index) const;
	friend ostream&operator<<(ostream&os, const Array&arr)
	{
		for (int i = 0; i < arr.logSize; i++)
		{
			os << *arr.arr[i] ;
		}
		return os;
	}

};
template <class T>
Array<T>::Array(const Array<T>&other)
{
	*this = other;
}
template <class T>
Array<T>::Array(int maxSize, char delimiter):pSize(maxSize),logSize(0),delimiter(delimiter)
{
	arr = new T[pSize];
}
template <class T>
Array<T>::~Array()
{
	delete[]arr;
}
template <class T>
const Array<T>&Array<T>::operator=(const Array<T>&other)
{
	if (this != &other)
	{
		delete[]arr;
		pSize = other.pSize;
		logSize = other.logSize;
		delimiter = other.delimiter;
		arr = new T[other.pSize];
		for (int i = 0; i < logSize; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	return *this;
}
template <class T>
const Array<T>& Array<T>::operator+=(const T& newVal)
{
	if (pSize == logSize)
		resizeArray();
	else
		arr[logSize++] = newVal;

	return *this;
}

template <class T>
void Array<T>::resizeArray()
{
	pSize *= 2;
	T *temp = new T[pSize];

	for (int i = 0; i < logSize; i++)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = temp;
}
template <class T>
const T& Array<T>::operator[](int index) const
{
	return arr[index];
}
template <class T>
int Array<T>::getLogSize() const
{
	return this->logSize;
}
#endif // !_AR_H
