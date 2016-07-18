#pragma once 

#ifndef Referenced_HPP
#define Referenced_HPP

//#include "Name.hpp"
#include "Common.hpp"

class SmartPtrerenceInferface {

public:

	virtual void addSmartPtr() = 0;
	virtual void removeSmartPtr() = 0;
	virtual unsigned getCounter() const = 0;

};


class Referenced {

	unsigned counter;

	//volatile DWORD counter;

public:

	Referenced() : counter( 0 ) {}
	virtual ~Referenced() {}

	void addSmartPtr() { counter++; }
	void removeSmartPtr() { assert( counter ); if( counter == 1 ) { counter = 0; delete this; } else { counter--; } }
	unsigned getCounter() const { return( counter ); }

};


template <typename T>
class SharedPtr {

	typedef T* Ptr;
	Ptr ptr;

public:

	SharedPtr() : ptr( NULL ) { }
	SharedPtr( const SharedPtr<T> &rhs ) {  ptr = rhs.ptr; if( ptr ) { ptr->addSmartPtr(); } }
	SharedPtr( T * ptr_ ) {  ptr = ptr_; if( ptr ) { ptr->addSmartPtr(); } }
	~SharedPtr() { if( ptr ) ptr->removeSmartPtr(); }

		
	Ptr operator->() { return( ptr ); }

	SharedPtr& operator=( T  *ptr_  ) {  

		if( ptr ) { 
			ptr->removeSmartPtr();  
		}
		ptr = ptr_;

		if( ptr ) {
				ptr->addSmartPtr();
		}
	
		return( *this );

	}

	SharedPtr& operator=( const SharedPtr<T>& rhs ) {  
	
		if( ptr ) { 
				ptr->removeSmartPtr(); 
		}

		ptr = rhs.ptr;

		if( ptr ) { 
				ptr->addSmartPtr(); 
		}

		return( *this );

	}

	bool operator < ( const SharedPtr<T> &rsh ) const { return( ptr < rsh.ptr ); }

	operator Ptr() const { return( ptr ); } 
	//const operator Ptr() const { return( ptr ); } 
	//const Ptr operator*() const { return( ptr ); } 

};


class Listener : virtual public Referenced {

	unsigned priority;

public:

	Listener() : priority(0) {}
	Listener(unsigned priority_) : priority(priority_) {}

	unsigned getPriority() const { return priority; }

};





class Archive;
class Class;



struct UID {
	uint32 value;
};


class Object : virtual public Referenced {


	UID GenerateNewUID() { 
		static uint32 value = 0;
		UID uid; uid.value = ++value;
		return uid;
	}

	UID uid;

public:

	const UID getUID() const { return uid; }
	bool isKindOf() const { return false; }


	virtual Object* clone() const {return NULL; }
	virtual void serialize(Archive&) {}

	static Object* CreateInstance( const char* class_name );



};




#endif

