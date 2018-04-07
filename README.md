# real_array
This template class is being created to access to the n-th element of an array using [n] instead of [n-1].

    
    
What is this? This is a new, never seen, useless container.
real_array is like a normal array, but with one difference:
to access to the n-th element of the array tou have to use [n] instead of [n-1]. 
What? Yes you have understood perfectly...we say enough to range errors!

What can I do? You can do whatever you want. This template class
provide all common methods like: size, front, back, at and others.
It provides iterators, exceptions for wrong indexing, and useful operator overloading.
You can also initialize a real_array using initializer_list.
Run examples.cpp to see some examples.
    
Note that jfet::real_array transfers its constness to the contained objects
    
P.S. you can use: jfet::char_array instead of jfet::real_array<char>;
    	          jfet::string_array instead of jfet::real_array<std::string>;
	              jfet::int_array instead of jfet::real_array<int> 
	              jfet::float_array instead of jfet::real_array<float> 
	              jfet::double_array instead of jfet::real_array<double
					  
#code4fun