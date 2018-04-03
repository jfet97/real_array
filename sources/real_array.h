#ifndef REALARRAY_H
#define REALARRAY_H

#include <ostream>

namespace jfet
{

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

			// no copy - temporary
			real_array(const real_array&) = delete;
			real_array& operator = (const real_array&) = delete;
			
			
			// return the numbers of element inserted in the array
			size_t size() {
				return _size;
			}

			// overload for [] operator
			T& operator[](size_t n);

			// overload for << operator
			friend std::ostream& operator<<(std::ostream& os, const real_array &a);
			
			// destructor
			~real_array();
	};
}

#endif

