#include "real_array.h"
#include <iostream>

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



	return 0;
}
