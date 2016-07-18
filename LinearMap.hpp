#pragma once

#ifndef __LM_HPP__
#define __LM_HPP__

#include "Common.hpp"

template <typename Key, typename Value>
class LinearMap {

	struct KeyValue {
		Key key;
		Value value;
		bool operator <(const KeyValue& rhs) const { return key < rhs.key; }

	};

	typedef std::vector<KeyValue> Map;
	Map map;

	void sort() {
		std::sort(map.begin(), map.end());
	}

public:

	LinearMap(size_t reserve = 32) { map.reserve(reserve); }

	size_t size() const { return map.size(); }

	const KeyValue& operator[](size_t index) const { return map[index]; }
	
	void clear() { map.clear(); }
	void add(const Key& key, const Value& value) { 

		KeyValue mapItem;
		mapItem.key = key;
		mapItem.value = value;

		map.push_back( mapItem ); 
		sort();

	}

	void remove(const Key& key) {

		for( Map::iterator it = map.begin(); it != map.end(); it++) {			
			if( it->key == key) {
				map.erase( it);
				//sort();
				return;
			}		
		}

	}

};

template <typename Value>
class LinearSet {

	typedef std::vector<Value> SetType;
	SetType set;

	void sort() {
		std::sort(set.begin(), set.end());
	}

public:

	LinearSet(size_t reserve = 32) { set.reserve(reserve); }

	size_t size() const { return set.size(); }

	const Value& operator[](uint32 index) const { return set[index]; }
	
	void clear() { set.clear(); }
	void add(const Value& value) { 
	
		set.push_back( mapItem ); 
		//sort();

	}

	void remove(const Value& value) {

		for( SetType::iterator it = set.begin(); it != set.end(); it++) {			
			if( *it == value) {
				set.erase( it);
				return;
			}		
		}

	}

};







#endif






