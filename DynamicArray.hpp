#pragma once

#ifndef __DA_HPP__
#define __DA_HPP__

#include "Common.hpp"

template <typename T> 
class DynamicArray {

	typedef std::vector<T> ArrayType;

	ArrayType array;

public:

	DynamicArray(unsigned reserve = 32) { array.reserve(reserve); }

	unsigned size() const { return (unsigned)array.size(); }

	const T& operator[](size_t index) const { return array[index ]; }
	T& operator[](size_t index){ return array[index ]; }

	bool find(const T& value) const { 
		return std::find(array.begin(), array.end(), value) != array.end();  		
	}

	void clear() { array.clear(); }

	void add( const T& value, bool unique = true ) { 

		if (unique && find(value)) {
			return;
		}
		array.push_back(value); 
	}	

	void remove( const T& value ) {
	
		ArrayType::iterator it = std::find( array.begin(), array.end(), value );
		if( it != array.end() ) array.erase(it);
	
	}

	void removeAt(size_t index) {

		//ArrayType::iterator it = std::find(array.begin(), array.end(), value);
		//if (it != array.end()) array.erase(it);		
		ArrayType::iterator it = array.begin();
		for (size_t i = 0; i < index; it++) {
					
		}

		array.erase(it);

	}


	void resize(size_t size) { array.resize(size); }
	void reserve(size_t size) { array.reserve(size); }


	void removeLast() { 

		check( array.size() > 0 );  
		array.pop_back();
	}


};



#endif






