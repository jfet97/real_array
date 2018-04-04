#include "real_array.h"
#include <iostream>

                        // void constructor
			template<typename T>
			real_array<T>::real_array() : real_array<T>(0) {}
			
			// delegated constructor
			template<typename T>
			real_array<T>::real_array(size_t n) {
				if(n) {
					ptr = new T[n];
					_size = n;
				} else {
					ptr = nullptr;
					_size = 0;
				}
			}
			
			// overload for [] operator
			template<typename T>
			T& real_array<T>::operator[](size_t _n) {
				// if 0 is inserted, you got first element as usual ;)
				if(_n==0) return ptr[0];
				// else you got the "real" object requested
				if(_n<=_size) return ptr[_n-1];
				// throw exception if n>size_t
				if(_n>_size) return ptr[0];
			}
			
			// overload for [] operator for const objects
			template<typename T>
			const T& real_array<T>::operator[](size_t _n) const {
				// if 0 is inserted, you got first element as usual ;)
				if(_n==0) return ptr[0];
				// else you got the "real" object requested
				if(_n<=_size) return ptr[_n-1];
				// throw exception if n>size_t
				if(_n>_size) return ptr[0];
			}

			// overload for << operator
			template<typename T>
			std::ostream& operator<<(std::ostream& _os, const real_array<T> &_a) {
				for(size_t index = 1; index <=_a._size; index++) std::cout << _a[index] << std::endl;
				return _os;
			}
			
			// destructor
			template<typename T>
		        real_array<T>::~real_array()
			{
				delete [] ptr;
			}



