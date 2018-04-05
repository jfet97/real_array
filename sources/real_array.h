#ifndef REALARRAY_H
#define REALARRAY_H

#include <ostream>
#include <iterator>

namespace jfet
{
	
	// approach #2 for Template Classes and Friend Function -> https://web.mst.edu/~nmjxv3/articles/templates.html
	template <typename T> class real_array;
	// Here, operator<< is declared as a template function using a declared (but not yet defined) templated class real_array
	template <typename T> std::ostream& operator<<( std::ostream&, const real_array<T> &);
	
	template<typename T>
	class real_array
	{
		private:
			size_t _size;
			T * ptr;

		public:
			// some definition for STL
			typedef T value_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef long size_type;
			typedef size_type difference_type;

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
			
			// iterator
			class iterator : public std::iterator <std::random_access_iterator_tag, T> {
				
				// derived class can access to it, like const_iterator
				protected:
					T * pointer;
				
				public:
					using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
				
					iterator() : pointer{nullptr} {}
					iterator(T * _p) : pointer{_p} {}
					// rule of zero
					
					// operators overload
					
					T& operator*() const {return *pointer;} // It's const because we do not modify 'pointer' value. We can modify the value pointed
					// const T& operator*() const {return *pointer;} // It's const because we do not modify 'pointer' value. We cannot modify the value pointed, so we return const T&
					T& operator[](difference_type _d) const {return pointer[_d];} // It's const because we do not modify 'pointer' value
					// const T& operator[](difference_type _d) const {return pointer[_d];} // return a const object for const_iterator
					
					iterator& operator+=(difference_type _d) {pointer += _d; return *this;}
					iterator& operator-=(difference_type _d) {pointer -= _d; return *this;}
					iterator& operator++() {++pointer; return *this;} //prefix ++
					iterator& operator--() {--pointer; return *this;} // prefix --
					iterator operator++(int) {iterator temporary{*this}; ++pointer; return temporary;} // postfix ++
					iterator operator--(int) {iterator temporary{*this}; --pointer; return temporary;} // postfix--
					
					difference_type operator-(const iterator& other) const {return pointer - other.pointer;} // difference between iterators
					iterator operator-(difference_type _d) const {return iterator{pointer-_d};} 
					iterator operator+(difference_type _d) const {return iterator{pointer+_d};}
					friend inline iterator operator+(difference_type _d, const iterator& other) {return iterator(_d+other.pointer);}
					friend inline iterator operator-(difference_type _d, const iterator& other) {return iterator(_d-other.pointer);} // weird but...

					bool operator==(const iterator& other) const {return pointer == other.pointer;}
					bool operator!=(const iterator& other) const {return pointer != other.pointer;}
					bool operator>(const iterator& other) const {return pointer > other.pointer;}
					bool operator<(const iterator& other) const {return pointer < other.pointer;}
					bool operator>=(const iterator& other) const {return pointer >= other.pointer;}
					bool operator<=(const iterator& other) const {return pointer <= other.pointer;}
			};
			
			iterator begin() { // not const because i must call cbegin() for const object
				return iterator(ptr);
			}
			
			iterator end() { // not const because i must call cend() for const object
				return iterator(ptr + _size);
			}
	};
}

#include "real_array.tpp"
#endif



