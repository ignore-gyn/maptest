/*
 * template_array.cpp
 *
 *  Created on: 2016/07/13
 *      Author: GYN
 */

#include <string>
#include <iostream>
#include <stdlib.h>

#include "template_array.hpp"

int main()
{
	std::string originalStr("abcdigu");

	SpecialArray<char> str1;

	for (unsigned int  i = 0; i != originalStr.size(); i++) {
		str1.addItem(originalStr[i]);
	}

	std::cout << str1 << std::endl;


	SpecialVector<char> str2;

	for (unsigned int  i = 0; i != originalStr.size(); i++) {
		str2.addItem(originalStr[i]);
	}

	std::cout << str2 << std::endl;
}
