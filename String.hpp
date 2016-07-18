#pragma once

#ifndef __STRING_HPP__
#define __STRING_HPP__

#include "Common.hpp"
#include "DynamicArray.hpp"
#include <stdarg.h>


class String;

class String { 

	typedef std::wstring StringType;

	StringType string;		

public:

	String() {}	
	~String() {}
	String( const wchar_t* string_ ) : string( string_) {}
	String( const char* string_ ) {

		size_t size = strlen(string_);
		string.resize(size);

		for (size_t i = 0; i < size; i++) { 
			string[i] = (wchar_t)string_[i];		
		}

	}

	bool splitPathFileExt( String& path, String& file, String& ext ) const;		
	void split(DynamicArray<String>& strings, wchar_t delimiter);
	void replaceSlash();

	static String Format(const char* formatString, ...);

	static const String Empty;

	/*
	static String Format(const wchar_t* formatString, ...) {

		va_list argList;
		wchar_t outputString[ 4096 ];

		va_start( argList, formatString );
		vcwprintf( outputString, formatString, argList );
		va_end( argList );
  
		return String( outputString );	
	}
	*/


	//

	//ResourceName( const wchar_t* name_ ) { name.reserve( MAX_RESOURCE_NAME_SIZE ); name = name_; }
	//ResourceName( const ResourceName& name_ ) { name = name_.name; }
	//~ResourceName() {}

	bool operator==( const String& rhs ) const { return( string == rhs.string ); }
	bool operator!=( const String& rhs ) const { return( string != rhs.string ); }
	bool operator<(const String& rhs) const { return(std::lexicographical_compare(string.begin(), string.end(), rhs.string.begin(), rhs.string.end())); }

	String& operator+=(const String& rhs) {  string+= rhs.string; return *this; }

	//static ResourceName NONAME;

	//const  StringType& w_str() const { return string; }
	const wchar_t* w_str() const { return string.c_str(); }

private:

};


class ResourceName {

	String path, file, ext, name;
	bool valid;

public:

	ResourceName() : valid(false) {}

	ResourceName( const char* cstr ) {	
		String string(cstr);
		valid = string.splitPathFileExt( path, file, ext );			
		name = string;
	}

	ResourceName( const String& string ) {	
		valid = string.splitPathFileExt( path, file, ext );			
		name = string;
	}

	bool isValid() const { return valid; }

	const String& getName() const { return name; }
	const String& getPath() const { return path; }
	const String& getFile() const { return file; }
	const String& getExt() const { return ext; }

	bool operator<(const ResourceName& rhs) const { return( name < rhs.name); }

};

//class FileName
//void Split(const String& string, DynamicArray<String>& strings, wchar_t delimiter);

	//ResourceName( const wchar_t* name_ ) { name.reserve( MAX_RESOURCE_NAME_SIZE ); name = name_; }
	//ResourceName( const ResourceName& name_ ) { name = name_.name; }


#endif
