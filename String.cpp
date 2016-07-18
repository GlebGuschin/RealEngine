#include "stdafx.h"
#include "String.hpp"

const String String::Empty("");

String String::Format(const char* formatString, ...) {

		va_list argList;
		char outputString[ 4096 ];

		va_start( argList, formatString );
		vsprintf( outputString, formatString, argList );
		va_end( argList );
  
		return String( outputString );
	
}

bool String::splitPathFileExt( String& path, String& file, String& ext ) const {
	
	const wchar_t* dotChar = L".";
	const wchar_t* slashChar = L"/";

	path = file = ext = L"";

	size_t dotPos = string.find_last_of(dotChar);
	size_t slashPos = string.find_last_of(slashChar);

	if (dotPos == String::StringType::npos || slashPos == String::StringType::npos ) {
		return false;
	}

	for (size_t i = dotPos + 1; i < string.size(); i++) {
		ext.string += string[ i ];
	}

	for (size_t i = 0; i < slashPos; i++) {
		path.string += string[i];
	}

	for (size_t i = slashPos +1; i < dotPos; i++) {
		file.string += string[i];
	}

	return true;
}


//void Split(const String& string, DynamicArray<String>& strings, wchar_t delimiter);

void String::split(DynamicArray<String>& strings, wchar_t delimiter) {

	bool b = false;
	strings.clear();
	String temp;

	for (size_t i = 0; i < string.size(); i++) {
		
		if ( string[i] == delimiter && temp.string.size() > 0 ) {
			strings.add( temp );
			temp = L"";
			b = true;
		} else {
			temp.string += string[i];
		}

	}

	if ( temp.string.size() > 0 ) {
		strings.add(temp);
		b = true;
	}

	//return b;
}

void String::replaceSlash() {

	for (size_t i = 0; i < string.size(); i++) {
		if ( string[ i ] == wchar_t('\\') ) {
			string[i] = wchar_t('/');
		}
	}
}