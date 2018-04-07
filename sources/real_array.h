#ifndef REALARRAY_H
#define REALARRAY_H

#include <iostream>
#include <iterator>
#include <initializer_list>

/* jfet::real_array transfers its constness to the contained objects */

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
			
			// initializer_list constructor
			real_array(std::initializer_list<T> args);
			
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
			
			// return a reference to the first element
			T& front() {
				return ptr[0];
			}
			
			const T& front() const{
				return ptr[0];
			}
			
			// return a reference to the last element
			T& back() {
				return ptr[_size - 1];
			}
			
			const T& back() const{
				return ptr[-size - 1];
			}
			
			// return a copy of the first element's pointer
			T* data() {
				return ptr;
			}
			
			// if real_array is const, you cannot modify contained elements
			const T* data() const {
				return ptr;
			}
			
			// return a copy of the last element's pointer
			T* last_data() {
				return ptr + _size - 1;
			}
			
			// if real_array is const, you cannot modify contained elements
			const T* last_data() const {
				return ptr + _size - 1;
			}
			
			// returns a reference to the element at position n in the real_array
			T& at(size_t n);
			const T& at(size_t n) const;

			// overload for [] operator
			T& operator[](size_t n);
			
			// overload for [] operator for const object
			const T& operator[](size_t n) const;
			
			// overload for == operator
			bool operator==(const real_array<T>& other) const;
			
			// overload for != operator
			bool operator!=(const real_array<T>& other) const;

			// overload for > operator
			bool operator>(const real_array<T>& other) const;
			
			// overload for < operator
			bool operator<(const real_array<T>& other) const;
			
			// overload for == operator
			bool operator>=(const real_array<T>& other) const;
			
			// overload for != operator
			bool operator<=(const real_array<T>& other) const;

			// overload for << operator
			friend std::ostream& operator<<<T>(std::ostream& _os, const real_array &a);
			
			// destructor
			~real_array();
			
			
			// iterators
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
					
					inline T& operator*() const {return *pointer;} // It's const because we do not modify 'pointer' value. We can modify the value pointed
					inline T& operator[](difference_type _d) const {return pointer[_d];} // It's const because we do not modify 'pointer' value
					
					inline iterator& operator+=(difference_type _d) {pointer += _d; return *this;}
					inline iterator& operator-=(difference_type _d) {pointer -= _d; return *this;}
					inline iterator& operator++() {++pointer; return *this;} //prefix ++
					inline iterator& operator--() {--pointer; return *this;} // prefix --
					inline iterator operator++(int) {iterator temporary{*this}; ++pointer; return temporary;} // postfix ++
					inline iterator operator--(int) {iterator temporary{*this}; --pointer; return temporary;} // postfix--
					
					inline difference_type operator-(const iterator& other) const {return pointer - other.pointer;} // difference between iterators
					inline iterator operator-(difference_type _d) const {return iterator{pointer-_d};} 
					inline iterator operator+(difference_type _d) const {return iterator{pointer+_d};}
					friend inline iterator operator+(difference_type _d, const iterator& other) {return iterator(_d+other.pointer);}
					friend inline iterator operator-(difference_type _d, const iterator& other) {return iterator(_d-other.pointer);} // weird but...

					inline bool operator==(const iterator& other) const {return pointer == other.pointer;}
					inline bool operator!=(const iterator& other) const {return pointer != other.pointer;}
					inline bool operator>(const iterator& other) const {return pointer > other.pointer;}
					inline bool operator<(const iterator& other) const {return pointer < other.pointer;}
					inline bool operator>=(const iterator& other) const {return pointer >= other.pointer;}
					inline bool operator<=(const iterator& other) const {return pointer <= other.pointer;}
			};
			
			class const_iterator : public iterator {
				
				public:
				
					const_iterator() : iterator{nullptr} {}
					const_iterator(T * _p) : iterator{_p} {}
					// rule of zero
					
					// operators overload
					
					inline const T& operator*() const {return *iterator::pointer;} // It's const because we do not modify 'pointer' value. We cannot modify the value pointed, so we return const T&
					inline const T& operator[](difference_type _d) const {return iterator::pointer[_d];} // return a const object 
					
					inline const const_iterator& operator+=(difference_type _d) {iterator::pointer += _d; return *this;}
					inline const const_iterator& operator-=(difference_type _d) {iterator::pointer -= _d; return *this;}
					inline const const_iterator& operator++() {++iterator::pointer; return *this;} //prefix ++
					inline const const_iterator& operator--() {--iterator::pointer; return *this;} // prefix --
					inline const_iterator operator++(int) {const_iterator temporary{*this}; ++iterator::pointer; return temporary;} // postfix ++
					inline const_iterator operator--(int) {const_iterator temporary{*this}; --iterator::pointer; return temporary;} // postfix--
					
					inline difference_type operator-(const const_iterator& other) const {return iterator::pointer - other.iterator::pointer;} // difference between iterators
					inline const_iterator operator-(difference_type _d) const {return const_iterator{iterator::pointer-_d};} 
					inline const_iterator operator+(difference_type _d) const {return const_iterator{iterator::pointer+_d};}
					friend inline const_iterator operator+(difference_type _d, const const_iterator& other) {return const_iterator(_d+other.iterator::pointer);}
					friend inline const_iterator operator-(difference_type _d, const const_iterator& other) {return const_iterator(_d-other.iterator::pointer);} // weird but...

					inline bool operator==(const const_iterator& other) const {return iterator::pointer == other.iterator::pointer;}
					inline bool operator!=(const const_iterator& other) const {return iterator::pointer != other.iterator::pointer;}
					inline bool operator>(const const_iterator& other) const {return iterator::pointer > other.iterator::pointer;}
					inline bool operator<(const const_iterator& other) const {return iterator::pointer < other.iterator::pointer;}
					inline bool operator>=(const const_iterator& other) const {return iterator::pointer >= other.iterator::pointer;}
					inline bool operator<=(const const_iterator& other) const {return iterator::pointer <= other.iterator::pointer;}
			};
			
			class reverse_iterator : public iterator {
				
				public:
				
					reverse_iterator() : iterator{nullptr} {}
					reverse_iterator(T * _p) : iterator{_p} {}
					// rule of zero
					
					// operators overload
					
					/* There is a distinction between the physical
					   position that defines the element to which the iterator refers and the logical position that defines the
					   value to which the iterator refer. 
					   Thus, the value is moved to the previous element -> -1
					*/
					inline T& operator*() const {return *(iterator::pointer - 1);} 
					inline T& operator[](difference_type _d) const {return *(iterator::pointer - _d - 1);} 
					
					// reverse operators' meaning
					inline reverse_iterator& operator+=(difference_type _d) {iterator::pointer -= _d; return *this;}
					inline reverse_iterator& operator-=(difference_type _d) {iterator::pointer += _d; return *this;}
					inline reverse_iterator& operator++() {--iterator::pointer; return *this;} //prefix ++
					inline reverse_iterator& operator--() {++iterator::pointer; return *this;} // prefix --
					inline reverse_iterator operator++(int) {reverse_iterator temporary{*this}; --iterator::pointer; return temporary;} // postfix ++
					inline reverse_iterator operator--(int) {reverse_iterator temporary{*this}; ++iterator::pointer; return temporary;} // postfix--
					
					inline difference_type operator-(const reverse_iterator& other) const {return other.iterator::pointer - iterator::pointer;} // difference between iterators
					inline reverse_iterator operator-(difference_type _d) const {return reverse_iterator{iterator::pointer+_d};} 
					inline reverse_iterator operator+(difference_type _d) const {return reverse_iterator{iterator::pointer-_d};}
					friend inline reverse_iterator operator+(difference_type _d, const reverse_iterator& other) {return reverse_iterator(_d-other.iterator::pointer);}
					friend inline reverse_iterator operator-(difference_type _d, const reverse_iterator& other) {return reverse_iterator(_d+other.iterator::pointer);} // weird but...

					inline bool operator==(const reverse_iterator& other) const {return iterator::pointer == other.iterator::pointer;}
					inline bool operator!=(const reverse_iterator& other) const {return iterator::pointer != other.iterator::pointer;}
					inline bool operator>(const reverse_iterator& other) const {return iterator::pointer < other.iterator::pointer;}
					inline bool operator<(const reverse_iterator& other) const {return iterator::pointer > other.iterator::pointer;}
					inline bool operator>=(const reverse_iterator& other) const {return iterator::pointer <= other.iterator::pointer;}
					inline bool operator<=(const reverse_iterator& other) const {return iterator::pointer >= other.iterator::pointer;}
			};
			
			class const_reverse_iterator : public reverse_iterator {
				
				public:
				
					const_reverse_iterator() : reverse_iterator{nullptr} {}
					const_reverse_iterator(T * _p) : reverse_iterator{_p} {}
					// rule of zero
					
					// operators overload
					
					/* There is a distinction between the physical
					   position that defines the element to which the iterator refers and the logical position that defines the
					   value to which the iterator refer. 
					   Thus, the value is moved to the previous element -> -1
					*/
					const T& operator*() const {return *(iterator::pointer - 1);} 
					const T& operator[](difference_type _d) const {return *(iterator::pointer - _d - 1);} 
					
					// reverse operators' meaning
					inline const const_reverse_iterator& operator+=(difference_type _d) {iterator::pointer -= _d; return *this;}
					inline const const_reverse_iterator& operator-=(difference_type _d) {iterator::pointer += _d; return *this;}
					inline const const_reverse_iterator& operator++() {--iterator::pointer; return *this;} //prefix ++
					inline const const_reverse_iterator& operator--() {++iterator::pointer; return *this;} // prefix --
					inline const_reverse_iterator operator++(int) {const_reverse_iterator temporary{*this}; --iterator::pointer; return temporary;} // postfix ++
					inline const_reverse_iterator operator--(int) {const_reverse_iterator temporary{*this}; ++iterator::pointer; return temporary;} // postfix--
					
					inline difference_type operator-(const const_reverse_iterator& other) const {return other.iterator::pointer - iterator::pointer;} // difference between iterators
					inline const_reverse_iterator operator-(difference_type _d) const {return const_reverse_iterator{iterator::pointer+_d};} 
					inline const_reverse_iterator operator+(difference_type _d) const {return const_reverse_iterator{iterator::pointer-_d};}
					friend inline const_reverse_iterator operator+(difference_type _d, const const_reverse_iterator& other) {return const_reverse_iterator(_d-other.iterator::pointer);}
					friend inline const_reverse_iterator operator-(difference_type _d, const const_reverse_iterator& other) {return const_reverse_iterator(_d+other.iterator::pointer);} // weird but...

					inline bool operator==(const const_reverse_iterator& other) const {return iterator::pointer == other.iterator::pointer;}
					inline bool operator!=(const const_reverse_iterator& other) const {return iterator::pointer != other.iterator::pointer;}
					inline bool operator>(const const_reverse_iterator& other) const {return iterator::pointer < other.iterator::pointer;}
					inline bool operator<(const const_reverse_iterator& other) const {return iterator::pointer > other.iterator::pointer;}
					inline bool operator>=(const const_reverse_iterator& other) const {return iterator::pointer <= other.iterator::pointer;}
					inline bool operator<=(const const_reverse_iterator& other) const {return iterator::pointer >= other.iterator::pointer;}
			};
			
			
			iterator begin() { // not const because i must call cbegin() for const object
				return iterator(ptr);
			}
			
			iterator end() { // not const because i must call cend() for const object
				return iterator(ptr + _size);
			}
			
			const_iterator cbegin() const { 
				return const_iterator(ptr);
			}
			
			const_iterator cend() const {
				return const_iterator(ptr + _size);
			}
			
			reverse_iterator rbegin() { // non-const because i must call crbegin() for const object
				return reverse_iterator(ptr + _size);
			}

			reverse_iterator rend() { // non-const because i must call crend() for const object
				return reverse_iterator(ptr);
			} 
			
			const_reverse_iterator crbegin() const { 
				return const_reverse_iterator(ptr + _size);
			}

			const_reverse_iterator crend() const { 
				return const_reverse_iterator(ptr);
			} 
	};
	
	
	typedef real_array<char> char_array;
	typedef real_array<std::string> string_array;
	typedef real_array<int> int_array;
	typedef real_array<float> float_array;
	typedef real_array<double> double_array;
}

#include "real_array.tpp"
#endif



