#ifndef REALARRAY_H
#define REALARRAY_H

#include <ostream>

namespace jfet
{
	
	// approach #2 for Template Classes and Friend Function -> https://web.mst.edu/~nmjxv3/articles/templates.html
	template <typename T> class real_array;
	// Here, operator<< is declared as a template function using a declared (but not yet defined) templated class real_array
	template <typename T> std::ostream& operator<<( std::ostream&, const real_array<T> &);
	
	template<class T>
	class real_array
	{
		private:
			size_t _size;
			T *ptr;

		public:
			// void constructor
			real_array();

			// delegated constructor
			real_array(size_t n);

			// copy constructor
			real_array(const real_array&);
			
			// copy assignment operator
			real_array& operator= (const real_array&);
			
			// move constructor
			real_array(real_array&&);
			
			// move assignment operator
			real_array& operator= (real_array&&);
			
			// return the numbers of element inserted in the array
			size_t size() const {
				return _size;
			}
			
			// return the numbers of element inserted in the array
			size_t length() const {
				return _size;
			}

			// overload for [] operator
			T& operator[](size_t n);
			
			// overload for [] operator for const object
			const T& operator[](size_t n) const;

			// overload for << operator
			friend std::ostream& operator<<<T>(std::ostream& _os, const real_array &a);
			
			// destructor
			~real_array();
	};
}

#include "real_array.tpp"
#endif



