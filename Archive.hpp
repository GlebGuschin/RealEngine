#pragma once

#ifndef _ARCHIVE_HPP_
#define _ARCHIVE_HPP_


#include "String.hpp"
#include "Name.hpp"

enum ARCHIVE_MODE { ARCHIVE_WRITE, ARCHIVE_READ };

class Archive {

	long endPosition;
	
  //SmartPtr<ICoreSystem> coreSystem;
  
  bool bReading;
  bool bValid;
	bool bEOF;
  
  FILE *file;

	bool swap( size_t size, void *ptr );

public:

	Archive();
  //XArchive( ICoreSystem *_coreSystem );
  ~Archive();

	bool isReading() const { return( bReading );}
	bool isValid() const { return( bValid ); }
	bool isEOF() const { return( bEOF ); }
	
  bool open( const String &fileName, ARCHIVE_MODE mode );
  void close();
  

  template<class T>
  friend Archive& swap( Archive&, T& value );
  

	friend Archive& operator << ( Archive&, bool& );		
	friend Archive& operator << ( Archive&, char& );		
	friend Archive& operator << ( Archive&, uint8& );		
	friend Archive& operator << ( Archive&, wchar_t& );	
	friend Archive& operator << ( Archive&, uint16& );
	friend Archive& operator << ( Archive&, uint32& );  
	friend Archive& operator << ( Archive&, uint64& );
	friend Archive& operator << ( Archive&, float& );		
	friend Archive& operator << ( Archive &archive, std::wstring &str );

	//friend Archive& operator << (Archive &archive, ResourceName& resourceName);
	//friend Archive& operator << (Archive &archive, Name& name);

    
};


#endif