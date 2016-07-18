


#include "stdafx.h"

#include "Archive.hpp"



Archive::Archive() {}
  //XArchive( ICoreSystem *_coreSystem );
Archive::~Archive() {}

	
bool Archive::open( const String &fileName, ARCHIVE_MODE mode ) {

	static wchar_t* writeMode = L"wb+";
	static wchar_t* readMode = L"rb+";

	
	if( mode == ARCHIVE_WRITE )	{
			file = _wfopen(fileName.w_str(), writeMode);
			bReading = false;
			endPosition = 0;
	} else {
			file = _wfopen(fileName.w_str(), readMode);
			bReading = true;
			fseek( file, 0, SEEK_END );
			endPosition = ftell( file );
			fseek( file, 0, SEEK_SET );
			assert( ftell( file ) == 0 );						
	}
  
  return( !file );
  

}
 
void Archive::close() {

	long currentPosition = 0;
	
			
	if( !isReading() ) {
			fflush( file );
	} else {
			fseek( file, 0, SEEK_END );
			currentPosition = ftell( file );	
	}

	fclose( file );

	if( !isReading() ) {
			assert( endPosition == currentPosition );
	}
		    
  file = NULL;


}
  


template
<class T>
Archive& swap( Archive &archive, T &_value ) {

	T value = _value;
	size_t Size = sizeof(T);

	long filePos = ftell( archive.file );

	if( !archive.isReading() ) {

		  size_t written = fwrite( &value, Size, 1, archive.file );
			assert( written == 1 );

	} else {

			size_t readed = fread( &value, Size, 1, archive.file );
			assert( readed == 1 );
			_value = value;

	}

	filePos = ftell( archive.file );

  return( archive );

}



  //template< class T>
  //friend Archive& swap( XArchive&, T& value );
  
Archive& operator << ( Archive &archive, bool &value ) { return( swap( archive, value ) ); }
Archive& operator << ( Archive &archive, char &value ) { return( swap( archive, value ) ); }
Archive& operator << ( Archive &archive, uint8 &value ) { return( swap( archive, value ) ); }		
Archive& operator << ( Archive &archive, uint16 &value ) { return( swap(archive, value)) ; }
Archive& operator << ( Archive &archive, uint32 &value ) { return( swap( archive, value ) ); }
Archive& operator << ( Archive &archive, uint64 &value ) { return( swap(archive, value) ); }

Archive& operator << (Archive &archive, String& resourceName) {

	if( archive.isReading() ) {
			uint16 size = 0;
			archive << size;
			std::wstring string;
			string.resize( size );
			for( uint16 i = 0; i < size; i++) {
					archive << string[ i ];
			}			
			//resourceName = ResourceName( string.c_str() );
	} else {
		std::wstring string = resourceName.w_str();
		uint16 size = (uint16)string.size();
		archive << size;
		for( uint16 i = 0; i < size; i++) {
				archive << string[ i ];
		}
	}

	return archive;

}

Archive& operator << (Archive &archive, Name& name) { 

	if( archive.isReading() ) {
			uint16 size = 0;
			archive << size;
			std::string string;
			string.resize( size );
			for( uint16 i = 0; i < size; i++) {
					archive << string[ i ];
			}

			Name name2( string.c_str() );
			name = name2;

	} else {
		std::string string(name);
		uint16 size = (uint16)string.size();
		archive << size;
		for( uint16 i = 0; i < size; i++) {
				archive << string[ i ];
		}
	}


	return archive;
}

/*
Archive& operator << ( Archive &archive, uint& );  

Archive& operator << ( Archive &archive, float& );	
Archive& operator << ( Archive &archive, dword& );
*/

Archive& operator << ( Archive &archive, wchar_t &value ) { return( swap( archive, value ) ); }

Archive& operator << ( Archive &archive, float &value ) {  return( swap( archive, value ) ); }

Archive& operator << ( Archive &archive, std::wstring &str ) {

	if( !archive.isReading() ) {	

			size_t len = str.size();

			archive << len;

			for( std::wstring::const_iterator it = str.begin(); it != str.end(); it++ ) {
						wchar_t wc = *it;
						archive << wc;    
			}

	} else {
	
			size_t len;

			archive << len;
			str.resize( len );

			for( size_t i = 0; i < len; i++ ) {
					 archive << str[ i ];    
			}

	}

	return( archive );

}


/*

Archive& operator << ( Archive &archive, Color &color ) {

	return( archive << color.r << color.g << color.b << color.a );

}



Archive& operator <<( Archive& archive, VertexLayout &vertexLayout ) {

	archive << vertexLayout;

	for( size_t i = 0; i < VertexLayout::MAX_VALUE; i++ ) {
			//archive << vertexLayout[ i ].
	
	}

	return( archive );

}

Archive& operator << ( Archive &archive, Sphere &sphere ) {

	return( archive << sphere.origin << sphere.radius );

}

Archive& operator << ( Archive &archive, Plane &plane ) {
	//assert(0);
	//return( archive );
	return( archive << plane.getNormal() << plane.getDistanse() );
	//return( archive << plane.getNormal() );
}

Archive& operator << ( Archive &archive, Vector3 &vector ) {
	return( archive << vector.x() << vector.y() << vector.z() );
}

Archive& operator << ( Archive &archive, Matrix3x3& matrix ) {
	return( archive << matrix.x() << matrix.y() << matrix.z() );
}

Archive& operator << ( Archive &archive, Vector4 &vector ) {
	return( archive << vector.x() << vector.y() << vector.z() << vector.w() );
}

Archive& operator << ( Archive &archive, Matrix4x4 &matrix ) {
	return( archive << matrix.x() << matrix.y() << matrix.z() << matrix.w() );
}

*/