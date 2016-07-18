#pragma once

#ifndef FILE_HPP
#define FILE_HPP

#include "Referenced.hpp"
#include "String.hpp"

enum FILE_TYPE {
	FILE_BINARY,
	FILE_TEXT,
};

enum FILE_MODE_TYPE {
	FILE_MODE_WRITE = 1,
	FILE_MODE_READ = 2
};

class File : public Referenced {

public:

	virtual bool open(const String&, FILE_MODE_TYPE mode, FILE_TYPE type = FILE_BINARY ) =0;
	virtual void close() =0;
	virtual size_t write(size_t, const void* ) =0;
	virtual size_t read(size_t, void* ) =0;
	//virtual size_t setPos(size_t) =0;

};

File* CreateFile();


class Stream : public Referenced {

public:

	//virtual bool open(const String&, FILE_MODE_TYPE mode, FILE_TYPE type = FILE_BINARY ) =0;
	//virtual void close() =0;

	virtual bool write(const String& ) =0;

	virtual bool read(String& ) =0;	

};


#endif