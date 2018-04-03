#include "real_array.h"
#include <ostream>

namespace jfet
{
			// void constructor 
			real_array::real_array(): real_array(0) {}

			// delegated constructor
			real_array::real_array(size_t n): _size{n} {
				if(n) ptr = new T[n];
				else ptr = nullptr;
			}

			// overload for [] operator
			T& real_array::operator[](size_t _n) {
				// if 0 is inserted, you got first element as usual ;)
				if(_n==0) return ptr[0];
				// else you got the "real" object requested
				if(_n<=_size) return ptr[n-1];
				// throw exception if n>size_t
			}

			// overload for << operator
			std::ostream& operator<<(std::ostream& _os, const real_array &_a) {
				_os << static_cast<void*>_a.ptr;
				return _os;
			}
			
			// destructor
			~real_array()
			{
				delete [] ptr;
			}
	};
}
