#include "real_array.h"
#include <iostream>


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
		_size = other._size;
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
		// if 0 is inserted, you got first element as usual ;)
		if(_n==0) return ptr[0];
		// else you got the "real" object requested
		if(_n<=_size) return ptr[_n-1];
		// throw exception if n>size_t
		else throw std::out_of_range(std::to_string(_n) + " is greater than " + std::to_string(_size));
	}
	
	// at returns a const reference to the element at position n in the real_array 
	template<typename T>
	const T& real_array<T>::at(size_t _n) const{
		// if 0 is inserted, you got first element as usual ;)
		if(_n==0) return ptr[0];
		// else you got the "real" object requested
		if(_n<=_size) return ptr[_n-1];
		// throw exception if n>size_t
		else throw std::out_of_range(std::to_string(_n) + " is greater than " + std::to_string(_size));
	}
	
			
	// overload for [] operator
	template<typename T>
	T& real_array<T>::operator[](size_t _n) {
		// if 0 is inserted, you got first element as usual ;)
		if(_n==0) return ptr[0];
		// else you got the "real" object requested
		if(_n<=_size) return ptr[_n-1];
		// throw exception if n>size_t
		else throw std::out_of_range(std::to_string(_n) + " is greater than " + std::to_string(_size));
	}
			
	// overload for [] operator for const objects
	template<typename T>
	const T& real_array<T>::operator[](size_t _n) const {
		// if 0 is inserted, you got first element as usual ;)
		if(_n==0) return ptr[0];
		// else you got the "real" object requested
		if(_n<=_size) return ptr[_n-1];
		// throw exception if n>size_t
		else throw std::out_of_range(std::to_string(_n) + " is greater than " + std::to_string(_size));
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

	// overload for << operator
	template<typename T>
	std::ostream& operator<<(std::ostream& _os, const real_array<T> &other) {
		for(size_t index = 1; index <=other._size; index++) std::cout << other[index] << " ";
		std::cout << std::endl;
		return _os;
	}
			
	// destructor
	template<typename T>
	real_array<T>::~real_array() {
		delete [] ptr;
	}
}


