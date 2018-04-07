#include "real_array.h"
#include <iostream>
int main(int argc, char **argv)
{
	jfet::real_array<int> a(5);
	jfet::real_array<int> b(5);
	
	
	for(int i = 1; i <= 5; i++) {
		a[i] = i;
	}
	
	for(int i = 1; i <= 5; i++) {
		b[i] = 2*i;
	}
	
	
	try {
		b[67];
	}
	catch(std::out_of_range exception) {
		std::cout << exception.what() << std::endl;
	}
	
	
	jfet::real_array<int>c = std::move(a);
	jfet::real_array<int>d(5);
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

	jfet::real_array<int> array_1 = b;
	jfet::real_array<int> array_2 = b;
	jfet::real_array<int> array_3 (4);
	
	std::cout << std::endl << "------------------------------------------------------------------------------" << std::endl;
	
	if(array_2 == array_1) std::cout << "We are equals" << std::endl;
	if(array_2 != array_3) std::cout << "We are different" << std::endl;
	std::cout << array_1.front() << std::endl;
	std::cout << array_1.back() << std::endl;
	std::cout << array_1.at(3) << std::endl;
	
	try {
		std::cout << array_1.at(54) << std::endl;
	}
	catch(std::out_of_range exception) {
		std::cout << exception.what() << std::endl;
	}
	
	jfet::real_array<float> realFloatArray {1.5, 6.8, 33.2, 9.53};
	std::cout << "realFloatArray has size: " << realFloatArray.size() << std::endl;
	for(auto x : realFloatArray) std::cout << x << std::endl;
	
	
	jfet::real_array<std::string> p {"aaa","aab","aab"};
	jfet::real_array<std::string> p2 {"aaa","aab","aac"};
	if(p >= p2) std::cout << "ciao" << std::endl; 
	
	
	jfet::int_array ar {1,2,3,4,5,6,7,8,9,0};
	for(auto x : ar) std::cout << x << std::endl;
	
	return 0;
}
