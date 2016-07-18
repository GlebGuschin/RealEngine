
#pragma once

#ifndef __COMMON_HPP__
#define __COMMON_HPP__


#include <typeinfo.h>
#include <string>
#include <wchar.h>
#include <assert.h>

#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>

//#include "Engine/Common/Name.hpp"
//#include "String.hpp"
//typedef ResourceName AssetName;


typedef unsigned short half;
typedef unsigned uint;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned int dword;
typedef unsigned short word;


typedef unsigned	uint32;
typedef int			int32;

typedef unsigned short  uint16;
typedef short 	int16;

typedef unsigned char uint8;
typedef char int8;

typedef unsigned long long uint64;
typedef  long long 			int64;



#define check(param)  assert(param)

//#define  dcast(ptr) dynamic_cast<T>(ptr)

//#define TEXT(x) L#x


template <class T, size_t SIZE = 16>
class Array {

	T array[SIZE];

public:

	const T& operator[](size_t index) const { assert(index < SIZE); return array[ index ]; }
	T& operator[](size_t index) { assert(index < SIZE); return array[index]; }
	size_t size() const { return SIZE; }

};


class TimeUpdate {

	float delta;

public:

	TimeUpdate() { reset(); }
	void reset() {  delta = 0.0f; }
	float getValue() const { return( delta ); }
	void process( float deltaTime ) {  delta += deltaTime; }

};













template <class T, uint32 CAPACITY = 16>
class Timeline {

	struct Pair {
		float key;
		T value;
		Pair(float key_, const T& value_) {
			key = key_;
			value = value_;
		}
		bool operator<(const Pair& pair) const { return key < pair.key; }
};
	//Pair pairs[ CAPACITY ];
	std::vector<Pair> pairs;

	float EPSILON;

public:

	Timeline(uint reserve = 32, float epsilon_ = 0.001f) : EPSILON(epsilon_) { pairs.reserve(reserve); }

	void add(float key, const T& value) {

		for (uint i = 0; i < pairs.size(); i++) {
			if (fabs(key - pairs[i].key) < EPSILON) {
				pairs[i].value = value;
				return;
			}
		}

		pairs.push_back(Pair(key, value));
		std::sort(pairs.begin(), pairs.end());
	}

	void remove(float key) {
	
		for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); it++) {
			if (fabs(key - it->key) < EPSILON) {
				pairs.erase(it);
				return;
			}
		}
		assert(0);
	}

	void removeAll() { pairs.clear();  }

};

void Log(const char* ...);







#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
//#include <tchar.h>
#include <windows.h>



// TODO: SmartPtrerence additional headers your program requires here

#endif