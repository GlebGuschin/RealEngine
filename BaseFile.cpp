#include "stdafx.h"
#include "File.hpp"



class BaseFile : public File {

	FILE* file; 

public:

	BaseFile() : file(NULL){}

	bool open(const String& name, FILE_MODE_TYPE mode_, FILE_TYPE type = FILE_BINARY ) {
			
		static wchar_t* writeMode[2] = { L"wb+", L"w+" };
		static wchar_t* readMode[2] = {  L"rb+", L"r+" };	

		wchar_t* mode = NULL;

		if( mode_ == FILE_MODE_WRITE) {
				mode = type == FILE_BINARY ? writeMode[0] : writeMode[1];
		}
		if( mode_ == FILE_MODE_READ) {
				mode = type == FILE_BINARY ? readMode[0] : readMode[1];
		}


		file = _wfopen( name.w_str(), mode );
		if(!file ) return false;

		return true;

	}

	void close() {

		if(file) {
			fclose(file);
		}

		file = NULL;
	
	}

	size_t write(size_t size, const void* ptr ) {			

		size_t writted = fwrite( ptr, size, 1, file );
		return size;
	}

	size_t read(size_t size, void* ptr ) {

		size_t readed = fread( ptr, size, 1, file );
		return readed;

	}

	//size_t setPos(size_t) =0;

};

File* CreateFile() { return new BaseFile; }
