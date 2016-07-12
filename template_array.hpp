/*
 * template_array.hpp
 *
 *  Created on: 2016/07/13
 *      Author: GYN
 */

#ifndef TEMPLATE_ARRAY_HPP_
#define TEMPLATE_ARRAY_HPP_


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <map>



#define SIZE 512

template <typename T>
class SpecialArray
{
	template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const SpecialArray<U>& sa);

private:
	T* pArray;
    unsigned int size;
    unsigned int count;

public:
    //T* getBufferPointer();
    //void findItem(T classValue, unsigned int* nIndex);

	SpecialArray()
	{
		pArray = new T[SIZE];
		size = SIZE;
		count = 0;
	}

	~SpecialArray()
	{
		delete[] pArray;
	}


	T* getBufferPointer()
	{
		return pArray;
	}

	void addItem(T classValue)
	{
		if (count >= size) {
			size += SIZE;
			T* tmp = new T[size];
			delete[] pArray;
			pArray = tmp;
		}
		pArray[count] = classValue;
		count++;
	}

	void findItem(T classValue, unsigned int* nIndex)
	{
		for (unsigned int i = 0; i < count; i++) {
			if (pArray[i] == classValue) {
				*nIndex = i;
				return;
			}
		}

		return;
	}

};

template<typename T> std::ostream& operator<<(std::ostream& os, const SpecialArray<T>& sa)
{
	os << sa.pArray;
	return os;
}


template <typename T>
class SpecialVector
{
	template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const SpecialVector<U>& sa);

private:
	std::vector<T> pArray;
    //unsigned int size;
    //unsigned int count;

public:

	SpecialVector()
	{
		//std::vector<T> data;
		//pArray = &data;
	}

	~SpecialVector()
	{
	}

	T* getBufferPointer()
	{
		return &pArray;
	}


	void addItem(T classValue)
	{
		pArray.push_back(classValue);
	}

	void findItem(T classValue, unsigned int* nIndex)
	{
		typename std::vector<T>::iterator iter = pArray.find(classValue);
		if (iter != pArray.end()) {
			*nIndex = iter - pArray.begin();
			return;
		}

		return;
	}
};

template<typename T> std::ostream& operator<<(std::ostream& os, const SpecialVector<T>& sa)
{
	//typename std::vector<T>::iterator
    for (typename std::vector<T>::const_iterator iter = sa.pArray.begin(); iter != sa.pArray.end(); ++iter) {
        std::cout <<  *iter;
    }
	return os;
}

#endif /* TEMPLATE_ARRAY_HPP_ */
