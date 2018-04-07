#include "real_array.h"
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	jfet::real_array<int> a{5};
	jfet::real_array<int> b{5};
	
	
	for(int i = 1; i <= 5; i++)
	{
		a[i] = i;
	}
	
	for(int i = 1; i <= 5; i++)
	{
		b[i] = 2*i;
	}
	
	
	try {
	b[67];
	}
	catch(std::out_of_range exception) {
		std::cout << exception.what() << std::endl;
	}
	


	
	jfet::real_array<int>c = std::move(a);
	jfet::real_array<int>d{5};
	d = b;
	
	std::cout << std::endl << "------------------------------------------------------------------------------" << std::endl;
	
	for(jfet::real_array<int>::iterator iter = d.begin(); iter != d.end(); iter++) *iter *= 2;
	for(jfet::real_array<int>::iterator iter = d.begin(); iter != d.end(); iter++) std::cout << "d: "<< *iter << std::endl;
	
	// for(jfet::real_array<int>::const_iterator iter = d.cbegin(); iter != d.cend(); iter++) *iter *= 2; 
	// ERROR *iter *= 2 because iter is const_iterator
	
	for(jfet::real_array<int>::const_iterator iter = d.cbegin(); iter != d.cend(); iter++) std::cout << "d: "<< *iter << std::endl;
	
	const jfet::real_array<int> e{b};
	// for(jfet::real_array<int>::iterator iter = e.begin(); iter != e.end(); iter++) std::cout << "e: "<< *iter << std::endl;
	// ERROR you can't use non.const iterator on const object, also for read-only operation. You have to use const_iterator
	for(jfet::real_array<int>::const_iterator iter = e.cbegin(); iter != e.cend(); iter++) std::cout << "e: "<< *iter << std::endl;
	
	std::cout << std::endl << "------------------------------------------------------------------------------" << std::endl;
	
	for(jfet::real_array<int>::reverse_iterator iter = d.rbegin(); iter != d.rend(); iter++) *iter *= 2;
	for(jfet::real_array<int>::reverse_iterator iter = d.rbegin(); iter != d.rend(); iter++) std::cout << "d: "<< *iter << std::endl;
	
	// for(jfet::real_array<int>::const_reverse_iterator iter = d.crbegin(); iter != d.crend(); iter++) *iter *= 2; 
	// ERROR *iter *= 2 because iter is const_reverse_iterator
	
	for(jfet::real_array<int>::const_reverse_iterator iter = d.crbegin(); iter != d.crend(); iter++) std::cout << "d: "<< *iter << std::endl;
	
	const jfet::real_array<int> f{b};
	// for(jfet::real_array<int>::reverse_iterator iter = e.rbegin(); iter != e.rend(); iter++) std::cout << "e: "<< *iter << std::endl;
	// ERROR you can't use non-const reverse_iterator on const object, also for read-only operation. You have to use const_iterator
	for(jfet::real_array<int>::const_reverse_iterator iter = e.crbegin(); iter != e.crend(); iter++) std::cout << "f: "<< *iter << std::endl;

	

	return 0;
}
