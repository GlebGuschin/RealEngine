#include "stdafx.h"
#include "MemoryBuffer.hpp"


class BaseMemoryBuffer : public MemoryBuffer {

	void* ptr;

public:

	BaseMemoryBuffer(size_t size_, void* ptr_): MemoryBuffer(size_), ptr(ptr_) {}
	~BaseMemoryBuffer() { assert( lockCounter == 0 ); free(ptr); }

	void* lock(unsigned flags =0) { assert(ptr); lockCounter++; return ptr; }
	void  unlock() { assert(lockCounter && ptr); lockCounter--; } 

};

MemoryBuffer* CreateMemoryBuffer(size_t size) { 

	void* ptr = malloc( size );
	if(ptr) return new BaseMemoryBuffer( size, ptr);

	return NULL; 

}


class BoundMemoryBuffer : public MemoryBuffer {

	SharedPtr<MemoryBuffer> buffer;
	size_t offset;

public:

	BoundMemoryBuffer(MemoryBuffer* buffer_, size_t size_, size_t offset_ ) : MemoryBuffer(size_), offset(offset_), buffer(buffer_) {}
	~BoundMemoryBuffer() { assert(lockCounter == 0); }

	void* lock(unsigned flags = 0) { 
		assert(buffer); lockCounter++; 
	char* ptr = (char*)buffer->lock();
	return &ptr[offset]; }

	void  unlock() { assert(lockCounter && buffer); lockCounter--; buffer->unlock(); }

};

MemoryBuffer* CreateMemoryBuffer( MemoryBuffer* buffer,  size_t size, size_t offset) {

	if (buffer) return new BoundMemoryBuffer(buffer, size, offset);

	return NULL;

}








class FileMemoryBuffer : public MemoryBuffer {

	//void* ptr;
	HANDLE hFile;

public:

	FileMemoryBuffer(size_t size_): MemoryBuffer(size_) {}
	~FileMemoryBuffer() { assert( lockCounter == 0 );  }

	//void* lock(unsigned flags =0) { assert(ptr); lockCounter++; return ptr; }
	//void  unlock() { assert(lockCounter && ptr); lockCounter--; } 

};


