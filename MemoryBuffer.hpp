#pragma once

#ifndef __MEMORY_BUFFER_HPP__
#define __MEMORY_BUFFER_HPP__

#include "Common.hpp"
#include "Referenced.hpp"


struct MemoryBufferInfo {
	size_t size;
	unsigned flags;	
};



class MemoryBuffer : public Referenced {

	size_t size;
	void* ptr;

protected:

	unsigned lockCounter; // atomic ?

public:

	MemoryBuffer(size_t size_) : size(size_), lockCounter(0) {}

	size_t getSize() const { return size; }

	virtual void* lock(unsigned flags =0) = 0;
	virtual void  unlock() = 0;

};

MemoryBuffer* CreateMemoryBuffer(size_t size);
MemoryBuffer* CreateMemoryBuffer(MemoryBuffer*, size_t size, size_t offset);


//static MemoryBuffer* Create(const void* ptr, size_t size);

/*
class MemoryBuffer : public Referenced {

protected:

	unsigned lockCounter;
	MemoryBufferInfo info;

	size_t size;
	byte *ptr;
	 
	SharedPtr<MemoryBuffer> buffer;

	void reset() { size = 0; ptr = NULL; }

	MemoryBuffer( size_t size_ ) : buffer(NULL){ 
		lockCounter = 0; 
		size = size_; 
		ptr = (byte*)malloc( size );
		memset( ptr, 0, size ); 
	}

	MemoryBuffer() { reset(); }

	MemoryBuffer( MemoryBuffer *buffer_, size_t size_, size_t offset_ = 0) {
		assert( offset_ + size_ < size );
		buffer = buffer_;
		ptr = buffer->lock() + offset_;
	}
	
public:

	~MemoryBuffer() { 
	
		assert( lockCounter == 0 );

		size = 0;

		if( buffer ) {
				buffer = NULL; 
				return;
		}

		free( ptr );  
	
	} 

	template<typename T>
	void setValue(const T& value, unsigned arrayIndex) {
		size_t valueSize = sizeof(T);
		check( arrayIndex * valueSize <= size );
		T* valuePtr = (T*)ptr;
		valuePtr[arrayIndex] = value;
	}




	size_t getSize() const { return size; }
	virtual byte* lock() { lockCounter++; return( ptr ); }
	virtual void unlock() { assert( lockCounter ); lockCounter--; }

	byte& at( size_t index ) { assert( index < size ); return( ptr[ index ] ); }
	const byte& at( size_t index ) const { assert( index < size ); return( ptr[ index ] ); }
	
	byte& operator[]( size_t index ) { return( at( index ) ); }
	const byte& operator[]( size_t index ) const { return( at( index ) ); }
	
	void copyFrom( void* src_ptr, size_t src_size, size_t dst_offset = 0 ) {
		
		assert( dst_offset + src_size <= size );
		//lock();
		memcpy( (void*)(ptr + dst_offset), src_ptr, src_size );
		//memcpy( ((byte)ptr + dst_offset), src_ptr, src_size );
		//unlock();		
	}

	void copyFrom( MemoryBuffer* srcBuffer, size_t srcSize, size_t dstOffset = 0 ) {

		check( dstOffset + srcSize <= size );
		void* srcPtr = srcBuffer->lock();
		check(srcPtr);
		memcpy( (void*)(ptr + dstOffset), srcPtr, srcSize );
		//memcpy( ((byte)ptr + dst_offset), src_ptr, src_size );
		srcBuffer->unlock();			
	
	}
	
	static MemoryBuffer* Create( size_t size ) { return( new MemoryBuffer( size ) ); }

	static MemoryBuffer* Create( MemoryBuffer* buffer, size_t size, size_t offset = 0 ) { 
		return( new MemoryBuffer( buffer, size, offset ) ); 
	}

	static MemoryBuffer* CreateFromFile( const char *fileName );
	static MemoryBuffer* Create( const std::string& string );
	static MemoryBuffer* Create(const void* ptr, size_t size); 

};

*/


#endif