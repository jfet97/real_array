#include "real_array.h"

namespace jfet
{
	// void constructor
	template<typename T>
	real_array<T>::real_array() : real_array<T>(0) {}
	
	// size_t constructor
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
	
	// initializer_list constructor
	template<typename T>
	real_array<T>::real_array(std::initializer_list<T> args) {
		// _size of our real_array is equal to the initializer_list's size
		_size = args.size();
		
		// allocate enough memory, we call type T void constructor...
		ptr = new T[_size];
		
		//... so we move elements from the initializer_list to our array; we avoid copy
		// there does not appear to be any way of using move-semantic in initializer list elements in the current revision of the language, because it provides only const reference to its arguments
		for(size_t i = 0; i < _size; i++) ptr[i] = std::move(args.begin()[i]);
		
	}
	
	// copy constructor
	template<typename T>
	// using T[other._size] I'm sure avoiding garbage values if I change variables' declaration order
	real_array<T>::real_array(const real_array<T> &other) : _size{other._size}, ptr{new T[other._size]} {
		for(size_t index = 0; index < _size; index++) ptr[index] = other.ptr[index];
	}

			
	// copy assignment operator
	template<typename T>
	real_array<T>& real_array<T>::operator= (const real_array<T> &other) {
		// if sizes are different is dangerous perform any operation
		if(_size != other._size) throw std::length_error("sizes are different");
		// object already esixts, so I don't need to allocate new memory
		for(size_t index = 0; index < _size; index++) ptr[index] = other.ptr[index];
		return *this;
	}
	
	// move constructor
	template<typename T>
	// I set ptr = nullptr because move assignment operator call delete to free previous resources that this object does not have
	real_array<T>::real_array(real_array<T> &&other) : _size{0}, ptr{nullptr} {
		// I call move assignment operator
		*this = std::move(other); 
	}

			
	// move assignment operator
	template<typename T>
	real_array<T>& real_array<T>::operator= (real_array<T> &&other) {
		if(this != &other) {
			_size = other._size;
			// object already esixts, so I don't need to allocate new memory, but I must free previous resources
			delete [] ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
			other._size = 0;
		}
		return *this;
	}
	
	// at returns a reference to the element at position n in the real_array 
	template<typename T>
	T& real_array<T>::at(size_t _n) {
		// return const_cast<T&>(std::as_const(*this).at(_n)); 
		// as_const will force the compiler to see *this as a const object, so at(_n) const will be called, const_cast remove the constness from the reference returned | C++17
		return const_cast<T&>(static_cast<const real_array<T>*>(this)->at(_n));
		// static_cast will force the compiler to see this as a pointer to const object, so at(_n) const will be called, const_cast remove the constness from the reference returned
	}
	
	// at returns a const reference to the element at position n in the real_array 
	template<typename T>
	const T& real_array<T>::at(size_t _n) const{
		if(_n==0) throw std::out_of_range("0 is no more a valid index");
		// else you got the "real" object requested
		if(_n<=_size) return ptr[_n-1];
		// throw exception if n>size_t
		else throw std::out_of_range(std::to_string(_n) + " is greater than " + std::to_string(_size));
	}
	
			
	// overload for [] operator
	template<typename T>
	T& real_array<T>::operator[](size_t _n) {
		return this->at(_n); // call non-const version, because this is a pointer to non-const
	}
			
	// overload for [] operator for const objects
	template<typename T>
	const T& real_array<T>::operator[](size_t _n) const {
		return this->at(_n); // call const version, because this is a pointer to const
	}
	
	// overload for == operator
	template<typename T>
	bool real_array<T>::operator==(const real_array<T>& other) const {
		if(_size == other._size) {
			for(size_t i = 0; i < _size; i++) if(ptr[i] != other.ptr[i]) return false; // if I find only one value different them are different
			return true; // they have same size and all elements are equal
		}
		return false; // if them have different size, they cannot be equal
	}
	
	// overload for != operator
	template<typename T>
	bool real_array<T>::operator!=(const real_array<T>& other) const {
		return !(*this==other); // calling == operator
	}
	
	// overload for > operator
	template<typename T>
	bool real_array<T>::operator>(const real_array<T>& other) const {
		if(_size > other._size) return true; 
		if(_size == other._size) { // if sizes are equals, check elements, starting by index 0 (MOST SIGNIFICANT VALUE)
			for(size_t i = 0; i < _size; i++) { 
				if(ptr[i] < other.ptr[i]) return false; // if the value checked is smaller we return false
				if(ptr[i] > other.ptr[i]) return true; // if the value checked is greater we return true
				// if them are the same, for cycle continue...if it ends we return false because values are the same
			}
		}
		return false; // if _size < other._size or if them are exa
	}
	
	// overload for < operator
	template<typename T>
	bool real_array<T>::operator<(const real_array<T>& other) const {
		return !((*this > other)||(*this == other));
	}
	
	//= overload for >= operator
	template<typename T>
	bool real_array<T>::operator>=(const real_array<T>& other) const {
		return !(*this < other);
	}
	
	//= overload for >= operator
	template<typename T>
	bool real_array<T>::operator<=(const real_array<T>& other) const {
		return !(*this > other);
	}

	// overload for << operator
	template<typename T>
	std::ostream& operator<<(std::ostream& _os, const real_array<T> &other) {
		for(size_t index = 1; index <=other._size; index++) _os << other[index] << " ";
		_os << std::endl;
		return _os;
	}
			
	// destructor
	template<typename T>
	real_array<T>::~real_array() {
		delete [] ptr;
	}
}


